# UVa 11882 - Biggest Number 题面讲解

## 【题目概览】

在带障碍物的迷宫中，从任意格子开始行走，收集数字形成最大的数字。

## 【输入格式：逐句解释】

> There will be at most 25 test cases.

最多 25 组测试数据。

> Each test begins with two integers R and C (2 ≤ R,C ≤ 15, R ∗ C ≤ 30), the number of rows and columns of the maze.

每组数据第一行两个整数 R 和 C，表示迷宫的行数和列数，满足 2 ≤ R, C ≤ 15，且 R×C ≤ 30。

> The next R rows represent the maze. Each line contains exactly C characters (without leading or trailing spaces), each of them will be either '#' or one of the nine non-zero digits.

接下来 R 行表示迷宫。每行恰好 C 个字符（没有前导或尾随空格），每个字符要么是 '#'（障碍物），要么是 1-9 的非零数字。

> There will be at least one non-obstacle squares (i.e. squares with a non-zero digit in it) in the maze.

迷宫中至少有一个非障碍格子（即至少有一个数字格子）。

> The input is terminated by a test case with R = C = 0, you should not process it.

输入以 R = C = 0 的测试用例结束，不需要处理该行。

## 【输入格式（结构化摘要）——字段清单形式】

字段顺序：

1. 第 1 行：R, C
   - 含义：迷宫的行数和列数
   - 类型：两个整数
   - 取值范围：2 ≤ R, C ≤ 15，且 R×C ≤ 30
   - 数据保证：至少有一个非障碍格子

2. 第 2 至第 R+1 行：迷宫内容
   - 含义：每行表示迷宫的一行
   - 类型：字符串
   - 长度：恰好 C 个字符，无前导或尾随空格
   - 字符范围：'#'（障碍物）或 '1'-'9'（数字）
   - 特别说明：不包含字符 '0'

多组输入：
- 是否多组：是
- 每组格式：第一行 R C，接下来 R 行迷宫
- 终止条件：R = C = 0
- 终止行是否需要处理：否

隐含条件 / 数据保证：
- 最多 25 组测试数据
- 每个迷宫至少有一个数字格子
- R×C ≤ 30 保证了状态空间有限

## 【输出格式】

> For each test case, print the biggest number you can find, on a single line.

对每组测试数据，输出一行，表示能找到的最大数字。

输出说明：
- 每组输出一行
- 直接输出数字，无前缀
- 数字可能很大（最多 30 位），需用字符串处理

## 【样例输入输出（完整引用 + 输入部分解释）】

样例输入：
```
3 7
##9784#
##123##
##45###
0 0
```

样例输出：
```
791452384
```

样例解释：
- 第 1 组：3×7 的迷宫
  - 第 1 行：`##9784#`
  - 第 2 行：`##123##`
  - 第 3 行：`##45###`
  - 可行路径：7→9→1→4→5→2→3→8→4，得到 791452384
- 终止行：0 0

## 【关键假设 / 陷阱清单】

1. **不能重复访问同一个格子**（PDF 明确说明："you cannot walk into a square more than once"）
2. **可以从任意格子开始**（PDF 明确说明："You can start from any square"）
3. **数字可能非常大**（最多 30 位），不能用整数类型，必须用字符串比较
4. **最大数字的定义**：先比较长度（位数多的更大），长度相同时字典序比较
5. **障碍物用 '#' 表示**，不能经过
6. **只包含非零数字 1-9**，不含 '0'
7. **行走方向**：只能上下左右四个方向

## 【解法提示（可选）】

- 核心算法：DFS + 回溯
- 从每个可能的起点（按数字从大到小）开始搜索
- 维护 visited 数组防止重复访问
- 关键剪枝：
  1. 如果当前字符串长度相同但字典序已经小于已知最优解，可以剪枝
  2. 优先从大数字开始搜索
  3. 在搜索过程中实时更新最优解
- 时间复杂度：O(4^(R×C))，但通过剪枝可以显著优化
