import os
import json
import random
import shutil
import time
from typing import List, Optional

from llm.ollama_client import ollama_generate
from utils.io import zid

STRATEGIES = {
    "generate-new": (
        "Create a NEW input from scratch that exercises the target and stresses the SUT.\n"
        "Make it more complex than typical examples.\n"
    ),
    "mutate-existing": (
        "Mutate the given example input.\n"
        "Mutation must INCREASE complexity.\n"
        "Do not simplify.\n"
    ),
    "semantic-equiv": (
        "Create a semantically equivalent variant of the example, but syntactically different.\n"
        "Refactor/rewrite without simplifying.\n"
    ),
}

def save_bug(out_base: str, bug_id: str, program_path: str, log0_path: str, log1_path: Optional[str], meta: dict):
    bdir = os.path.join(out_base, "bugs", f"bug_{bug_id}")
    os.makedirs(bdir, exist_ok=True)
    ext = os.path.splitext(program_path)[1]
    # include bug number in input filename
    shutil.copy2(program_path, os.path.join(bdir, f"input_bug_{bug_id}{ext}"))
    shutil.copy2(log0_path, os.path.join(bdir, "run_0.txt"))
    if log1_path:
        shutil.copy2(log1_path, os.path.join(bdir, "run_1.txt"))
    with open(os.path.join(bdir, "report.json"), "w", encoding="utf-8") as f:
        json.dump(meta, f, indent=2)
    print(f"[BUG] Saved to: {bdir}")

def _pct(n: int, d: int) -> float:
    if d <= 0:
        return 0.0
    return (100.0 * float(n) / float(d))

