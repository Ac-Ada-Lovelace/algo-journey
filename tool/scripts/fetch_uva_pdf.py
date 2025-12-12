#!/usr/bin/env python3
"""
Download a UVA problem statement PDF and store it following the repository's
`prac/UVa<ID> <Title>/p<ID>.pdf` layout. If the title is omitted, the script
will search the catalog JSON files at the repository root.
"""

import argparse
import json
import os
import pathlib
import re
import ssl
import subprocess
import sys
import urllib.error
import urllib.request
from typing import Optional, Tuple

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
CATALOG_CANDIDATES = [
    "Beginning_Algorithm_Contests.json",
    "Beginning_Algorithm_Contests_(Second_Edition).json",
    "Beginning_Algorithm_Contests_--_Training_Guide.json",
]


def build_uva_url(uva_id: int) -> str:
    group = uva_id // 100
    return f"https://onlinejudge.org/external/{group}/{uva_id}.pdf"


def download_pdf(url: str, context: Optional[ssl.SSLContext] = None) -> bytes:
    request = urllib.request.Request(
        url, headers={"User-Agent": "Mozilla/5.0 (Codex PDF fetcher)"}
    )
    with urllib.request.urlopen(request, context=context) as response:
        return response.read()


def download_with_http_fallback(url: str) -> Tuple[bytes, str]:
    try:
        return download_pdf(url), url
    except urllib.error.HTTPError as exc:
        primary_error = f"HTTP {exc.code}"
        primary_exc: Exception = exc
    except urllib.error.URLError as exc:
        primary_error = str(exc.reason)
        primary_exc = exc
    else:
        primary_error = ""
        primary_exc = RuntimeError("unreachable")

    if url.startswith("https://"):
        fallback = "http://" + url[len("https://") :]
        print(
            f"[warn] 通过 HTTPS 下载失败（{primary_error}），尝试 HTTP: {fallback}",
            file=sys.stderr,
        )
        try:
            return download_pdf(fallback), fallback
        except urllib.error.HTTPError as exc:
            print(f"[error] HTTP 回退仍失败（HTTP {exc.code}）: {fallback}", file=sys.stderr)
            raise
        except urllib.error.URLError as exc:
            # 某些环境会强制将 http 重定向到 https，导致继续触发证书错误
            if isinstance(exc.reason, ssl.SSLError):
                insecure_ctx = ssl._create_unverified_context()
                print(
                    "[warn] HTTP 回退被重定向到 HTTPS 且证书无效，尝试忽略证书校验一次",
                    file=sys.stderr,
                )
                return download_pdf(fallback, context=insecure_ctx), fallback
            print(f"[error] 无法连接 UVA: {exc.reason}", file=sys.stderr)
            raise

    raise primary_exc


def find_title_in_catalogs(
    uva_id: int, catalog_root: pathlib.Path
) -> Optional[Tuple[str, Optional[str]]]:
    pattern = f"{uva_id} - "

    def dfs(node) -> Optional[Tuple[str, Optional[str]]]:
        if isinstance(node, dict):
            name = node.get("name", "")
            if isinstance(name, str) and name.startswith(pattern):
                title = name.split(" - ", 1)[1].strip()
                url = node.get("url")
                if not isinstance(url, str):
                    url = None
                return title, url
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
        result = dfs(data)
        if result:
            return result
    return None


