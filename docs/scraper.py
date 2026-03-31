import requests
from bs4 import BeautifulSoup

def scrape_and_clean(url: str, raw_path: str, clean_path: str) -> str:
    print(f"[SCRAPE] Downloading: {url}")
    r = requests.get(url, timeout=40)
    r.raise_for_status()
    html = r.text

    with open(raw_path, "w", encoding="utf-8") as f:
        f.write(html)

    soup = BeautifulSoup(html, "lxml")
    for tag in soup(["script", "style", "noscript", "header", "footer", "nav"]):
        tag.decompose()

    main = soup.find("div", {"id": "mw-content-text"}) or soup.body
    text = main.get_text(separator="\n") if main else soup.get_text(separator="\n")

    lines = [ln.strip() for ln in text.splitlines() if ln.strip()]
    clean = "\n".join(lines)

    with open(clean_path, "w", encoding="utf-8") as f:
        f.write(clean)

    print(f"[SCRAPE] Clean docs saved to: {clean_path}")
    return clean
