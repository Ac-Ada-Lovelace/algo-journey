# VS Code C++ 调试配置指南

## 快速开始

### 一键调试
1. 打开任意 `.cpp` 文件
2. 点击行号左侧设置断点（出现红点）
3. 按 **F5**
4. 选择 **🐛 GDB Debug (GNU C++)** 
5. 程序自动编译并在断点处暂停

## 调试配置

### 🐛 GDB Debug (GNU C++) - 推荐使用

**专门的 GDB 调试配置，提供最佳调试体验**

- **编译器**: `/usr/bin/g++` (GNU C++)
- **编译选项**:
  - `-g3`: 完整调试信息（包含宏定义）
  - `-O0`: 完全无优化，确保变量值准确
  - `-std=c++17`: C++17 标准
  - `-Wall -Wextra`: 显示所有编译警告
- **输出**: `${filename}.debug.bin`（已在 .gitignore 中）
- **调试器**: GDB with VS Code DAP
- **特性**:
  - ✅ 数组完整展开，带索引显示
  - ✅ STL 容器美化打印（vector、map、string 等）
  - ✅ 无网络延迟（已禁用 debuginfod）
  - ✅ Intel 汇编语法
  - ✅ 图形化断点、变量查看
  - ✅ **自动跳过标准库代码**（单步时不进入 STL 源码）

## 调试快捷键

| 快捷键 | 功能 | 说明 |
|--------|------|------|
| `F5` | 继续/启动 | 启动调试或继续执行到下一个断点 |
| `F9` | 切换断点 | 在当前行添加/删除断点 |
| `F10` | 单步跳过 | 执行当前行，不进入函数内部 |
| `F11` | 单步进入 | 进入函数内部调试 |
| `Shift+F11` | 单步跳出 | 跳出当前函数 |
| `Ctrl+Shift+F5` | 重新启动 | 重启调试会话 |
| `Shift+F5` | 停止调试 | 终止调试会话 |

## 查看变量

### 1. 变量面板（VARIABLES）
- 自动显示当前作用域的所有变量
- 点击变量左侧的 ▶ 展开查看内容
- 数组、结构体、STL 容器都可以展开

### 2. 监视面板（WATCH）
右键点击监视面板 → "添加表达式"，输入：

```cpp
variable         // 查看变量
arr[i]          // 查看数组元素
*arr@10         // 查看数组前 10 个元素（GDB 语法）
*(arr+5)@5      // 查看数组第 6-10 个元素
vec.size()      // 查看 vector 大小
str.c_str()     // 查看 string C 字符串
```

### 3. 鼠标悬停
调试暂停时，将鼠标悬停在代码中的变量上，会弹出值显示

### 4. 调试控制台（DEBUG CONSOLE）
输入 GDB 命令（需要 `-exec` 前缀）：

```gdb
-exec print variable
-exec print *arr@10
-exec info locals
-exec backtrace
-exec watch variable  // 设置观察点
```

## 断点技巧

### 普通断点
点击行号左侧，出现红点即为断点

### 条件断点
1. 右键点击断点
2. 选择"编辑断点"
3. 添加条件表达式

```cpp
i > 100           // 当 i 大于 100 时才中断
str == "test"     // 当字符串等于 "test" 时中断
arr[0] != 0       // 当数组首元素不为 0 时中断
```

### 日志点（Logpoint）
不暂停程序，只输出日志信息

1. 右键点击行号
2. 选择"添加日志点"
3. 输入消息模板

```
i = {i}, sum = {sum}, result = {result}
```

## 示例：调试当前文件

假设调试 `solve_try.cpp`：

1. **编译命令**（自动执行）:
   ```bash
   /usr/bin/g++ -g3 -O0 -std=c++17 -Wall -Wextra \
       solve_try.cpp -o solve_try.debug.bin
   ```

2. **生成文件**: `solve_try.debug.bin`（不会提交到 git）

3. **调试流程**:
   - 在关键代码行设置断点
   - 按 F5，选择 "🐛 GDB Debug (GNU C++)"
   - 程序在断点处暂停
   - 查看变量面板中的所有变量值
   - 使用 F10/F11 单步执行
   - 在监视面板添加需要重点关注的表达式

## 数组和容器调试

### C 风格数组
```cpp
int arr[100];
double data[50];

// 在监视面板输入:
*arr@10          // 查看前 10 个元素
*(arr+10)@20     // 查看第 11-30 个元素
arr[i]           // 查看特定索引
```

### STL 容器
```cpp
vector<int> vec;
string str;
map<int, string> mp;
set<int> st;

// 直接在变量面板展开查看
// GDB pretty-printing 会自动格式化显示
```

### 字符串
```cpp
string s = "hello";
char str[] = "world";

// 变量面板会直接显示内容
// 或在监视面板:
s.c_str()        // 查看 C 字符串
s.size()         // 查看长度
```

## 常见问题

### Q: 变量显示为 `<optimized out>`
**A**: 不会出现，配置已使用 `-O0` 无优化