def convert_pdf_to_text(pdf_path: pathlib.Path, txt_path: pathlib.Path) -> bool:
    try:
        subprocess.run(
            ["pdftotext", str(pdf_path), str(txt_path)],
            check=True,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
    except FileNotFoundError:
        print("[warn] 未找到 pdftotext，可安装 poppler-utils 后再试", file=sys.stderr)
        return False
    except subprocess.CalledProcessError:
        print("[warn] pdftotext 执行失败，跳过文本提取", file=sys.stderr)
        return False
    return True


SECTION_LABELS = [
    "sample input",
    "sample inputs",
    "sample output",
    "sample outputs",
    "input",
    "inputs",
    "output",
    "outputs",
    "note",
    "notes",
    "explanation",
]


def is_section_header(line: str) -> bool:
    stripped = line.strip().lower()
    if not stripped:
        return False
    return any(stripped.startswith(label) for label in SECTION_LABELS)


def is_footer_line(line: str) -> bool:
    stripped = line.strip().lower()
    if not stripped:
        return False
    if re.fullmatch(r"\d+/\d+", stripped):
        return True
    return "universidad de valladolid" in stripped


def extract_section(lines, start_idx: int) -> Optional[str]:
    i = start_idx + 1
    while i < len(lines) and not lines[i].strip():
        i += 1
    section = []
    while i < len(lines):
        if is_section_header(lines[i]) or is_footer_line(lines[i]):
            break
        section.append(lines[i].rstrip())
        i += 1
    while section and not section[-1].strip():
        section.pop()
    content = "\n".join(section).strip()
    return content if content else None


def extract_samples(text: str) -> Tuple[Optional[str], Optional[str]]:
    clean_text = text.replace("\f", "\n")
    lines = clean_text.splitlines()
    input_idx = output_idx = None
    for idx, line in enumerate(lines):
        lowered = line.strip().lower()
        if input_idx is None and lowered.startswith("sample input"):
            input_idx = idx
        elif output_idx is None and lowered.startswith("sample output"):
            output_idx = idx
    sample_input = extract_section(lines, input_idx) if input_idx is not None else None
    sample_output = (
        extract_section(lines, output_idx) if output_idx is not None else None
    )
    return sample_input, sample_output


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Download a UVA problem PDF into the prac/ directory."
    )
    parser.add_argument("uva_id", type=int, help="Problem number, e.g. 210")
    parser.add_argument(
        "title",
        nargs="?",
        help="Problem title, e.g. 'Concurrency Simulator'; if omitted the script "
        "will try to read it from catalog JSON files",
    )
    parser.add_argument(
        "--root",
        default="prac",
        help="Root directory for UVA problems (default: %(default)s)",
    )
    parser.add_argument(
        "--catalog-root",
        default=str(REPO_ROOT),
        help="Directory containing catalog JSON files (default: repository root)",
    )
    parser.add_argument(
        "--overwrite", action="store_true", help="Overwrite an existing PDF if present"
    )
    parser.add_argument(
        "--problem-url",
        help="Problem statement URL; defaults to catalog entry if available",
    )
    args = parser.parse_args()

    catalog_root = pathlib.Path(args.catalog_root)
    catalog_info = find_title_in_catalogs(args.uva_id, catalog_root)

    title = args.title
    problem_url = args.problem_url
    if not title:
        if not catalog_info:
            print(
                "[error] 未找到题目标题，请手动提供 title 参数或更新 catalog JSON",
                file=sys.stderr,
            )
            return 1
        title = catalog_info[0]
    if not problem_url and catalog_info:
        problem_url = catalog_info[1]

    folder_name = f"UVa{args.uva_id} {title}"
    folder_path = pathlib.Path(args.root) / folder_name
    folder_path.mkdir(parents=True, exist_ok=True)

    pdf_path = folder_path / f"p{args.uva_id}.pdf"
    if pdf_path.exists() and not args.overwrite:
        print(
            f"[skip] {pdf_path} 已存在，若需重新下载请使用 --overwrite", file=sys.stderr
        )
        return 0

    url = build_uva_url(args.uva_id)
    try:
        data, final_url = download_with_http_fallback(url)
    except urllib.error.HTTPError as exc:
        print(f"[error] 下载失败（HTTP {exc.code}）: {url}", file=sys.stderr)
        return 1
    except urllib.error.URLError as exc:
        print(f"[error] 无法连接 UVA: {exc.reason}", file=sys.stderr)
        return 1

    pdf_path.write_bytes(data)
    text_path = folder_path / f"p{args.uva_id}.txt"
    sample_path = folder_path / f"p{args.uva_id}_sample.txt"
    #
    # create solve_try.cpp in same folder
    solve_try_path = folder_path / f"uva_{args.uva_id}_solve_try.cpp"
    if not solve_try_path.exists():
        header_url = problem_url or final_url
        if not problem_url:
            print(
                "[warn] 未找到题面 URL，solve_try.cpp 将写入 PDF 链接",
                file=sys.stderr,
            )
        solve_try_path.write_text(
            f"// {header_url}\n"
            f"// {folder_name}\n"
            "#include <bits/stdc++.h>\n"
            "using namespace std;\n"
            "\n"
            "int main() {\n"
            "    ios::sync_with_stdio(false);\n"
            "    cin.tie(nullptr);\n"
            "    \n"
            "}\n"
        )

    if convert_pdf_to_text(pdf_path, text_path):
        try:
            text_content = text_path.read_text(encoding="utf-8")
        except UnicodeDecodeError:
            text_content = text_path.read_text(encoding="latin1")
        sample_input, sample_output = extract_samples(text_content)
        if sample_input or sample_output:
            with sample_path.open("w", encoding="utf-8") as fh:
                if sample_input:
                    fh.write("Sample Input:\n")
                    fh.write(sample_input)
                    fh.write("\n\n")
                if sample_output:
                    fh.write("Sample Output:\n")
                    fh.write(sample_output)
                    fh.write("\n")
        elif sample_path.exists():
            sample_path.unlink()
    else:
        if text_path.exists():
            text_path.unlink()
        if sample_path.exists():
            sample_path.unlink()

    print(f"[ok] 已保存 {final_url} -> {pdf_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
