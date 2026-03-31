import os

SUBDIRS = ["docs", "autoprompt", "corpus", "logs", "bugs", "seeds"]

def ensure_dirs(base: str) -> None:
    os.makedirs(base, exist_ok=True)
    for s in SUBDIRS:
        os.makedirs(os.path.join(base, s), exist_ok=True)

def zid(i: int) -> str:
    return str(i).zfill(6)
