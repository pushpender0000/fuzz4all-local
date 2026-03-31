#!/usr/bin/env python3
import argparse
import json
import os
import sys

REPO_ROOT = os.path.dirname(os.path.abspath(__file__))
if REPO_ROOT not in sys.path:
    sys.path.insert(0, REPO_ROOT)

from targets import GppCppTarget

def find_sources(work_dir: str):
    srcs = []
    for name in sorted(os.listdir(work_dir)):
        p = os.path.join(work_dir, name)
        if os.path.isfile(p) and name.endswith((".cpp", ".cc", ".cxx")):
            srcs.append(p)
    return srcs

def main():
    ap = argparse.ArgumentParser("Run only my C++ pipeline on one YARPGen test dir")
    ap.add_argument("--input-dir", required=True)
    ap.add_argument("--output-json", required=True)
    ap.add_argument("--compiler", default="g++")
    ap.add_argument("--std", default="c++17")
    ap.add_argument("--timeout", type=int, default=30)
    args = ap.parse_args()

    srcs = find_sources(args.input_dir)
    if not srcs:
        raise SystemExit("No .cpp/.cc/.cxx files found")

    combined = []
    for s in srcs:
        with open(s, "r", encoding="utf-8") as f:
            combined.append(f"// FILE: {os.path.basename(s)}\n" + f.read())
    program_text = "\n\n".join(combined)

    target = GppCppTarget(
        compiler=args.compiler,
        std=args.std,
        extra_flags="",
    )

    target.oracle(program_text, timeout_s=args.timeout)
    report = getattr(target, "last_report", None) or {}

    static_scan = report.get("static_ub_scan", {}) or {}
    sanitizer = report.get("sanitizer_gate", {}) or {}
    normal = report.get("normal_compilation", {}) or {}
    execution = report.get("execution_check", {}) or {}
    finding = report.get("finding", {}) or {}

    cppcheck_rc = int(static_scan.get("cppcheck_rc", 1))
    clang_tidy_rc = int(static_scan.get("clang_tidy_rc", 1))
    static_scan_passed = bool(static_scan.get("static_scan_passed", False))

    sanitizer_passed = bool(sanitizer.get("sanitizer_passed", False))
    sanitizer_compile_rc = int(sanitizer.get("sanitizer_compile_rc", 1))
    sanitizer_run_rc = int(sanitizer.get("sanitizer_run_rc", 1))
    sanitizer_stderr = sanitizer.get("sanitizer_stderr", "")

    compile_o0_rc = int(normal.get("compile_O0_rc", 1))
    compile_o2_rc = int(normal.get("compile_O2_rc", 1))

    run_o0_timed = bool(execution.get("run_O0_timed_out", False))
    run_o2_timed = bool(execution.get("run_O2_timed_out", False))
    outputs_match = bool(execution.get("outputs_match", False))

    finding_kind = str(finding.get("finding_kind", "NONE")).upper()

    out = {
        "validation": {
            "cppcheck": {
                "passed": (cppcheck_rc == 0),
                "rc": cppcheck_rc,
                "stdout": "",
                "stderr": static_scan.get("cppcheck_output", ""),
                "timed_out": False,
                "cmd": "",
            },
            "clang_tidy": {
                "passed": (clang_tidy_rc == 0),
                "rc": clang_tidy_rc,
                "stdout": "",
                "stderr": static_scan.get("clang_tidy_output", ""),
                "timed_out": False,
                "cmd": "",
            },
            "sanitizer_gate": {
                "passed": sanitizer_passed,
                "compile_rc": sanitizer_compile_rc,
                "run_rc": sanitizer_run_rc,
                "stderr": sanitizer_stderr,
            },
        },
        "oracle": {
            "compile_O0": compile_o0_rc,
            "compile_O2": compile_o2_rc,
            "outputs_match": outputs_match,
        },
        "final": {
            "classification": "UNKNOWN",
            "bug_kind": "",
        }
    }

    if finding_kind == "CRASH":
        out["final"]["classification"] = "COMPILER_CRASH"
        out["final"]["bug_kind"] = "CRASH"
    elif finding_kind == "TIMEOUT":
        out["final"]["classification"] = "COMPILER_HANG"
        out["final"]["bug_kind"] = "TIMEOUT"
    elif not sanitizer_passed:
        out["final"]["classification"] = "REJECT_SANITIZER"
    elif run_o0_timed or run_o2_timed:
        out["final"]["classification"] = "PROGRAM_HANG"
        out["final"]["bug_kind"] = "TIMEOUT"
    elif finding_kind == "DIFF":
        out["final"]["classification"] = "MISCOMPILATION_DIFF"
        out["final"]["bug_kind"] = "DIFF"
    elif compile_o0_rc != 0 or compile_o2_rc != 0:
        out["final"]["classification"] = "REJECT_NORMAL_COMPILE_FAIL"
    elif static_scan_passed and sanitizer_passed and compile_o0_rc == 0 and compile_o2_rc == 0 and outputs_match:
        out["final"]["classification"] = "VALID_ORACLE_PASS"
    elif outputs_match:
        out["final"]["classification"] = "VALID_ORACLE_PASS"
    else:
        out["final"]["classification"] = "REJECT_NORMAL_COMPILE_FAIL"

    with open(args.output_json, "w", encoding="utf-8") as f:
        json.dump(out, f, indent=2)

if __name__ == "__main__":
    main()
