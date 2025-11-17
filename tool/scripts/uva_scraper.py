#!/usr/bin/env python3
"""
Fetch UVA Online Judge category pages and extract chapter -> example/exercise links.

Usage:
    python tool/scripts/uva_scraper.py 442 93 827

Pages are cached under tool/cache/cat_<id>.html to avoid repeated downloads.
"""
from __future__ import annotations

import html
import re
import sys
from pathlib import Path
from typing import Dict, List, Set, Tuple
from urllib.request import urlopen

BASE_URL = "https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category={}"
CACHE_DIR = Path(__file__).resolve().parents[1] / "cache"
CACHE_DIR.mkdir(parents=True, exist_ok=True)

Anchor = Tuple[str, str, str]  # (title, url, category_id)
GLOBAL_SKIP = {"0", "442", "93", "827"}


def fetch_category(cat_id: str) -> str:
    cache_file = CACHE_DIR / f"cat_{cat_id}.html"
    if cache_file.exists():
        return cache_file.read_text(encoding="utf-8", errors="replace")
    url = BASE_URL.format(cat_id)
    with urlopen(url) as resp:
        data = resp.read().decode("utf-8", errors="replace")
    cache_file.write_text(data, encoding="utf-8")
    return data


def get_children(cat_id: str, skip_ids: Set[str] | None = None) -> List[Anchor]:
    text = fetch_category(cat_id)
    anchors = re.findall(
        r'<a href="(index\.php\?option=com_onlinejudge&amp;Itemid=8&amp;category=\d+[^"]*)">(.*?)</a>',
        text,
        flags=re.I,
    )
    items: List[Anchor] = []
    seen: Set[Tuple[str, str]] = set()
    skip_ids = (skip_ids or set()).copy()
    skip_ids.add(cat_id)
    skip_ids.update(GLOBAL_SKIP)

    for href, title in anchors:
        title = html.unescape(title).strip()
        if title in {"Root", "Browse Problems"}:
            continue
        full_url = "https://onlinejudge.org/" + html.unescape(href)
        cat_match = re.search(r"category=(\d+)", href)
        if not cat_match:
            continue
        child_id = cat_match.group(1)
        if child_id in skip_ids:
            continue
        key = (child_id, title)
        if key in seen:
            continue
        seen.add(key)
        items.append((title, full_url, child_id))
    return items


def collect_example_paths(cat_id: str) -> Dict[str, List[Tuple[List[str], str]]]:
    """Return mapping chapter_title -> list of ([path], url) for example/exercise links."""
    chapters: Dict[str, List[Tuple[List[str], str]]] = {}
    top_children = [
        child for child in get_children(cat_id) if child[0].startswith(("Chapter", "Volume"))
    ]
    for title, _, child_id in top_children:
        paths: List[Tuple[List[str], str]] = []
        visited: Set[str] = set()

        def dfs(current_id: str, trail: List[str]) -> None:
            if current_id in visited:
                return
            visited.add(current_id)
            for sub_title, sub_url, sub_id in get_children(current_id, skip_ids={cat_id}):
                if sub_title.startswith(("Chapter", "Volume")) and sub_id != current_id:
                    continue
                lowered = sub_title.lower()
                new_trail = trail + [sub_title]
                if "example" in lowered or "exercise" in lowered:
                    paths.append((new_trail, sub_url))
                else:
                    dfs(sub_id, new_trail)

        dfs(child_id, [title])
        chapters[title] = paths
    return chapters


def main(cat_ids: List[str]) -> None:
    for cat_id in cat_ids:
        print(f"== Category {cat_id} ==")
        chapters = collect_example_paths(cat_id)
        for chapter, entries in chapters.items():
            print(f"  {chapter}:")
            if not entries:
                print("    (no example/exercise subcategories found)")
                continue
            for path, url in entries:
                print(f"    - {' > '.join(path)} -> {url}")
        print()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python tool/scripts/uva_scraper.py <category_id> [<category_id> ...]")
        sys.exit(1)
    main(sys.argv[1:])
