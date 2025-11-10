# C++ 单文件调试配置指南

## 配置文件说明

### 1. tasks.json - 编译任务
- **作用**: 定义如何编译当前打开的 C++ 文件
- **编译器**: `/usr/bin/g++`
- **编译参数**:
  - `-g`: 生成调试信息
  - `-O0`: 无优化（方便调试，可以正确显示变量值）
  - `-std=c++17`: 使用 C++17 标准
  - 输出文件: 与源文件同名（无扩展名）

### 2. launch.json - 调试配置
- **调试器**: GDB (`/usr/bin/gdb`)
- **配置名**: "Debug Active File"
- **preLaunchTask**: 会在调试前自动编译文件
- **工作目录**: 源文件所在目录

### 3. c_cpp_properties.json - IntelliSense 配置
- 配置代码补全和语法检查
- 使用 GCC 编译器路径

## 如何使用

### 方法一：使用 F5 快捷键（推荐）
1. 在 VS Code 中打开要调试的 `.cpp` 文件（如 `decimal.cpp`）
2. 在需要的地方设置断点（点击行号左侧）
3. 按 **F5** 开始调试
4. 程序会自动编译并在断点处停止

### 方法二：使用调试面板
1. 打开要调试的文件
2. 点击左侧调试图标（或按 `Ctrl+Shift+D`）
3. 选择 "Debug Active File" 配置
4. 点击绿色播放按钮开始调试

## 调试功能

### 设置断点
- **行断点**: 点击行号左侧的空白处
- **条件断点**: 右键点击断点，选择 "Edit Breakpoint"，添加条件表达式

### 调试控制
- **F5**: 继续执行
- **F10**: 单步跳过（Step Over）
- **F11**: 单步进入（Step Into）
- **Shift+F11**: 单步跳出（Step Out）
- **Ctrl+Shift+F5**: 重新启动调试
- **Shift+F5**: 停止调试

### 查看变量
- **变量面板**: 自动显示当前作用域的所有变量
- **监视面板**: 添加表达式进行监视
- **悬停查看**: 鼠标悬停在变量上可以查看其值
- **调试控制台**: 可以执行 GDB 命令

## 常见问题

### 1. 找不到调试器
**错误**: "Unable to start debugging. Unable to locate gdb."
**解决**: 
```bash
sudo pacman -S gdb  # Arch Linux
```

### 2. 断点无效或位置不对
**原因**: 编译时使用了 `-O2` 或更高的优化级别
**解决**: 已配置为 `-O0`，如需修改优化级别，请编辑 `tasks.json`

### 3. 无法显示 STL 容器内容
**解决**: 已启用 GDB 的 pretty-printing，应该可以正常显示 `vector`, `map` 等容器

### 4. bits/stdc++.h 的警告
这是正常的，因为这个头文件包含了一些在 C++17 中已弃用的头文件。不影响调试功能。

## 自定义配置

### 修改编译参数
编辑 `.vscode/tasks.json` 的 `args` 数组：
```json
"args": [
    "-g",              // 保留，用于生成调试信息
    "${file}",         // 保留，当前文件
    "-O0",             // 可改为 -O1, -O2, -O3（会影响调试体验）
    "-std=c++17",      // 可改为 -std=c++20, -std=c++23
    "-Wall",           // 可添加，显示所有警告
    "-Wextra",         // 可添加，显示额外警告
    "-o",
    "${fileDirname}/${fileBasenameNoExtension}"
]
```

### 添加程序参数
编辑 `.vscode/launch.json` 的 `args` 数组：
```json
"args": ["arg1", "arg2"],  // 程序运行时的命令行参数
```

### 使用外部控制台
编辑 `.vscode/launch.json`：
```json
"externalConsole": true,  // 改为 true，在外部终端运行
```

## 示例：调试 decimal.cpp

1. 打开 `prac/decimal.cpp`
2. 在第 29 行（`int main() {`）设置断点
3. 按 F5 开始调试
4. 使用 F10 单步执行，观察变量 `ans` 的变化
5. 在变量面板可以看到 `ans` 数组的值

## 验证配置

运行以下命令验证环境：
```bash
# 检查 g++ 版本
g++ --version

# 检查 gdb 版本
gdb --version

# 手动编译测试
cd prac
g++ -g decimal.cpp -O0 -std=c++17 -o decimal

# 手动调试测试
gdb ./decimal
(gdb) break main
(gdb) run
(gdb) quit
```

## 更多资源

- [VS Code C++ 调试文档](https://code.visualstudio.com/docs/cpp/cpp-debug)
- [GDB 调试指南](https://sourceware.org/gdb/documentation/)
- [VS Code 调试技巧](https://code.visualstudio.com/docs/editor/debugging)
