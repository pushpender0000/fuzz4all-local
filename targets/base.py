from dataclasses import dataclass
from typing import Optional, Tuple

@dataclass
class RunResult:
    ok: bool
    rc: int
    stdout: str
    stderr: str
    timed_out: bool
    crash_like: bool

@dataclass
class Finding:
    kind: str  # "CRASH", "TIMEOUT", "DIFF", "NONE"
    details: str

class Target:
    name: str = "base"
    file_ext: str = ".txt"

    # populated by c/cpp targets per input (JSON schema requested)
    last_report: Optional[dict] = None

    def autoprompt_instruction(self) -> str:
        raise NotImplementedError

    def build_generation_rules(self) -> str:
        raise NotImplementedError

    def extract_program(self, llm_text: str) -> str:
        return llm_text.strip()

    def fence_lang(self) -> str:
        return ""

    def build_fuzz_prompt(self, base_prompt: str, strategy_text: str, example: Optional[str]) -> str:
        rules = self.build_generation_rules()
        if example is None:
            return base_prompt.strip() + "\n\n" + strategy_text + "\n\n" + rules

        lang = self.fence_lang().strip()
        fence = f"```{lang}\n{example.strip()}\n```" if lang else f"```\n{example.strip()}\n```"
        return (
            base_prompt.strip()
            + "\n\n[EXAMPLE INPUT]\n"
            + fence
            + "\n\n"
            + strategy_text
            + "\n\n"
            + rules
        )

    def oracle(self, program_text: str, timeout_s: int) -> Tuple[Finding, RunResult, Optional[RunResult]]:
        raise NotImplementedError

    def is_valid(self, run0: RunResult, run1: Optional[RunResult]) -> bool:
        raise NotImplementedError

    def complexity(self, program_text: str) -> int:
        return 0
