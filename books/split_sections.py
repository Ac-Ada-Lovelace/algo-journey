import json
import re
import subprocess
from pathlib import Path

BOOKS = [
    {
        "path": Path("books/算法竞赛入门经典（第2版） (刘汝佳) (Z-Library).pdf"),
        "out_dir": Path("books/split/alg_intro_2e_sections"),
    },
    {
        "path": Path("books/陈锋 - 2021 - 算法竞赛入门经典 算法实现 算法艺术与信息学竞赛.pdf"),
        "out_dir": Path("books/split/chenfeng_2021_sections"),
    },
]


def run(cmd):
    return subprocess.check_output(cmd, text=True)


def safe_title(title: str, max_len: int = 120) -> str:
    title = title.strip()
    title = re.sub(r'[\\/:*?"<>|]', "_", title)
    title = re.sub(r"\s+", "_", title)
    title = re.sub(r"_+", "_", title).strip("_")
    return title[:max_len] if len(title) > max_len else title


def load_outlines(pdf: Path):
    data = run(["qpdf", "--json", "--json-key=outlines", str(pdf), "-"])
    return json.loads(data).get("outlines", [])


def page_count(pdf: Path) -> int:
    info = run(["pdfinfo", str(pdf)])
    for line in info.splitlines():
        if line.startswith("Pages:"):
            return int(line.split(":")[1].strip())
    raise RuntimeError(f"Page count not found for {pdf}")


def flatten_outlines(items, depth=1, acc=None):
    if acc is None:
        acc = []
    for bm in items:
        acc.append(
            {
                "title": bm.get("title", "untitled"),
                "page": bm.get("destpageposfrom1"),
                "depth": depth,
            }
        )
        kids = bm.get("kids") or []
        flatten_outlines(kids, depth + 1, acc)
    return acc


def level_two_sections(outlines):
    flat = flatten_outlines(outlines, 1, [])
    sections = []
    seen = set()
    for bm in flat:
        if bm["depth"] != 2:
            continue
        page = bm.get("page")
        if page is None:
            continue
        page_no = int(page)
        if page_no in seen:
            continue
        seen.add(page_no)
        sections.append({"title": bm["title"], "page": page_no})
    sections.sort(key=lambda x: x["page"])
    return sections


def split_sections(pdf: Path, out_dir: Path):
    outlines = load_outlines(pdf)
    sections = level_two_sections(outlines)
    if not sections:
        print(f"[warn] No level-2 outlines found in {pdf}")
        return
    total_pages = page_count(pdf)
    out_dir.mkdir(parents=True, exist_ok=True)

    for idx, sec in enumerate(sections):
        start = sec["page"]
        end = sections[idx + 1]["page"] - 1 if idx + 1 < len(sections) else total_pages
        if end < start:
            print(f"[skip] invalid range {start}-{end} for {sec['title']}")
            continue
        fname = f"{idx+1:03d}_{safe_title(sec['title']) or 'section'}_{start}-{end}.pdf"
        out_file = out_dir / fname
        page_spec = f"{start}-{end}" if start != end else str(start)
        cmd = [
            "qpdf",
            str(pdf),
            "--pages",
            str(pdf),
            page_spec,
            "--",
            str(out_file),
        ]
        print(f"[split] {sec['title']} -> {out_file.name} ({page_spec})")
        subprocess.run(cmd, check=True)


def main():
    for book in BOOKS:
        pdf = book["path"]
        out_dir = book["out_dir"]
        if not pdf.exists():
            print(f"[warn] Missing: {pdf}")
            continue
        split_sections(pdf, out_dir)


if __name__ == "__main__":
    main()
