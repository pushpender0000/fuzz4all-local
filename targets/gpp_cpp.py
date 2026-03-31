import os
import re
import shutil
import tempfile
from typing import Optional, Tuple, List

from targets.base import Target, RunResult, Finding
from utils.complexity import complexity_score_cpp
from utils.tooling import (
    run_capture, trim_output, cmd_to_str, looks_like_ub,
    get_os_string, resolve_tool_path, compiler_version_line
)

ICE_PATTERNS = [
    "internal compiler error",
    "please submit a full bug report",
    "segmentation fault",
    "bus error",
    "stack smashing",
    "double free",
    "malloc():",
]

def _mk_runresult(rc: int, out: str, err: str, timed: bool) -> RunResult:
    low = (err or "").lower()
    crash_like = any(pat in low for pat in ICE_PATTERNS)
    ok = (rc == 0) and (not timed) and (not crash_like)
    return RunResult(ok=ok, rc=rc, stdout=out or "", stderr=err or "", timed_out=timed, crash_like=crash_like)

def extract_fenced_cpp(text: str) -> str:
    m = re.search(r"```(?:cpp|c\+\+)?\s*(.*?)```", text, flags=re.DOTALL | re.IGNORECASE)
    return (m.group(1).strip() if m else text.strip())

class GppCppTarget(Target):
    name = "cpp"
    file_ext = ".cpp"

    def __init__(self, compiler: str = "g++", std: str = "c++20", extra_flags: Optional[str] = None):
        self.compiler = compiler
        self.std = std
        self.extra_flags = extra_flags or ""

    def fence_lang(self) -> str:
        return "cpp"

    def extract_program(self, llm_text: str) -> str:
        return extract_fenced_cpp(llm_text)

    def autoprompt_instruction(self) -> str:
        return (
            "Please summarize the above information in a concise manner to describe the usage and "
            "functionality of the target.\n"
            "This summary will be used as an input prompt for generating VALID C++ programs for compiler fuzzing.\n"
            "Include: core concept, types/constraints, key APIs, tricky edge cases, typical usage patterns.\n"
            "Write structured.\n"
        )

    def build_generation_rules(self) -> str:
        return f"""Generate a VALID, compilable C++ program designed to stress GCC/G++.
Hard requirements:
- Output ONLY C++ code (no explanations).
- Single self-contained file.
- Must compile under: -std={self.std}
- Program MUST be deterministic: no randomness, no time, no filesystem, no undefined behavior.
- Program MUST print exactly one line to stdout (e.g., an integer/hash).
- Use templates + at least one nested template instantiation.
- Use constexpr or consteval at least once.
- Use lambdas at least once.
- Use type traits / decltype / std::is_same_v at least once.
- Avoid UB (no OOB / uninitialized).
- Keep <= 200 lines.
Goal: Stress parsing + templates + constexpr + optimization.
"""

    def _static_scan(self, src: str, timeout_s: int) -> Tuple[bool, int, str, int, str]:
        cppcheck = resolve_tool_path("cppcheck")
        clang_tidy = resolve_tool_path("clang-tidy")

        cpp_cmd: List[str] = [
            cppcheck,
            "--enable=warning,style,performance,portability",
            "--inconclusive",
            "--language=c++",
            f"--std={self.std}",
            "--error-exitcode=2",
            "-q",
            src,
        ]
        tidy_cmd: List[str] = [
            clang_tidy,
            "-checks=clang-analyzer-*,bugprone-*",
            "-warnings-as-errors=clang-analyzer-*",
            src,
            "--",
            f"-std={self.std}",
        ]

        cpp_rc, cpp_out, cpp_err, cpp_timed = run_capture(cpp_cmd, timeout_s=timeout_s)
        cpp_txt = trim_output((cpp_out or "") + ("\n" + cpp_err if cpp_err else ""))
        cpp_failed = (cpp_rc != 0) or cpp_timed or looks_like_ub(cpp_txt)

        tidy_rc, tidy_out, tidy_err, tidy_timed = run_capture(tidy_cmd, timeout_s=timeout_s)
        tidy_txt = trim_output((tidy_out or "") + ("\n" + tidy_err if tidy_err else ""))
        tidy_failed = (tidy_rc != 0) or tidy_timed or looks_like_ub(tidy_txt)

        passed = not (cpp_failed or tidy_failed)
        return passed, cpp_rc, cpp_txt, tidy_rc, tidy_txt

    def _sanitizer_gate(self, src: str, timeout_s: int) -> Tuple[str, int, int, str, bool, bool]:
        tmpbin = src + ".asan.out"
        extra = self.extra_flags.split() if self.extra_flags else []

        compile_cmd = [
            self.compiler,
            src,
            f"-std={self.std}",
            "-O1",
            "-g",
            "-fno-omit-frame-pointer",
            "-fsanitize=address,undefined",
            "-fno-sanitize-recover=all",
            *extra,
            "-o",
            tmpbin,
        ]
        c_rc, c_out, c_err, c_timed = run_capture(compile_cmd, timeout_s=timeout_s)
        c_txt = trim_output((c_out or "") + ("\n" + c_err if c_err else ""))

        if c_timed:
            return cmd_to_str(compile_cmd), 124, 0, trim_output(c_txt + "\n[TIMEOUT]"), False, True

        if c_rc != 0:
            return cmd_to_str(compile_cmd), c_rc, 0, c_txt, False, looks_like_ub(c_txt)

        r_rc, r_out, r_err, r_timed = run_capture([tmpbin], timeout_s=timeout_s)
        r_txt = trim_output((r_out or "") + ("\n" + r_err if r_err else ""))

        ub = looks_like_ub(r_txt)
        passed = (not r_timed) and (r_rc == 0) and (not ub)
        return cmd_to_str(compile_cmd), c_rc, (124 if r_timed else r_rc), r_txt, passed, ub

    def _run_and_capture_trim(self, bin_path: str, timeout_s: int) -> Tuple[int, str, str, bool]:
        rc, out, err, timed = run_capture([bin_path], timeout_s=timeout_s)
        return rc, trim_output(out), trim_output(err), timed

    def oracle(self, program_text: str, timeout_s: int) -> Tuple[Finding, RunResult, Optional[RunResult]]:
        tmp = tempfile.mkdtemp(prefix="gpp_fuzz_")
        src = os.path.join(tmp, "t.cpp")
        b0 = os.path.join(tmp, "o0.out")
        b2 = os.path.join(tmp, "o2.out")

        report = {
            "input_identity": {"id": "N/A", "target": "cpp", "source_file": "N/A"},
            "static_ub_scan": {
                "static_scan_passed": False,
                "cppcheck_rc": 0,
                "cppcheck_output": "",
                "clang_tidy_rc": 0,
                "clang_tidy_output": "",
            },
            "sanitizer_gate": {
                "sanitizer_compile_cmd": "",
                "sanitizer_compile_rc": 0,
                "sanitizer_run_rc": 0,
                "sanitizer_stderr": "",
                "sanitizer_passed": False,
                "ub_detected": False,
            },
            "normal_compilation": {
                "compile_O0_cmd": "",
                "compile_O0_rc": 0,
                "compile_O0_stderr": "",
                "compile_O2_cmd": "",
                "compile_O2_rc": 0,
                "compile_O2_stderr": "",
            },
            "execution_check": {
                "exec_enabled": True,
                "run_O0_rc": 0,
                "run_O0_stdout": "",
                "run_O0_stderr": "",
                "run_O0_timed_out": False,
                "run_O2_rc": 0,
                "run_O2_stdout": "",
                "run_O2_stderr": "",
                "run_O2_timed_out": False,
                "outputs_match": False,
            },
            "finding": {
                "finding_kind": "NONE",
                "finding_stage": "N/A",
                "finding_details": "",
            },
            "environment": {
                "os": get_os_string() or "N/A",
                "compiler_path": resolve_tool_path(self.compiler) or "N/A",
                "compiler_version": compiler_version_line(self.compiler) or "N/A",
                "std": self.std or "N/A",
                "timeout_sec": int(timeout_s),
            },
        }

        try:
            with open(src, "w", encoding="utf-8") as f:
                f.write(program_text)

            # Step 1: Static UB scan
            static_passed, cpp_rc, cpp_txt, tidy_rc, tidy_txt = self._static_scan(src, timeout_s=timeout_s)
            report["static_ub_scan"]["static_scan_passed"] = bool(static_passed)
            report["static_ub_scan"]["cppcheck_rc"] = int(cpp_rc)
            report["static_ub_scan"]["cppcheck_output"] = cpp_txt
            report["static_ub_scan"]["clang_tidy_rc"] = int(tidy_rc)
            report["static_ub_scan"]["clang_tidy_output"] = tidy_txt

            if not static_passed:
                report["finding"]["finding_kind"] = "NONE"
                report["finding"]["finding_stage"] = "static_scan"
                report["finding"]["finding_details"] = "Rejected by static UB scan (cppcheck/clang-tidy)."
                self.last_report = report
                return Finding("NONE", "Rejected by static UB scan"), _mk_runresult(2, "", "Rejected by static UB scan", False), None

            # Step 2: Sanitizer gate (ASan+UBSan)
            san_cmd, san_c_rc, san_r_rc, san_stderr, san_passed, ub = self._sanitizer_gate(src, timeout_s=timeout_s)
            report["sanitizer_gate"]["sanitizer_compile_cmd"] = san_cmd or "N/A"
            report["sanitizer_gate"]["sanitizer_compile_rc"] = int(san_c_rc)
            report["sanitizer_gate"]["sanitizer_run_rc"] = int(san_r_rc)
            report["sanitizer_gate"]["sanitizer_stderr"] = san_stderr
            report["sanitizer_gate"]["sanitizer_passed"] = bool(san_passed)
            report["sanitizer_gate"]["ub_detected"] = bool(ub)

            if not san_passed:
                report["finding"]["finding_kind"] = "NONE"
                report["finding"]["finding_stage"] = "sanitizer"
                report["finding"]["finding_details"] = "Rejected by ASan/UBSan gate (UB/crash/runtime error)."
                self.last_report = report
                return Finding("NONE", "Rejected by sanitizer gate"), _mk_runresult(3, "", "Rejected by sanitizer gate", False), None

            # Step 3: Compiler testing (-O0 / -O2)
            extra = self.extra_flags.split() if self.extra_flags else []
            cmd_o0 = [self.compiler, src, f"-std={self.std}", "-O0", "-w", "-pipe", *extra, "-o", b0]
            cmd_o2 = [self.compiler, src, f"-std={self.std}", "-O2", "-w", "-pipe", *extra, "-o", b2]
            report["normal_compilation"]["compile_O0_cmd"] = cmd_to_str(cmd_o0)
            report["normal_compilation"]["compile_O2_cmd"] = cmd_to_str(cmd_o2)

            o0_rc, o0_out, o0_err, o0_timed = run_capture(cmd_o0, timeout_s=timeout_s)
            o2_rc, o2_out, o2_err, o2_timed = run_capture(cmd_o2, timeout_s=timeout_s)

            o0_err_txt = trim_output((o0_out or "") + ("\n" + o0_err if o0_err else ""))
            o2_err_txt = trim_output((o2_out or "") + ("\n" + o2_err if o2_err else ""))

            report["normal_compilation"]["compile_O0_rc"] = int(o0_rc)
            report["normal_compilation"]["compile_O0_stderr"] = o0_err_txt
            report["normal_compilation"]["compile_O2_rc"] = int(o2_rc)
            report["normal_compilation"]["compile_O2_stderr"] = o2_err_txt

            r0 = _mk_runresult(o0_rc, o0_out, o0_err, o0_timed)
            r2 = _mk_runresult(o2_rc, o2_out, o2_err, o2_timed)

            if r0.crash_like or r2.crash_like:
                report["finding"]["finding_kind"] = "CRASH"
                report["finding"]["finding_stage"] = "compile_O0" if r0.crash_like else "compile_O2"
                report["finding"]["finding_details"] = "ICE/crash signature in compiler output."
                self.last_report = report
                return Finding("CRASH", "ICE/crash signature in compiler output"), r0, r2

            if r0.timed_out or r2.timed_out:
                report["finding"]["finding_kind"] = "TIMEOUT"
                report["finding"]["finding_stage"] = "compile_O0" if r0.timed_out else "compile_O2"
                report["finding"]["finding_details"] = "Compiler timed out (potential hang)."
                self.last_report = report
                return Finding("TIMEOUT", "Compiler timed out (potential hang)"), r0, r2

            if o0_rc != 0 or o2_rc != 0:
                report["finding"]["finding_kind"] = "NONE"
                report["finding"]["finding_stage"] = "compile"
                report["finding"]["finding_details"] = "Did not compile cleanly under both -O0/-O2."
                self.last_report = report
                return Finding("NONE", ""), r0, r2

            # Step 4: Miscompilation check (execute binaries)
            run_o0_rc, run_o0_out, run_o0_err, run_o0_timed = self._run_and_capture_trim(b0, timeout_s=timeout_s)
            run_o2_rc, run_o2_out, run_o2_err, run_o2_timed = self._run_and_capture_trim(b2, timeout_s=timeout_s)

            report["execution_check"]["run_O0_rc"] = int(run_o0_rc)
            report["execution_check"]["run_O0_stdout"] = run_o0_out
            report["execution_check"]["run_O0_stderr"] = run_o0_err
            report["execution_check"]["run_O0_timed_out"] = bool(run_o0_timed)

            report["execution_check"]["run_O2_rc"] = int(run_o2_rc)
            report["execution_check"]["run_O2_stdout"] = run_o2_out
            report["execution_check"]["run_O2_stderr"] = run_o2_err
            report["execution_check"]["run_O2_timed_out"] = bool(run_o2_timed)

            outputs_match = (
                (not run_o0_timed) and (not run_o2_timed)
                and (run_o0_rc == run_o2_rc)
                and (run_o0_out == run_o2_out)
                and (run_o0_err == run_o2_err)
            )
            report["execution_check"]["outputs_match"] = bool(outputs_match)

            if not outputs_match:
                report["finding"]["finding_kind"] = "DIFF"
                report["finding"]["finding_stage"] = "execute"
                report["finding"]["finding_details"] = "Potential miscompilation: -O0 vs -O2 execution outputs/rc differ."
                self.last_report = report
                return Finding("DIFF", "Potential miscompilation: -O0 vs -O2 outputs/rc differ"), r0, r2

            report["finding"]["finding_kind"] = "NONE"
            report["finding"]["finding_stage"] = "N/A"
            report["finding"]["finding_details"] = ""
            self.last_report = report
            return Finding("NONE", ""), r0, r2
        finally:
            shutil.rmtree(tmp, ignore_errors=True)

    def is_valid(self, run0: RunResult, run1: Optional[RunResult]) -> bool:
        rep = getattr(self, "last_report", None) or {}
        try:
            s_ok = bool(rep.get("static_ub_scan", {}).get("static_scan_passed", False))
            g_ok = bool(rep.get("sanitizer_gate", {}).get("sanitizer_passed", False))
            n = rep.get("normal_compilation", {}) or {}
            o0 = int(n.get("compile_O0_rc", 1))
            o2 = int(n.get("compile_O2_rc", 1))
            ex = rep.get("execution_check", {}) or {}
            match = bool(ex.get("outputs_match", False))
            return s_ok and g_ok and (o0 == 0) and (o2 == 0) and match
        except Exception:
            return False

    def complexity(self, program_text: str) -> int:
        return complexity_score_cpp(program_text)
