#!/usr/bin/env python3
"""
Download a UVA problem statement PDF and store it following the repository's
`prac/UVa<ID> <Title>/p<ID>.pdf` layout.
"""

import argparse
import pathlib
import sys
import urllib.error
import urllib.request


def build_uva_url(uva_id: int) -> str:
  group = uva_id // 100
  return f"https://onlinejudge.org/external/{group}/{uva_id}.pdf"


def download_pdf(url: str) -> bytes:
  request = urllib.request.Request(
      url, headers={"User-Agent": "Mozilla/5.0 (Codex PDF fetcher)"})
  with urllib.request.urlopen(request) as response:
    return response.read()


def main() -> int:
  parser = argparse.ArgumentParser(
      description="Download a UVA problem PDF into the prac/ directory.")
  parser.add_argument("uva_id", type=int, help="Problem number, e.g. 210")
  parser.add_argument(
      "title",
      help="Problem title, e.g. 'Concurrency Simulator'; used for folder name")
  parser.add_argument(
      "--root",
      default="prac",
      help="Root directory for UVA problems (default: %(default)s)")
  parser.add_argument(
      "--overwrite",
      action="store_true",
      help="Overwrite an existing PDF if present")
  args = parser.parse_args()

  folder_name = f"UVa{args.uva_id} {args.title}"
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