### Q: 看不到数组的所有元素
**A**: 
- 点击数组左侧的展开箭头
- 或在监视面板使用 `*array@size` 语法
- 配置已启用数组索引显示

### Q: 断点位置不对或跳过某些代码
**A**: 不会出现，`-O0` 确保代码未被优化

### Q: GDB 启动很慢
**A**: 配置已禁用 debuginfod，不会有网络延迟

### Q: 程序需要输入数据
**A**: 
- 调试控制台支持标准输入
- 或使用重定向：修改 `launch.json` 中的 `args`
- 或使用 `externalConsole: true` 打开外部终端

### Q: 单步调试时进入了 STL 源码（如 vector、string）
**A**: 
- 配置已自动跳过标准库代码（包括 `/usr/src/debug/*` 和 GCC 构建目录）
- 已添加 `.gdbinit` 配置文件，包含：
  - 跳过所有 `/usr/include/c++/*` 文件
  - 跳过所有 `/usr/src/debug/*` 文件
  - 跳过所有 `*/gcc-build/*` 和 `*/libstdc++*/*` 文件
  - 跳过所有 `std::` 和 `__gnu_cxx::` 命名空间的函数
- 使用 **F10（单步跳过）** 而不是 **F11（单步进入）**
- 如需查看跳过的文件列表：在调试控制台输入 `-exec info skip`
- 如需临时禁用：`-exec skip disable` 然后重新调试

## 配置文件位置

```
.vscode/
├── launch.json          # 调试配置
├── tasks.json           # 编译任务
└── c_cpp_properties.json # IntelliSense 配置
.gdbinit                  # GDB 启动配置（自动跳过标准库）
```

## 编译输出文件

| 文件模式 | 用途 | Git 状态 |
|---------|------|----------|
| `*.debug.bin` | GDB 调试用 | 已忽略 |
| `*.bin` | 普通编译输出 | 已忽略 |
| `*.o` | 目标文件 | 已忽略 |
| `*.exe` | Windows 可执行文件 | 已忽略 |

## 进阶技巧

### 修改编译选项
编辑 `.vscode/tasks.json` → 找到 `GNU C++ Compile for Debug` 任务：

```json
"args": [
    "-g3",              // 调试信息级别
    "-O0",              // 优化级别 (O0/O1/O2/O3)
    "-std=c++17",       // C++ 标准 (c++11/14/17/20/23)
    "-Wall",            // 所有警告
    "-Wextra",          // 额外警告
    "${file}",          // 当前文件
    "-o",
    "${fileDirname}/${fileBasenameNoExtension}.debug.bin"
]
```

### 添加程序参数
编辑 `.vscode/launch.json` → 找到 `🐛 GDB Debug (GNU C++)` 配置：

```json
"args": ["input.txt", "output.txt"],  // 命令行参数
```

### 使用外部终端
```json
"externalConsole": true,  // 在外部终端运行
```

### 修改工作目录
```json
"cwd": "${workspaceFolder}/data",  // 设置工作目录
```

## Git 配置

当前 Git 用户配置：
```bash
git config --global user.name "yehj"
git config --global user.email "ac1583001@gmail.com"
```

验证配置：
```bash
git config --global --list | grep user
```

## 项目结构

根据 `AGENTS.md` 规范：

```
algo/
├── .vscode/           # VS Code 配置
│   ├── launch.json    # 调试配置
│   ├── tasks.json     # 编译任务
│   └── *.md          # 文档
├── codeforce/         # Codeforces 题目
├── leetcode/          # LeetCode 题目
├── luogu/            # 洛谷题目
└── prac/             # 练习题
    └── UVa* /        # UVa 题目目录
        ├── *.cpp     # 源代码
        └── *.bin     # 可执行文件（已忽略）
```

每道题使用独立目录：`题目标识符 空格 题目中文名`

## 推荐工作流

1. **新建题目**:
   ```bash
   mkdir -p "prac/UVa999 题目名"
   cd "prac/UVa999 题目名"
   touch solve.cpp
   ```

2. **编写代码**: 在 VS Code 中打开 `solve.cpp`

3. **调试**:
   - 设置断点
   - F5 启动 "🐛 GDB Debug (GNU C++)"
   - 单步调试，查看变量

4. **测试**:
   ```bash
   ./solve.debug.bin < input.txt
   ```

5. **提交**: 确认正确后提交到 OJ

## 参考资源

- [GDB 官方文档](https://sourceware.org/gdb/documentation/)
- [VS Code C++ 调试](https://code.visualstudio.com/docs/cpp/cpp-debug)
- [GDB 调试技巧](https://sourceware.org/gdb/onlinedocs/gdb/index.html)
- [C++ Reference](https://en.cppreference.com/)

## 总结

✅ 已配置完成的功能：
- GNU C++ 编译器 (g++ 17)
- GDB 调试器
- VS Code DAP 图形化界面
- 数组和容器完整显示
- 一键式启动调试
- 自动编译和错误检测
- Git 用户配置

🎯 立即开始：按 `F5` → 选择 "🐛 GDB Debug (GNU C++)" → 开始调试！
