#!/usr/bin/env python3
"""Batch OCR for alg_intro_2e section PDFs using ocrmypdf."""

from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
from pathlib import Path


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(
      description="Run ocrmypdf over all PDFs in a directory.")
  parser.add_argument(
      "--src",
      default="alg_intro_2e_sections",
      help="Source directory of PDFs (default: alg_intro_2e_sections).")
  parser.add_argument(
      "--dst",
      default="alg_intro_2e_sections_ocr",
      help="Output directory for OCRed PDFs (default: alg_intro_2e_sections_ocr).")
  parser.add_argument(
      "--lang",
      default="chi_sim+eng",
      help="Languages passed to ocrmypdf -l (default: chi_sim+eng).")
  parser.add_argument(
      "--jobs",
      type=int,
      default=4,
      help="Worker threads passed to ocrmypdf --jobs (default: 4).")
  parser.add_argument(
      "--redo",
      action="store_true",
      help="Re-OCR even if output exists (otherwise skip existing files).")
  parser.add_argument(
      "--ocrmypdf",
      default=None,
      help="Path to ocrmypdf binary (default: resolve from PATH).")
  return parser.parse_args()


def main() -> int:
  args = parse_args()
  base = Path(__file__).resolve().parent
  src_dir = (base / args.src).resolve()
  dst_dir = (base / args.dst).resolve()

  ocrmypdf = args.ocrmypdf or shutil.which("ocrmypdf")
  if not ocrmypdf:
    print("ocrmypdf not found in PATH; please ensure it is installed.", file=sys.stderr)
    return 1

  if not src_dir.is_dir():
    print(f"Source directory not found: {src_dir}", file=sys.stderr)
    return 1

  dst_dir.mkdir(parents=True, exist_ok=True)

  pdfs = sorted(src_dir.glob("*.pdf"))
  if not pdfs:
    print(f"No PDFs found in {src_dir}", file=sys.stderr)
    return 1

  failures: list[str] = []
  for pdf in pdfs:
    out = dst_dir / pdf.name
    if out.exists() and not args.redo:
      print(f"Skip existing {out.name}")
      continue
    if out.exists():
      out.unlink()

    print(f"OCR {pdf.name} -> {out}")
    cmd = [
        ocrmypdf,
        "--force-ocr",
        "--output-type",
        "pdf",
        "--deskew",
        "--rotate-pages",
        "--jobs",
        str(args.jobs),
        "-l",
        args.lang,
        str(pdf),
        str(out),
    ]
    result = subprocess.run(cmd)
    if result.returncode != 0:
      failures.append(pdf.name)

  if failures:
    print("Failed files:", ", ".join(failures), file=sys.stderr)
    return 1

  print(f"Done. OCR output in {dst_dir}")
  return 0


if __name__ == "__main__":
  sys.exit(main())
