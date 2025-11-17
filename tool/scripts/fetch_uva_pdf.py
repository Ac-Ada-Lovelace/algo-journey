#!/usr/bin/env python3
"""
Download a UVA problem statement PDF and store it following the repository's
`prac/UVa<ID> <Title>/p<ID>.pdf` layout. If the title is omitted, the script
will search the catalog JSON files at the repository root.
"""

import argparse
import json
import pathlib
import sys
import urllib.error
import urllib.request
from typing import Optional

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
CATALOG_CANDIDATES = [
    "Beginning_Algorithm_Contests.json",
    "Beginning_Algorithm_Contests_(Second_Edition).json",
    "Beginning_Algorithm_Contests_--_Training_Guide.json",
]


def build_uva_url(uva_id: int) -> str:
  group = uva_id // 100
  return f"https://onlinejudge.org/external/{group}/{uva_id}.pdf"


def download_pdf(url: str) -> bytes:
  request = urllib.request.Request(
      url, headers={"User-Agent": "Mozilla/5.0 (Codex PDF fetcher)"})
  with urllib.request.urlopen(request) as response:
    return response.read()


def find_title_in_catalogs(uva_id: int, catalog_root: pathlib.Path) -> Optional[str]:
  pattern = f"{uva_id} - "

  def dfs(node) -> Optional[str]:
    if isinstance(node, dict):
      name = node.get("name", "")
      if isinstance(name, str) and name.startswith(pattern):
        return name.split(" - ", 1)[1].strip()
      children = node.get("children")
      if isinstance(children, list):
        for child in children:
          result = dfs(child)
          if result:
            return result
    elif isinstance(node, list):
      for child in node:
        result = dfs(child)
        if result:
          return result
    return None

  for rel in CATALOG_CANDIDATES:
    path = catalog_root / rel
    if not path.exists():
      continue
    try:
      data = json.loads(path.read_text())
    except json.JSONDecodeError:
      continue
    title = dfs(data)
    if title:
      return title
  return None


def main() -> int:
  parser = argparse.ArgumentParser(
      description="Download a UVA problem PDF into the prac/ directory.")
  parser.add_argument("uva_id", type=int, help="Problem number, e.g. 210")
  parser.add_argument(
      "title",
      nargs="?",
      help="Problem title, e.g. 'Concurrency Simulator'; if omitted the script "
           "will try to read it from catalog JSON files")
  parser.add_argument(
      "--root",
      default="prac",
      help="Root directory for UVA problems (default: %(default)s)")
  parser.add_argument(
      "--catalog-root",
      default=str(REPO_ROOT),
      help="Directory containing catalog JSON files (default: repository root)")
  parser.add_argument(
      "--overwrite",
      action="store_true",
      help="Overwrite an existing PDF if present")
  args = parser.parse_args()

  title = args.title
  if not title:
    catalog_root = pathlib.Path(args.catalog_root)
    title = find_title_in_catalogs(args.uva_id, catalog_root)
    if not title:
      print("[error] 未找到题目标题，请手动提供 title 参数或更新 catalog JSON",
            file=sys.stderr)
      return 1

  folder_name = f"UVa{args.uva_id} {title}"
  folder_path = pathlib.Path(args.root) / folder_name
  folder_path.mkdir(parents=True, exist_ok=True)

  pdf_path = folder_path / f"p{args.uva_id}.pdf"
  if pdf_path.exists() and not args.overwrite:
    print(f"[skip] {pdf_path} 已存在，若需重新下载请使用 --overwrite", file=sys.stderr)
    return 0

  url = build_uva_url(args.uva_id)
  try:
    data = download_pdf(url)
  except urllib.error.HTTPError as exc:
    print(f"[error] 下载失败（HTTP {exc.code}）: {url}", file=sys.stderr)
    return 1
  except urllib.error.URLError as exc:
    print(f"[error] 无法连接 UVA: {exc.reason}", file=sys.stderr)
    return 1

  pdf_path.write_bytes(data)
  print(f"[ok] 已保存 {url} -> {pdf_path}")
  return 0


if __name__ == "__main__":
  sys.exit(main())
