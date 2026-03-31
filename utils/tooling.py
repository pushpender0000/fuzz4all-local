import platform
import shutil
import subprocess
from typing import List, Tuple, Optional

def trim_output(s: str, limit: int = 8000) -> str:
    s = s or ""
    s = s.strip()
    if not s:
        return ""
    if len(s) <= limit:
        return s
    head = s[: int(limit * 0.6)]
    tail = s[-int(limit * 0.4):]
    return head + "\n...\n" + tail

def cmd_to_str(cmd: List[str]) -> str:
    def q(x: str) -> str:
        if x == "":
            return "''"
        if any(c in x for c in " \t\n\"'\\$`"):
            return "'" + x.replace("'", "'\"'\"'") + "'"
        return x
    return " ".join(q(c) for c in cmd)

def run_capture(cmd: List[str], timeout_s: int, cwd: Optional[str] = None) -> Tuple[int, str, str, bool]:
    """
    Returns: (rc, stdout, stderr, timed_out)
    FileNotFound -> rc=127 + stderr message.
    """
    try:
        p = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,                 # normal path returns str
            timeout=timeout_s,
            cwd=cwd,
        )
        return p.returncode, (p.stdout or ""), (p.stderr or ""), False

    except subprocess.TimeoutExpired as e:
        out = e.stdout or ""
        err = e.stderr or ""

        # ---- FIX: stdout/stderr may be bytes on TimeoutExpired ----
        if isinstance(out, bytes):
            out = out.decode("utf-8", errors="replace")
        if isinstance(err, bytes):
            err = err.decode("utf-8", errors="replace")

        err = (err or "") + "\n[TIMEOUT]"
        return 124, out, err, True

    except FileNotFoundError as e:
        return 127, "", f"[ERROR] Command not found: {cmd[0]} ({e})", False

def get_os_string() -> str:
    try:
        return platform.platform()
    except Exception:
        return "N/A"

def resolve_tool_path(tool: str) -> str:
    try:
        p = shutil.which(tool)
        return p or tool or "N/A"
    except Exception:
        return tool or "N/A"

def compiler_version_line(compiler_path: str, timeout_s: int = 10) -> str:
    if not compiler_path:
        return "N/A"
    rc, out, err, _ = run_capture([compiler_path, "--version"], timeout_s=timeout_s)
    txt = (out.strip() or err.strip() or "").splitlines()
    if rc == 127:
        return "N/A"
    return txt[0].strip() if txt else "N/A"

def looks_like_ub(text: str) -> bool:
    low = (text or "").lower()
    needles = [
        "undefined behavior",
        "undefined behaviour",
        "runtime error:",
        "ubsan",
        "undefinedbehaviorsanitizer",
        "addresssanitizer",
        "use-of-uninitialized",
        "uninitialized",
        "out of bounds",
        "null pointer",
        "division by zero",
        "signed integer overflow",
        "shift exponent",
        "shift count",
        "misaligned",
        "heap-buffer-overflow",
        "stack-buffer-overflow",
        "use-after-free",
        "double free",
    ]
    return any(n in low for n in needles)
