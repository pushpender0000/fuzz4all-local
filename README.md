# Fuzz4All Local Pipeline (DeepSeek Coder v2)

A local Fuzz4All-style fuzzing pipeline for compiler and solver testing using Ollama.

This project bootstraps a local workspace under:

`Fuzzing compiler using Deepseek coder v1/fuzz4all_local`

It supports:
- **C++ compiler fuzzing** with `g++`
- **C compiler fuzzing** with `gcc`
- **Automatic prompt generation** from scraped docs
- **Manual prompt mode** with pasted prompts
- **Static UB screening** using `cppcheck` and `clang-tidy`
- **Sanitizer gate** using `ASan` + `UBSan`
- **Miscompilation detection** by comparing `-O0` and `-O2` outputs
- **Bug triage artifacts** and end-of-run summary metrics

## Features

### Prompt modes
- **Manual mode**: always asks the user to paste a base prompt directly into the terminal
- **Auto mode**: generates prompt candidates from documentation and selects the best one automatically

### Defaults
- Default Ollama model: `deepseek-coder-v2`
- Default prompt candidate count: `4`
- Default fuzzing duration: `24` hours

### Safety and filtering
For C and C++ targets, each generated input goes through:
1. **Static scan** with `cppcheck` and `clang-tidy`
2. **Sanitizer gate** with `-fsanitize=address,undefined`
3. **Normal compilation** under both `-O0` and `-O2`
4. **Execution comparison** between the two builds

This helps filter out invalid or UB-heavy programs before treating output mismatches as likely compiler bugs. :contentReference[oaicite:2]{index=2}

## Project Structure

```text
fuzz4all_local/
├── requirements.txt
├── main.py
├── llm/
│   ├── __init__.py
│   └── ollama_client.py
├── docs/
│   ├── __init__.py
│   └── scraper.py
├── autoprompt/
│   ├── __init__.py
│   └── autoprompt.py
├── fuzz/
│   ├── __init__.py
│   └── loop.py
├── targets/
│   ├── __init__.py
│   ├── base.py
│   ├── gpp_cpp.py
│   ├── gcc_c.py
│   └── z3_smt.py
└── utils/
    ├── __init__.py
    ├── io.py
    ├── complexity.py
    └── tooling.py
