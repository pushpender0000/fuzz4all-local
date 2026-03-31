import os
import re
import shutil
import tempfile
import subprocess
from typing import Optional, Tuple

from targets.base import Target, RunResult, Finding
from utils.complexity import complexity_score_smt2

CRASH_PATTERNS = [
    "segmentation fault",
    "bus error",
    "assertion",
    "abort",
    "stack smashing",
]

def extract_fenced_smt2(text: str) -> str:
    m = re.search(r"```(?:smt2|smtlib2|lisp)?\s*(.*?)```", text, flags=re.DOTALL | re.IGNORECASE)
    return (m.group(1).strip() if m else text.strip())

def _run(cmd, timeout_s: int) -> RunResult:
    try:
        p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=timeout_s, text=True)
        rc = p.returncode
        out = p.stdout or ""
        err = p.stderr or ""
        timed = False
    except subprocess.TimeoutExpired as e:
        rc = 124
        out = (e.stdout or "")
        err = (e.stderr or "") + "\n[TIMEOUT]"
        timed = True

    low = (out + "\n" + err).lower()
    crash_like = any(pat in low for pat in CRASH_PATTERNS)
    ok = (rc == 0) and (not timed) and (not crash_like)
    return RunResult(ok=ok, rc=rc, stdout=out, stderr=err, timed_out=timed, crash_like=crash_like)

class Z3SmtTarget(Target):
    name = "smt"
    file_ext = ".smt2"

    def __init__(self, solver: str = "z3"):
        self.solver = solver

    def fence_lang(self) -> str:
        return "smt2"

    def extract_program(self, llm_text: str) -> str:
        return extract_fenced_smt2(llm_text)

    def autoprompt_instruction(self) -> str:
        return (
            "Summarize relevant SMT-LIB2 syntax, supported theories, and tricky edge cases.\n"
            "This will be used to generate VALID SMT2 scripts to fuzz an SMT solver.\n"
            "Include: declarations, assertions, check-sat usage, corner cases.\n"
        )

    def build_generation_rules(self) -> str:
        return r"""Generate a VALID SMT-LIB2 script to stress an SMT solver.
Hard requirements:
- Output ONLY SMT2 text.
- Must end with: (check-sat) (exit)
- Use at least 2 declarations (declare-const or declare-fun).
- Use at least 3 asserts.
- Include a mix of Int/Real/BitVec/Array if possible.
- Include at least one quantifier (forall/exists) OR nested let.
- Avoid undefined symbols (everything declared).
- Keep <= 120 lines.
Goal: Stress parsing + theory combination + simplification.
"""

    def oracle(self, program_text: str, timeout_s: int) -> Tuple[Finding, RunResult, Optional[RunResult]]:
        tmp = tempfile.mkdtemp(prefix="smt_fuzz_")
        src = os.path.join(tmp, "t.smt2")
        try:
            with open(src, "w", encoding="utf-8") as f:
                f.write(program_text)

            r = _run([self.solver, src], timeout_s)

            if r.crash_like:
                return Finding("CRASH", "Crash-like signature in solver output"), r, None
            if r.timed_out:
                return Finding("TIMEOUT", "Solver timed out (potential hang)"), r, None

            low = (r.stdout + "\n" + r.stderr).lower()
            if "(error" in low or "parse error" in low:
                return Finding("NONE", ""), r, None

            return Finding("NONE", ""), r, None
        finally:
            shutil.rmtree(tmp, ignore_errors=True)

    def is_valid(self, run0: RunResult, run1: Optional[RunResult]) -> bool:
        low = (run0.stdout + "\n" + run0.stderr).lower()
        return run0.ok and (("sat" in low) or ("unsat" in low) or ("unknown" in low)) and ("(error" not in low)

    def complexity(self, program_text: str) -> int:
        return complexity_score_smt2(program_text)
