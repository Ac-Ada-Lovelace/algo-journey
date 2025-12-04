# UVa 1604 - Cubic Eight-Puzzle 题面讲解

## 【题目概览】

这是一个立方体八数码问题。在 3×3 棋盘上放置 8 个染色立方体，留一个空格。通过滚动立方体到空格，使得立方体顶面形成指定颜色模式。

## 【输入格式：逐句解释】

> The input is a sequence of datasets. The end of the input is indicated by a line containing two zeros separated by a space. The number of datasets is less than 16.

输入是一系列数据集。输入以包含两个空格分隔的 0 的行结束。数据集数量小于 16。

> Each dataset is formatted as follows.

每个数据集格式如下。

> The first line contains two integers x and y separated by a space, indicating the position (x, y) of the initially empty square. The values of x and y are 1, 2, or 3.

第一行包含两个空格分隔的整数 x 和 y，表示初始空格的位置 (x, y)。x 和 y 的值为 1、2 或 3。

> The following three lines specify the color pattern to make. Each line contains three characters F1j, F2j, and F3j, separated by a space.

接下来三行指定要形成的颜色模式。每行包含三个字符 F1j、F2j 和 F3j，用空格分隔。

> Character Fij indicates the top color of the cube, if any, at position (i, j) as follows:
> B: Blue,
> W: White,
> R: Red,
> E: the square is Empty.

字符 Fij 表示位置 (i, j) 处立方体（如果有）的顶面颜色，如下：
- B：蓝色
- W：白色
- R：红色
- E：该格子为空

> There is exactly one 'E' character in each dataset.

每个数据集中恰好有一个 'E' 字符。

## 【输入格式（结构化摘要）——字段清单形式】

字段顺序：

1. 第 1 行：x, y
   - 含义：初始空格的位置坐标
   - 类型：两个整数，空格分隔
   - 取值范围：x ∈ {1, 2, 3}，y ∈ {1, 2, 3}
   - 数据保证：题面明确指定为 1、2 或 3

2. 第 2 至第 4 行：目标颜色模式
   - 含义：3×3 的目标颜色配置
   - 类型：每行 3 个字符，空格分隔
   - 字符范围：'B'（蓝色）、'W'（白色）、'R'（红色）、'E'（空格）
   - 数据保证：恰好有一个 'E' 字符
   - 特别说明：字符 Fij 表示位置 (i, j) 的颜色

多组输入：
- 是否多组：是
- 每组格式：第一行 x y，接下来 3 行目标颜色模式
- 终止条件：x = 0 且 y = 0
- 终止行是否需要处理：否

隐含条件 / 数据保证：
- 数据集数量小于 16
- 每个数据集恰好有一个空格位置（'E'）
- 坐标系统：(x, y) 其中 x 是列，y 是行（从 1 开始）

## 【输出格式】

> For each dataset, output the minimum number of steps to achieve the goal, when the goal can be reached within 30 steps. Otherwise, output '-1' for the dataset.

对每个数据集，如果目标可以在 30 步内达到，输出达到目标的最小步数。否则，为该数据集输出 '-1'。

输出说明：
- 每组输出一行
- 输出一个整数：最小步数（0-30）或 -1
- 无前缀或额外格式

## 【样例输入输出（完整引用 + 输入部分解释）】

样例输入：
```
1 2
W W W
E W W
W W W
2 1
R B W
R W W
E W W
3 3
W B W
B R E
R B R
3 3
B W R
B W R
B E R
2 1
B B B
B R B
B R E
1 1
R R R
W W W
R R E
2 1
R R R
B W B
R R E
3 2
R R R
W E W
R R R
0 0
```

样例输出：
```
0
3
13
23
29
30
-1
-1
```

样例解释：
- 第 1 组：空格在 (1,2)，目标全是 W，空格在 (2,2) → 答案 0（初始状态已满足）
- 第 2 组：空格在 (2,1) → 需要 3 步
- 第 3 组：空格在 (3,3) → 需要 13 步
- 第 4 组：空格在 (3,3) → 需要 23 步
- 第 5 组：空格在 (2,1) → 需要 29 步
- 第 6 组：空格在 (1,1) → 需要 30 步（恰好达到限制）
- 第 7 组：空格在 (2,1) → 答案 -1（超过 30 步）
- 第 8 组：空格在 (3,2) → 答案 -1（超过 30 步）
- 终止行：0 0

## 【关键假设 / 陷阱清单】

1. **立方体染色规则**（PDF 明确说明）：
   - 所有立方体的染色方式相同
   - 相对的面颜色相同
   - 三种颜色：蓝色、白色、红色

2. **初始状态**（PDF 明确说明）：
   - 所有 8 个立方体具有相同的初始朝向
   - 需要根据图 4 理解初始朝向

3. **移动规则**（PDF 明确说明）：
   - 只能滚动（roll）相邻的立方体到空格
   - 不是平移，是滚动！立方体的朝向会改变

4. **步数限制**：30 步，超过输出 -1

5. **坐标系统**：
   - (x, y) 表示位置，x 是列（1-3），y 是行（1-3）
   - Fij 中 i 是列，j 是行

6. **状态空间**：
   - 需要追踪每个立方体的位置和朝向（6 个面的方向）
   - 状态数量巨大，需要高效的状态表示和搜索

7. **初始检查**：
   - 如果初始状态已经满足目标，输出 0

## 【解法提示（可选）】

- 核心算法：BFS（广度优先搜索）+ 状态压缩
- 关键点：
  1. 状态表示：每个立方体的位置 + 6 个面的朝向
  2. 滚动模拟：准确模拟立方体滚动时各面的旋转
  3. 状态去重：使用哈希表或 set 记录访问过的状态
  4. 深度限制：BFS 深度不超过 30
- 难点：正确实现立方体滚动的朝向变化逻辑
- 时间复杂度：状态空间大，需要高效剪枝
