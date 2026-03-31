import os
from typing import List

from llm.ollama_client import ollama_generate

def autoprompt_candidates(model: str, docs: str, instruction: str, k: int) -> List[str]:
    cands: List[str] = []
    print("[AUTO] Generating greedy distilled prompt...")
    p0 = ollama_generate(model, docs + "\n\n" + instruction, temperature=0.0, num_predict=900)
    cands.append(p0.strip())

    for i in range(1, k):
        print(f"[AUTO] Generating diverse prompt {i+1}...")
        instr_i = instruction + f"\nRewrite variation #{i+1} with a different structure and more fuzzing-relevant corner cases."
        pi = ollama_generate(model, docs + "\n\n" + instr_i, temperature=0.7, num_predict=900)
        cands.append(pi.strip())

    return cands

def select_best_prompt(out_base: str, model: str, target, docs_all: str, k: int, score_snips: int, timeout_s: int):
    instruction = target.autoprompt_instruction()
    cands = autoprompt_candidates(model, docs_all, instruction, k)

    ap_dir = os.path.join(out_base, "autoprompt")
    for i, c in enumerate(cands):
        with open(os.path.join(ap_dir, f"candidate_{i}.txt"), "w", encoding="utf-8") as f:
            f.write(c)

    best_i, best_s = 0, -1
    for i, cand in enumerate(cands):
        print(f"\n[SCORING] Prompt {i+1}/{k} ...")
        valid = 0
        for _ in range(score_snips):
            gen_prompt = cand.strip() + "\n\n" + target.build_generation_rules()
            out = ollama_generate(model, gen_prompt, temperature=0.6, num_predict=1400)
            prog = target.extract_program(out)
            _, r0, r1 = target.oracle(prog, timeout_s=timeout_s)
            if target.is_valid(r0, r1):
                valid += 1

        print(f"[SCORING] Score = {valid}/{score_snips}")
        if valid > best_s:
            best_s, best_i = valid, i

    best = cands[best_i]
    with open(os.path.join(ap_dir, "best_prompt.txt"), "w", encoding="utf-8") as f:
        f.write(best)

    print("\n==============================")
    print(" BEST PROMPT SELECTED")
    print("==============================")
    print(f"Index: {best_i}, score: {best_s}/{score_snips}\n")
    return best
