#!/usr/bin/env bash
set -euo pipefail

SRC_DIR="split/alg_intro_2e_sections"
OUT_DIR="split/alg_intro_2e_sections_ocr"
LANGS="chi_sim+eng"
DPI=300

command -v pdftoppm >/dev/null 2>&1 || {
  echo "pdftoppm not found" >&2
  exit 1
}

command -v tesseract >/dev/null 2>&1 || {
  echo "tesseract not found" >&2
  exit 1
}

command -v convert >/dev/null 2>&1 || {
  echo "ImageMagick convert not found" >&2
  exit 1
}

command -v tiffcp >/dev/null 2>&1 || {
  echo "tiffcp not found (from libtiff)" >&2
  exit 1
}

mkdir -p "$OUT_DIR"

shopt -s nullglob
pdfs=("$SRC_DIR"/*.pdf)
if [ ${#pdfs[@]} -eq 0 ]; then
  echo "No PDF files found in $SRC_DIR" >&2
  exit 1
fi

for pdf in "${pdfs[@]}"; do
  base=$(basename "$pdf" .pdf)
  out="$OUT_DIR/$base.pdf"
  if [ -f "$out" ]; then
    echo "Skip existing $out"
    continue
  fi

  tmpdir=$(mktemp -d)
  cleanup() {
    rm -rf "$tmpdir"
  }
  trap cleanup EXIT INT TERM

  echo "Convert $pdf -> images at $tmpdir"
  pdftoppm -r "$DPI" -png "$pdf" "$tmpdir/page"
  mapfile -t imgs < <(printf "%s\n" "$tmpdir"/page-*.png | sort -V)
  if [ ${#imgs[@]} -eq 0 ] || [ ! -f "${imgs[0]}" ]; then
    echo "No images generated for $pdf" >&2
    cleanup
    trap - EXIT INT TERM
    exit 1
  fi

  echo "Bundle images -> multipage TIFF"
  convert "${imgs[@]}" "$tmpdir/pages.tif"

  echo "OCR -> $out"
  tesseract "$tmpdir/pages.tif" "$tmpdir/out" -l "$LANGS" pdf

  mv "$tmpdir/out.pdf" "$out"

  cleanup
  trap - EXIT INT TERM
done

echo "Done. Output in $OUT_DIR"
