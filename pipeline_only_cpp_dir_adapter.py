#!/usr/bin/env python3
import argparse
import json
import os
import subprocess
from typing import Dict, List, Optional, Tuple

ICE_PATTERNS = [
    "internal compiler error",
    "please submit a full bug report",
    "segmentation fault",
    "bus error",
    "stack smashing",
    "double free",
    "malloc():",
    "abort",
]

SAN_PATTERNS = [
    "runtime error:",
    "undefined behavior",
    "undefined behaviour",
    "ubsan",
    "addresssanitizer",
    "heap-buffer-overflow",
    "stack-buffer-overflow",
    "use-after-free",
    "double free",
    "signed integer overflow",
    "null pointer",
    "out of bounds",
    "use-of-uninitialized-value",
]

def trim(s: str, limit: int = 12000) -> str:
    s = s or ""
    if len(s) <= limit:
        return s
    return s[: int(limit * 0.65)] + "\n...\n" + s[-int(limit * 0.35):]

def shell_join(cmd: List[str]) -> str:
    out = []
    for x in cmd:
        if not x:
            out.append("''")
        elif any(c in x for c in " \t\n\"'\\$`"):
            out.append("'" + x.replace("'", "'\"'\"'") + "'")
        else:
            out.append(x)
    return " ".join(out)

def contains_any(text: str, patterns: List[str]) -> bool:
    low = (text or "").lower()
    return any(p in low for p in patterns)

def run_capture(cmd: List[str], timeout_s: int, cwd: Optional[str] = None) -> Tuple[int, str, str, bool]:
    try:
        p = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            cwd=cwd,
            timeout=timeout_s,
        )
        return p.returncode, p.stdout or "", p.stderr or "", False
    except subprocess.TimeoutExpired as e:
        out = e.stdout or ""
        err = e.stderr or ""
        if isinstance(out, bytes):
            out = out.decode("utf-8", errors="replace")
        if isinstance(err, bytes):
            err = err.decode("utf-8", errors="replace")
        return 124, out, (err or "") + "\n[TIMEOUT]", True
    except FileNotFoundError as e:
        return 127, "", f"[ERROR] Command not found: {cmd[0]} ({e})", False

def find_sources(work_dir: str) -> List[str]:
    srcs = []
    for name in sorted(os.listdir(work_dir)):
        p = os.path.join(work_dir, name)
        if os.path.isfile(p) and name.endswith((".cpp", ".cc", ".cxx")):
            srcs.append(name)
    return srcs

def cppcheck_stage(srcs: List[str], work_dir: str, std: str, timeout: int) -> Dict:
    cmd = [
        "cppcheck",
        "--enable=warning,style,performance,portability",
        "--inconclusive",
        "--language=c++",
        f"--std={std}",
        "--error-exitcode=2",
        "-q",
        *srcs,
    ]
    rc, out, err, timed = run_capture(cmd, timeout_s=timeout, cwd=work_dir)
    return {
        "passed": (rc == 0 and not timed),
        "rc": rc,
        "stdout": trim(out),
        "stderr": trim(err),
        "timed_out": timed,
        "cmd": shell_join(cmd),
    }

def clang_tidy_stage(srcs: List[str], work_dir: str, std: str, timeout: int) -> Dict:
    if not srcs:
        return {
            "passed": False,
            "rc": 1,
            "stdout": "",
            "stderr": "No C++ source files found",
            "timed_out": False,
            "cmd": "",
        }

    src = srcs[0]
    cmd = [
        "clang-tidy",
        "-checks=clang-analyzer-*,bugprone-*",
        "-warnings-as-errors=clang-analyzer-*",
        src,
        "--",
        f"-std={std}",
        "-I.",
    ]
    rc, out, err, timed = run_capture(cmd, timeout_s=timeout, cwd=work_dir)
    txt = (out or "") + "\n" + (err or "")
    return {
        "passed": (rc == 0 and not timed and not contains_any(txt, SAN_PATTERNS)),
        "rc": rc,
        "stdout": trim(out),
        "stderr": trim(err),
        "timed_out": timed,
        "cmd": shell_join(cmd),
    }

def sanitizer_stage(srcs: List[str], work_dir: str, compiler: str, std: str, timeout: int) -> Dict:
    bin_name = "san.out"
    cmd = [
        compiler,
        *srcs,
        f"-std={std}",
        "-I.",
        "-O1",
        "-g",
        "-fno-omit-frame-pointer",
        "-fsanitize=address,undefined",
        "-fno-sanitize-recover=all",
        "-o",
        bin_name,
    ]
    c_rc, c_out, c_err, c_timed = run_capture(cmd, timeout_s=timeout, cwd=work_dir)
    c_txt = trim((c_out or "") + ("\n" + c_err if c_err else ""))

    if c_timed:
        return {
            "passed": False,
            "compile_rc": 124,
            "run_rc": 0,
            "stderr": c_txt + "\n[TIMEOUT]",
            "compile_cmd": shell_join(cmd),
        }

    if c_rc != 0:
        return {
            "passed": False,
            "compile_rc": c_rc,
            "run_rc": 0,
            "stderr": c_txt,
            "compile_cmd": shell_join(cmd),
        }

    r_rc, r_out, r_err, r_timed = run_capture([f"./{bin_name}"], timeout_s=timeout, cwd=work_dir)
    r_txt = trim((r_out or "") + ("\n" + r_err if r_err else ""))
    ub_hit = contains_any(r_txt, SAN_PATTERNS)
    passed = (r_rc == 0) and (not r_timed) and (not ub_hit)

    return {
        "passed": passed,
        "compile_rc": c_rc,
        "run_rc": (124 if r_timed else r_rc),
        "stderr": r_txt,
        "compile_cmd": shell_join(cmd),
    }

