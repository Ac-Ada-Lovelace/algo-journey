# Repository Guidelines

## Project Structure & Module Organization
- Top-level directories map to problem sources: `codeforce`, `leetcode`, `luogu`, and `prac`.
- Each problem in `prac` now lives in its own folder following the pattern `Identifier Human-Readable Title` (e.g., `prac/UVa1586 Molar Mass/`); keep supporting assets (notes, binaries) beside the solution.
- Shared headers such as `bits/stdc++.h` sit under each platform's `bits/` subfolder—include them via `-Icodeforce/bits` or the matching path for cross-platform reuse.
- Avoid reintroducing loose `.cpp` files at the root; create a new folder immediately when adding a problem.

## Build, Test, and Development Commands
- Compile single-file solutions with g++17 and the shared bits header, e.g.:
  ```bash
  g++ -std=c++17 -O2 -Wall -Wextra -Iprac/bits \
      prac/UVa455\ Count\ Num/count_num_UVa455.cpp -o build/count_num
  ```
- Run the produced binary directly (`./build/count_num < sample.in`). Keep binaries inside the per-problem folder or `build/` and add them to `.gitignore` if they are disposable.
- For quick experiments, mirror the pattern used in `prac/Practice Decimal Expansion/` where both source and helper executables are colocated.

## Coding Style & Naming Conventions
- Use C++17, include `bits/stdc++.h`, and prefer the STL.
- Indent with two spaces, brace on the same line as the control statement, and keep lines under 100 columns.
- Name new directories and files descriptively: `<JudgeID><space><Short Title>/<slug>.cpp` or `Practice <Topic>/<topic>.cpp` for non-judge drills.
- Print statements should be English unless the problem demands otherwise.

## Testing Guidelines
- No global framework exists; rely on deterministic stdin/stdout tests.
- Store reusable samples as `.txt` files inside the problem folder (e.g., `prac/UVa232 Crossword Answers/cases/input1.txt`) and document the command used to run them.
- When floating-point output matters, set precision explicitly (see `prac/Practice Sum Of Subsequence/sum_of_subsquence.cpp`).
- Before committing, rerun any binaries touched and capture edge cases (minimum/maximum constraints, empty input).

## Commit & Pull Request Guidelines
- Follow the short, imperative style already in history (`add molar_mass`, `fix: resolve merge conflict`).
- Each commit should touch a single logical change: new problem, refactor, or docs update.
- Pull requests should summarize the problem solved, steps to reproduce the fix/run, and include sample I/O when relevant; link issue IDs or judge URLs for traceability.
- Highlight any generated artifacts that should remain ignored so reviewers can cleanly rebuild.
