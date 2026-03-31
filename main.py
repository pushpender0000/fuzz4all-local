#!/usr/bin/env python3
import os
import argparse

from utils.io import ensure_dirs
from docs.scraper import scrape_and_clean
from autoprompt.autoprompt import select_best_prompt
from fuzz.loop import fuzz_loop
from targets import GppCppTarget, GccCTarget, Z3SmtTarget

def make_target(args):
    if args.target == "cpp":
        return GppCppTarget(compiler=args.compiler, std=args.std, extra_flags=args.extra_flags)
    if args.target == "c":
        return GccCTarget(compiler=args.compiler, std=args.std, extra_flags=args.extra_flags)
    if args.target == "smt":
        return Z3SmtTarget(solver=args.solver)
    raise ValueError("Unknown target")

def interactive_multiline_prompt() -> str:
    print("\n[MANUAL PROMPT] Paste your base prompt below.")
    print("End input with a single line containing only: EOF\n")
    lines = []
    while True:
        try:
            line = input()
        except EOFError:
            break
        if line.strip() == "EOF":
            break
        lines.append(line)
    prompt = "\n".join(lines).strip()
    if not prompt:
        raise SystemExit("Manual prompt was empty. Please paste a prompt and end with EOF.")
    return prompt

def main():
    ap = argparse.ArgumentParser("Fuzz4All-style local pipeline (Ollama) - DeepSeek Coder v2 default")

    ap.add_argument("--target", choices=["cpp", "c", "smt"], required=True, help="Which SUT type")
    ap.add_argument("--urls", nargs="+", required=True, help="Docs URLs (one or more). Saved under output/docs/")
    ap.add_argument("--target-name", required=True, help="Output folder name under --out-root")
    ap.add_argument("--out-root", default="outputs", help="Root output folder")

    # UPDATED DEFAULT MODEL (DeepSeek Coder v2)
    ap.add_argument("--model", default="deepseek-coder-v2", help="Ollama model name")

    ap.add_argument("--prompt-mode", choices=["auto", "manual"], default="auto",
                    help="auto = autoprompt selection; manual = interactive prompt (no file)")

    ap.add_argument("--num-candidates", type=int, default=4, help="Autoprompt candidate prompts K (default 4)")
    ap.add_argument("--score-snippets", type=int, default=3, help="How many quick samples to score prompts")

    ap.add_argument("--duration-hours", type=float, default=24.0, help="Run fuzzing for N hours (default 24)")
    ap.add_argument("--hours", type=float, default=None, help="Alias for --duration-hours")

    ap.add_argument("--batch-size", type=int, default=3)
    ap.add_argument("--seed-pool-max", type=int, default=80)
    ap.add_argument("--keep-invalid-threshold", type=int, default=35)
    ap.add_argument("--seed-save-every", type=int, default=10)
    ap.add_argument("--timeout", type=int, default=15, help="Timeout seconds per run/compile/execute")

    ap.add_argument("--compiler", default="", help="gcc or g++ path (for c/cpp targets)")
    ap.add_argument("--std", default="", help="c11/c17 OR c++17/c++20/c++23")
    ap.add_argument("--extra-flags", default="", help="Extra flags passed to compiler")
    ap.add_argument("--solver", default="z3", help="SMT solver binary path/name")

    args = ap.parse_args()

    if args.hours is not None:
        args.duration_hours = args.hours

    if args.target in ("c", "cpp"):
        if not args.compiler:
            args.compiler = "gcc" if args.target == "c" else "g++"
        if not args.std:
            args.std = "c11" if args.target == "c" else "c++20"
    else:
        if not args.std:
            args.std = ""

    target = make_target(args)
    out_base = os.path.join(args.out_root, args.target_name)
    ensure_dirs(out_base)

    docs_all = ""
    for i, url in enumerate(args.urls):
        raw = os.path.join(out_base, "docs", f"raw_{i}.html")
        clean = os.path.join(out_base, "docs", f"clean_{i}.txt")
        docs_all += "\n\n" + scrape_and_clean(url, raw, clean)

    if args.prompt_mode == "manual":
        best_prompt = interactive_multiline_prompt()
        with open(os.path.join(out_base, "autoprompt", "best_prompt.txt"), "w", encoding="utf-8") as f:
            f.write(best_prompt)
        print("[PROMPT] Using MANUAL prompt as best_prompt (saved to autoprompt/best_prompt.txt).")
    else:
        best_prompt = select_best_prompt(
            out_base=out_base,
            model=args.model,
            target=target,
            docs_all=docs_all,
            k=args.num_candidates,
            score_snips=args.score_snippets,
            timeout_s=args.timeout,
        )
        print("[PROMPT] Using AUTOPROMPT selected best_prompt.")

    duration_s = int(max(0.01, args.duration_hours) * 3600)
    fuzz_loop(
        out_base=out_base,
        model=args.model,
        target=target,
        base_prompt=best_prompt,
        timeout_s=args.timeout,
        duration_s=duration_s,
        batch_size=args.batch_size,
        seed_pool_max=args.seed_pool_max,
        keep_invalid_threshold=args.keep_invalid_threshold,
        seed_save_every=args.seed_save_every,
    )

if __name__ == "__main__":
    main()