def fuzz_loop(
    out_base: str,
    model: str,
    target,
    base_prompt: str,
    timeout_s: int,
    duration_s: int,
    batch_size: int,
    seed_pool_max: int,
    keep_invalid_threshold: int,
    seed_save_every: int,
):
    corpus_dir = os.path.join(out_base, "corpus")
    logs_dir = os.path.join(out_base, "logs")
    seeds_dir = os.path.join(out_base, "seeds")

    valid_seeds: List[str] = []
    interesting_invalid: List[str] = []

    next_id = 0
    bug_counter = 0
    seed_saved = 0

    # NEW: counters for requested percentage metrics
    total_inputs = 0
    static_passed = 0
    sanitizer_passed = 0
    valid_inputs = 0
    miscomp_bugs = 0
    crash_timeout_bugs = 0

    start = time.time()
    end = start + duration_s

    print("[FUZZ] Starting fuzz loop ...")
    print(f"[FUZZ] Duration={duration_s}s (~{duration_s/3600:.2f} hours), batch_size={batch_size}")

    it = 0
    while time.time() < end:
        it += 1

        if it == 1 or (not valid_seeds and not interesting_invalid):
            strategy_name = "generate-new"
            example = None
        else:
            pool = valid_seeds[-seed_pool_max:] if valid_seeds else []
            if not pool:
                pool = interesting_invalid[-seed_pool_max:]
            example = random.choice(pool) if pool else None

            if example is None:
                strategy_name = "generate-new"
            else:
                strategy_name = random.choices(
                    ["generate-new", "mutate-existing", "semantic-equiv"],
                    weights=[0.15, 0.55, 0.30],
                    k=1
                )[0]

        strategy_text = STRATEGIES[strategy_name]
        remaining = max(0, int(end - time.time()))
        print(f"\n[FUZZ] Iteration {it} | remaining~{remaining}s | strategy={strategy_name} | example={'yes' if example else 'no'}")

        fuzz_prompt = target.build_fuzz_prompt(base_prompt, strategy_text, example)

        for _ in range(batch_size):
            if time.time() >= end:
                break

            fid = zid(next_id)
            next_id += 1
            total_inputs += 1

            raw = ollama_generate(model, fuzz_prompt, temperature=0.85, num_predict=1600)
            prog = target.extract_program(raw)

            program_path = os.path.join(corpus_dir, f"{fid}{target.file_ext}")
            with open(program_path, "w", encoding="utf-8") as f:
                f.write(prog)

            finding, r0, r1 = target.oracle(prog, timeout_s=timeout_s)

            log0 = os.path.join(logs_dir, f"{fid}.run0.txt")
            with open(log0, "w", encoding="utf-8") as f:
                f.write(f"rc={r0.rc} ok={r0.ok} timeout={r0.timed_out} crash_like={r0.crash_like}\n\n")
                f.write("==== STDOUT ====\n" + (r0.stdout or "") + "\n")
                f.write("==== STDERR ====\n" + (r0.stderr or "") + "\n")

            log1 = None
            if r1 is not None:
                log1 = os.path.join(logs_dir, f"{fid}.run1.txt")
                with open(log1, "w", encoding="utf-8") as f:
                    f.write(f"rc={r1.rc} ok={r1.ok} timeout={r1.timed_out} crash_like={r1.crash_like}\n\n")
                    f.write("==== STDOUT ====\n" + (r1.stdout or "") + "\n")
                    f.write("==== STDERR ====\n" + (r1.stderr or "") + "\n")

            if target.name in ("c", "cpp"):
                meta = getattr(target, "last_report", None) or {}
                if "input_identity" not in meta:
                    meta["input_identity"] = {"id": fid, "target": target.name, "source_file": os.path.basename(program_path)}
                meta["input_identity"]["id"] = fid
                meta["input_identity"]["target"] = target.name
                meta["input_identity"]["source_file"] = os.path.basename(program_path)

                # NEW: update counters from report booleans when present
                try:
                    if bool(meta.get("static_ub_scan", {}).get("static_scan_passed", False)):
                        static_passed += 1
                    if bool(meta.get("sanitizer_gate", {}).get("sanitizer_passed", False)):
                        sanitizer_passed += 1
                except Exception:
                    pass

                with open(os.path.join(logs_dir, f"{fid}.meta.json"), "w", encoding="utf-8") as f:
                    json.dump(meta, f, indent=2)
            else:
                meta = {
                    "id": fid,
                    "iteration": it,
                    "strategy": strategy_name,
                    "has_example": example is not None,
                    "target": target.name,
                    "finding": {"kind": finding.kind, "details": finding.details},
                    "run0": {"ok": r0.ok, "rc": r0.rc, "timeout": r0.timed_out, "crash_like": r0.crash_like},
                    "run1": None if r1 is None else {"ok": r1.ok, "rc": r1.rc, "timeout": r1.timed_out, "crash_like": r1.crash_like},
                    "complexity_score": target.complexity(prog),
                    "timestamp_unix": int(time.time()),
                }
                with open(os.path.join(logs_dir, f"{fid}.meta.json"), "w", encoding="utf-8") as f:
                    json.dump(meta, f, indent=2)

            # NEW: treat DIFF as compiler bug too
            if finding.kind in ("CRASH", "TIMEOUT", "DIFF"):
                save_bug(out_base, zid(bug_counter), program_path, log0, log1, meta)
                if finding.kind == "DIFF":
                    miscomp_bugs += 1
                else:
                    crash_timeout_bugs += 1
                bug_counter += 1

            is_valid = target.is_valid(r0, r1)
            if is_valid:
                valid_inputs += 1
                valid_seeds.append(prog)
                if len(valid_seeds) % seed_save_every == 0:
                    sp = os.path.join(seeds_dir, f"valid_seed_{zid(seed_saved)}{target.file_ext}")
                    with open(sp, "w", encoding="utf-8") as f:
                        f.write(prog)
                    seed_saved += 1
            else:
                if target.complexity(prog) >= keep_invalid_threshold:
                    interesting_invalid.append(prog)

    elapsed = int(time.time() - start)

    # Requested % metrics
    pct_valid_inputs = _pct(valid_inputs, total_inputs)
    pct_static_pass = _pct(static_passed, total_inputs)
    pct_static_and_san = _pct(sanitizer_passed, total_inputs)  # sanitizer implies we got past static in this pipeline
    pct_bugs_over_valid = _pct(bug_counter, valid_inputs)

    summary = {
        "elapsed_sec": elapsed,
        "duration_sec": int(duration_s),
        "total_inputs_generated": int(total_inputs),
        "valid_inputs_generated": int(valid_inputs),
        "static_scan_passed": int(static_passed),
        "sanitizer_gate_passed": int(sanitizer_passed),
        "bugs_total": int(bug_counter),
        "bugs_miscompilation_DIFF": int(miscomp_bugs),
        "bugs_crash_or_timeout": int(crash_timeout_bugs),
        "percent_valid_inputs_generated": pct_valid_inputs,
        "percent_static_scan_passed": pct_static_pass,
        "percent_static_and_sanitizer_passed": pct_static_and_san,
        "percent_bugs_out_of_valid_inputs": pct_bugs_over_valid,
        "output_folder": out_base,
    }

    with open(os.path.join(out_base, "summary.json"), "w", encoding="utf-8") as f:
        json.dump(summary, f, indent=2)

    print("\n[DONE] Fuzz loop finished.")
    print(f"[DONE] Elapsed: {elapsed}s (~{elapsed/3600:.2f} hours)")
    print(f"[DONE] Total inputs generated: {total_inputs}")
    print(f"[DONE] Valid seeds collected: {len(valid_seeds)}")
    print(f"[DONE] Interesting invalid retained: {len(interesting_invalid)}")
    print(f"[DONE] Bugs reported: {bug_counter} (DIFF={miscomp_bugs}, CRASH/TIMEOUT={crash_timeout_bugs})")
    print(f"[DONE] Output folder: {out_base}")

    print("\n==============================")
    print(" SUMMARY (Requested Metrics)")
    print("==============================")
    print(f"% valid input generated: {pct_valid_inputs:.2f}% ({valid_inputs}/{total_inputs})")
    print(f"% Cppcheck+clang-tidy pass: {pct_static_pass:.2f}% ({static_passed}/{total_inputs})")
    print(f"% Static + UBSan/ASan gate pass: {pct_static_and_san:.2f}% ({sanitizer_passed}/{total_inputs})")
    print(f"% Total compiler bugs out of total valid seeds: {pct_bugs_over_valid:.2f}% ({bug_counter}/{max(1, valid_inputs)})")
    print(f"[DONE] summary.json written to: {os.path.join(out_base, 'summary.json')}")
