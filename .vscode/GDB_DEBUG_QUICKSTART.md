# GDB 调试快速指南

## 🚀 一键启动调试

### 方法 1：下拉菜单（推荐）
1. 按 `F5` 或点击左侧调试图标
2. 在顶部下拉菜单选择 **"🐛 GDB Debug (GNU C++)"**
3. 按 `F5` 开始调试

### 方法 2：快捷键
1. 打开要调试的 `.cpp` 文件
2. 设置断点（点击行号左侧）
3. 按 `F5`，选择 **"🐛 GDB Debug (GNU C++)"**
4. 程序会自动编译并在断点处暂停

## 📋 配置说明

### 🐛 GDB Debug (GNU C++)
**全新独立配置，专门用于 GDB 调试**

- **编译器**: `/usr/bin/g++` (GNU C++)
- **编译选项**:
  - `-g3`: 最详细的调试信息
  - `-O0`: 无优化，方便调试
  - `-std=c++17`: C++17 标准
  - `-Wall -Wextra`: 显示所有警告
- **输出文件**: `${filename}.debug.bin`
- **调试器**: GDB
- **特性**:
  - ✅ 数组完整展开显示
  - ✅ 数组索引显示
  - ✅ STL 容器美化打印
  - ✅ Intel 反汇编风格
  - ✅ 禁用 debuginfod（避免延迟）

### Debug Active File
**原有配置，保持兼容**

- 输出文件: `${filename}.bin`
- 其他配置基本相同

## 🎯 使用示例

### 当前文件：solve_try.cpp

#### 编译命令（自动执行）
```bash
/usr/bin/g++ -g3 -O0 -std=c++17 -Wall -Wextra \
    solve_try.cpp -o solve_try.debug.bin
```

#### 调试启动
- 按 `F5` → 选择 "🐛 GDB Debug (GNU C++)"
- 或在调试面板直接选择并点击绿色播放按钮

#### 生成的文件
- `solve_try.debug.bin` - 调试用可执行文件（已在 .gitignore）

## ⌨️ 调试快捷键

| 快捷键 | 功能 |
|--------|------|
| `F5` | 继续/启动 |
| `F9` | 设置/取消断点 |
| `F10` | 单步跳过（Step Over）|
| `F11` | 单步进入（Step Into）|
| `Shift+F11` | 单步跳出（Step Out）|
| `Ctrl+Shift+F5` | 重新启动 |
| `Shift+F5` | 停止调试 |

## 🔍 查看变量

### 变量面板
- 自动显示局部变量
- 展开数组、结构体、STL 容器

### 监视表达式
右键 **WATCH** 面板 → 添加表达式：
```cpp
variable_name      // 查看变量
*array@10         // 查看数组前 10 个元素
vec.size()        // 查看容器大小
str.c_str()       // 查看 string 内容
```

### 调试控制台
输入 GDB 命令（带 `-exec` 前缀）：
```gdb
-exec print variable
-exec print *array@10
-exec info locals
-exec backtrace
```

## 🐞 断点技巧

### 普通断点
- 点击行号左侧添加

### 条件断点
1. 右键断点
2. 选择 "编辑断点"
3. 输入条件：`i > 5` 或 `str == "test"`

### 日志点
1. 右键行号
2. 选择 "添加日志点"
3. 输入消息：`i = {i}, sum = {sum}`
4. 不暂停程序，只输出日志

## 📊 数组和容器显示

### 数组
```cpp
int arr[100];
// 在监视面板输入：
*arr@10          // 显示前 10 个
*(arr+10)@20     // 显示第 11-30 个
```

### STL 容器
```cpp
vector<int> vec;
string str;
map<int, string> mp;
// 直接在变量面板展开查看
// pretty-printing 会自动格式化
```

## 🛠️ 编译选项说明

### `-g3` vs `-g`
- `-g`: 标准调试信息
- `-g3`: 包含宏定义等额外信息

### `-O0` vs `-O2`
- `-O0`: 无优化，变量值准确，断点精确
- `-O2`: 优化后，变量可能被优化掉，断点位置可能不准

### 调试时建议
- 使用 `-O0` 确保调试准确性
- 提交 OJ 前改用 `-O2` 测试性能

## 🔧 故障排除

### 问题：按 F5 没反应
**解决**：
1. 检查是否选择了正确的配置
2. 查看 OUTPUT 面板的错误信息
3. 确保 GDB 已安装：`gdb --version`

### 问题：看不到数组内容
**解决**：
1. 确保断点在数组赋值**之后**
2. 在监视面板使用 `*array@size` 语法
3. 检查数组是否已初始化

### 问题：变量显示 optimized out
**解决**：
- 配置已使用 `-O0`，不应出现此问题
- 如果仍然出现，检查变量作用域

### 问题：GDB 启动很慢
**解决**：
- 配置已禁用 debuginfod
- 如果还慢，检查网络代理设置

## 📁 文件说明

### 配置文件
- `.vscode/launch.json` - 调试配置
- `.vscode/tasks.json` - 编译任务
- `.vscode/c_cpp_properties.json` - IntelliSense 配置

### 生成文件
- `*.debug.bin` - GDB 调试用（已被 .gitignore）
- `*.bin` - 普通编译输出（已被 .gitignore）

## 🎓 进阶技巧

### 反向调试
GDB 支持记录执行历史并反向调试：
```gdb
-exec record
-exec reverse-step    # 反向单步
-exec reverse-continue # 反向继续
```

### 监视内存
```gdb
-exec x/10xw &variable  # 以十六进制显示内存
-exec watch variable    # 设置观察点
```

### 多线程调试
```gdb
-exec info threads      # 查看所有线程
-exec thread 2          # 切换到线程 2
```

## 📚 相关文档

- [GDB 官方文档](https://sourceware.org/gdb/documentation/)
- [VS Code C++ 调试](https://code.visualstudio.com/docs/cpp/cpp-debug)
- [Repository Guidelines](../AGENTS.md)

---

**快速开始**: 打开任意 `.cpp` 文件，设置断点，按 `F5`，选择 "🐛 GDB Debug (GNU C++)" 即可！
