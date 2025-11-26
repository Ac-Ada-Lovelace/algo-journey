#!/usr/bin/env python3
import json
import sys
from pathlib import Path


def collect_files(node):
    kind = node.get("kind")
    if kind == "FILE":
        return [node.get("name", "").strip()]
    files = []
    for child in node.get("children", []):
        files.extend(collect_files(child))
    return [name for name in files if name]


def chapter_sections(chapter):
    sections = []
    general = []
    for child in chapter.get("children", []):
        if child.get("kind") == "FILE":
            general.append(child.get("name", "").strip())
        elif child.get("kind") == "FOLDER":
            files = collect_files(child)
            if files:
                sections.append((child.get("name", "").strip(), files))
    if general:
        sections.insert(0, ("General", general))
    return sections


def to_markdown(src, dest):
    with open(src, "r", encoding="utf-8") as f:
        data = json.load(f)

    out_lines = []
    for chapter in data.get("children", []):
        chapter_name = chapter.get("name", "").strip()
        if not chapter_name:
            continue
        out_lines.append(f"# {chapter_name}")
        sections = chapter_sections(chapter)
        for sec_name, problems in sections:
            out_lines.append(f"## {sec_name}")
            for prob in problems:
                out_lines.append(f"### {prob}")
            out_lines.append("")  # blank line between sections
        out_lines.append("")  # blank line between chapters

    Path(dest).write_text("\n".join(out_lines).rstrip() + "\n", encoding="utf-8")


def main():
    if len(sys.argv) != 3:
        print("Usage: catalog_to_md.py <input_json> <output_md>")
        return 1
    src, dest = sys.argv[1], sys.argv[2]
    to_markdown(src, dest)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