def compile_stage(srcs: List[str], work_dir: str, compiler: str, std: str, opt: str, out_name: str, timeout: int) -> Dict:
    cmd = [
        compiler,
        *srcs,
        f"-std={std}",
        "-I.",
        opt,
        "-w",
        "-pipe",
        "-o",
        out_name,
    ]
    rc, out, err, timed = run_capture(cmd, timeout_s=timeout, cwd=work_dir)
    txt = trim((out or "") + ("\n" + err if err else ""))
    crash_like = contains_any(txt, ICE_PATTERNS)
    return {
        "cmd": shell_join(cmd),
        "rc": rc,
        "out": txt,
        "timed_out": timed,
        "crash_like": crash_like,
        "ok": (rc == 0 and not timed and not crash_like),
    }

def run_once(bin_name: str, work_dir: str, timeout: int) -> Dict:
    rc, out, err, timed = run_capture([f"./{bin_name}"], timeout_s=timeout, cwd=work_dir)
    return {
        "rc": rc,
        "stdout": trim(out),
        "stderr": trim(err),
        "timed_out": timed,
    }

def main():
    ap = argparse.ArgumentParser("Directory-aware C++ adapter for YARPGen")
    ap.add_argument("--input-dir", required=True)
    ap.add_argument("--output-json", required=True)
    ap.add_argument("--compiler", default="g++")
    ap.add_argument("--std", default="c++17")
    ap.add_argument("--timeout", type=int, default=30)
    args = ap.parse_args()

    work_dir = args.input_dir
    srcs = find_sources(work_dir)
    if not srcs:
        raise SystemExit("No .cpp/.cc/.cxx files found in input dir")

    cpp_r = cppcheck_stage(srcs, work_dir, args.std, args.timeout)
    tidy_r = clang_tidy_stage(srcs, work_dir, args.std, args.timeout)
    san_r = sanitizer_stage(srcs, work_dir, args.compiler, args.std, args.timeout)

    out = {
        "validation": {
            "cppcheck": cpp_r,
            "clang_tidy": tidy_r,
            "sanitizer_gate": san_r,
        },
        "oracle": {
            "compile_O0": 1,
            "compile_O2": 1,
            "outputs_match": False,
        },
        "final": {
            "classification": "UNKNOWN",
            "bug_kind": "",
        }
    }

    if not san_r["passed"]:
        out["final"]["classification"] = "REJECT_SANITIZER"
        with open(args.output_json, "w", encoding="utf-8") as f:
            json.dump(out, f, indent=2)
        return

    c0 = compile_stage(srcs, work_dir, args.compiler, args.std, "-O0", "o0.out", args.timeout)
    c2 = compile_stage(srcs, work_dir, args.compiler, args.std, "-O2", "o2.out", args.timeout)

    out["oracle"]["compile_O0"] = c0["rc"]
    out["oracle"]["compile_O2"] = c2["rc"]

    if c0["crash_like"] or c2["crash_like"]:
        out["final"]["classification"] = "COMPILER_CRASH"
        out["final"]["bug_kind"] = "CRASH"
    elif c0["timed_out"] or c2["timed_out"]:
        out["final"]["classification"] = "COMPILER_HANG"
        out["final"]["bug_kind"] = "TIMEOUT"
    elif not c0["ok"] or not c2["ok"]:
        out["final"]["classification"] = "REJECT_NORMAL_COMPILE_FAIL"
    else:
        r0 = run_once("o0.out", work_dir, args.timeout)
        r2 = run_once("o2.out", work_dir, args.timeout)

        if r0["timed_out"] or r2["timed_out"]:
            out["final"]["classification"] = "PROGRAM_HANG"
            out["final"]["bug_kind"] = "TIMEOUT"
        else:
            outputs_match = (
                r0["rc"] == r2["rc"]
                and r0["stdout"] == r2["stdout"]
                and r0["stderr"] == r2["stderr"]
            )
            out["oracle"]["outputs_match"] = outputs_match
            if outputs_match:
                out["final"]["classification"] = "VALID_ORACLE_PASS"
            else:
                out["final"]["classification"] = "MISCOMPILATION_DIFF"
                out["final"]["bug_kind"] = "DIFF"

    with open(args.output_json, "w", encoding="utf-8") as f:
        json.dump(out, f, indent=2)

if __name__ == "__main__":
    main()
