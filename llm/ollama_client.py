import json
import requests

def ollama_generate(model: str, prompt: str, temperature: float, num_predict: int, timeout_s: int = 900) -> str:
    """
    Streaming /api/generate client for Ollama.
    Returns concatenated response text.
    """
    payload = {
        "model": model,
        "prompt": prompt,
        "options": {
            "temperature": temperature,
            "num_predict": num_predict,
        },
        "stream": True,
    }
    resp = requests.post("http://127.0.0.1:11434/api/generate", json=payload, timeout=timeout_s)
    resp.raise_for_status()

    out = ""
    for line in resp.iter_lines():
        if not line:
            continue
        j = json.loads(line.decode("utf-8"))
        out += j.get("response", "")
    return out
