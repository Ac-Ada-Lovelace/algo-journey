# Repository Guidelines

## 项目结构与模块划分

- 顶层按平台划分：`codeforce`、`leetcode`、`luogu`、`prac`；平台特有的 `bits/stdc++.h` 放在各自的 `bits/` 目录里，编译时使用 `-I<platform>/bits`。
- `prac` 中的每道题都使用 `题目标识符 空格 题目中文名` 作为文件夹名（例如 `prac/UVa1586 Molar Mass/`），同目录下可存放样例、笔记与可执行文件。
- 新题目必须直接建立对应目录，避免在 `prac` 根目录留下散落的 `.cpp`。
- 共享输出或临时数据请放在 `prac/output/` 一类的公共目录中，并视需要加入 `.gitignore`。

## 构建、测试与本地开发

- 推荐命令：
  ```bash
  g++ -std=c++17 -O2 -Wall -Wextra -Iprac/bits \
      prac/UVa455\ Count\ Num/count_num_UVa455.cpp \
      -o build/count_num.bin
  ./build/count_num.bin < sample.in
  ```
  产物统一使用 `.bin` 后缀，便于被忽略或清理。
- 临时调试可直接将可执行文件放在题目目录，但提交前删除或写入 `.gitignore`。
- 解 UVA OJ 题目时统一使用下述命令（兼容官方评测环境）：
  ```
  g++ -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE source.cpp -o build/problem.bin
  ```

## 代码风格与命名

- 统一使用 C++17 与 `bits/stdc++.h`；缩进为两个空格，花括号与控制语句同行，单行不超过 100 列。
- 变量名尽量语义化，函数使用 lowerCamelCase；常量使用全大写加下划线。
- 题主习惯将代码文件命名为 `solve.cpp`、`solve_try.cpp` 等与题目弱相关的名称，此命名方式在各题目录下视为默认，无需强制与题号绑定。
- 由于仓库默认中文交流，代码注释与 README 亦以中文为主（题面需英文的除外）。

## 测试指引

- 目前无统一框架，直接用标准输入输出驱动，必要时把样例写成 `input1.txt`、`output1.txt` 放在题目目录。
- 处理浮点题目务必设定精度（参见 `prac/Practice Sum Of Subsequence/sum_of_subsquence.cpp`），并测试极端范围。
- 每次修改后至少手动跑一遍对应 `.bin`，并记录命令行以便复现。

## 提交与 PR 规范

- 沿用历史中的简短祈使句提交信息，如 `add molar_mass`、`fix build`；同一次提交只做一类修改。
- PR 描述需写明解决的问题、运行命令、样例输入输出，并附上题目链接；仓库交流默认使用中文。
- 若生成了 `.bin`、日志或大文件，请在描述中说明是否忽略，以便审核者同步环境。

## Codex 使用习惯

1. “讲题面”代表要尽可能根据题目文件夹内的 PDF 或参考资料逐句讲解；若缺少本地资料，可联网查询补充。对于叙述性，背景性的问题，可以逐字翻译，对于一些文化性的问题，可以适当补充背景知识；讲解时务必明确交代题目的整体流程、输入结构（字段含义、范围、顺序）与输出要求（格式、含义），必要时可引用样例说明。涉及样例时，先逐字重 Sample Input/Output，再跟随文字解释；若样例含多个 case，应分隔逐个说明。
2. “看代码问题”只需指出代码中的问题，不要直接修改；只有在明确要求“给出正确代码”时，才新建文件给出实现，禁止覆盖原始文件。
3. 若用户要求“写代码”或“给出正确代码”，除非明确同意修改现有文件，否则需在相应目录新建文件保存方案，禁止直接覆盖或编辑用户已有代码。
4. 运行需要脚本的命令时，请把脚本放在 `tool/` 下（按用途建子目录），执行完毕也不要删除；缓存或临时数据也放在 `tool/` 体系内，以便复用。
5. 所有讲解、说明与答复一律使用中文。

## 书目题单 JSON 使用指南

- 根目录新增三份以 `Beginning_Algorithm_Contests*.json` 命名的题目目录，分别对应 AOAPC 第一版、第二版与 Training Guide。文件顶层是一个对象，统一包含 `name`（章节或题目标题）、`url`（原题链接）、`kind`（`FOLDER`/`FILE`）以及 `children`（子节点数组）。`FILE` 节点表示具体题目，`FOLDER` 节点表示章节或小节。
- 需要查找题目时，优先使用 `jq` 沿树遍历，例如：
  ```bash
  jq '.. | objects | select(.kind=="FILE" and (.name|test("10055"))) | {name,url}' Beginning_Algorithm_Contests.json
  ```
  也可以先列出章节：`jq -r '.children[].name' Beginning_Algorithm_Contests_(Second_Edition).json`。
- 讲解或整理题单时，请引用 JSON 中的 `name` 与 `url`，并将章节层级反映在描述里（如“Volume 0 ▶ 10055 - Hashmat...”），方便他人定位。
- 若需批量提取信息（例如生成练习计划），可以把 JSON 管道给自定义脚本，但脚本仍需放在 `tool/` 目录下，且不要直接编辑原始 JSON。

## 题面下载工具

- 若需按 `prac/UVa<ID> 标题/p<ID>.pdf` 的约定拉取 UVA 题面，可使用 `tool/scripts/fetch_uva_pdf.py`。示例命令：
  ```bash
  python tool/scripts/fetch_uva_pdf.py 210 "Concurrency Simulator"
  ```
  该脚本会自动创建 `prac/UVa210 Concurrency Simulator/` 目录并下载 `https://onlinejudge.org/external/2/210.pdf` 保存为 `p210.pdf`。文件存在时默认跳过，若需覆盖可追加 `--overwrite`，若想放在其他根目录则使用 `--root <dir>`。
- 请确保运行命令时网络可用（脚本使用官方 UVA PDF 链接），若下载失败会在终端输出具体 HTTP/连接错误，按提示重试或改用本地缓存。
