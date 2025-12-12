# UVA10366 Faucet Flow 详细题解

## 目录
1. [问题描述](#一问题描述)
2. [样例分析](#二样例分析)
3. [暴力思路与优化](#三暴力思路与优化)
4. [核心算法](#四核心算法)
5. [代码实现详解](#五代码实现详解)
6. [特殊情况处理](#六特殊情况处理)
7. [完整代码注释](#七完整代码注释)
8. [复杂度分析](#八复杂度分析)
9. [总结与技巧](#九总结与技巧)

---

## 一、问题描述

### 1.1 题目大意

有一个底部带有若干不同高度柱子的容器。从位置 (L, R) 之间的水龙头开始放水，水会向两侧扩散流动。求最终容器中水的总体积。

### 1.2 输入输出格式

**输入**：
- 第一行：两个整数 L 和 R，表示水龙头位置范围
- 第二行：若干个整数，表示每个柱子的高度 H[i]
- 当 L = 0 且 R = 0 时输入结束

**输出**：
- 输出水的总体积（面积单位）

### 1.3 数据范围
- 柱子数量 n：通过 `n = (|L| + |R|) / 2 + 1` 计算
- 柱子高度：正整数

---

## 二、样例分析

### 2.1 简单例子

假设有如下容器（数字表示柱子高度）：

```
位置:  1   2   3   4   5   6   7
高度:  3   1   2   4   2   1   3
```

水龙头在位置 3 和 4 之间（L=3, R=4）。

**水的扩散过程**：

```
初始状态（位置3-4之间）：
    ║
  ══║══
████████
3 1 2 4 2 1 3
      ↑水龙头

水量 = min(H[3], H[4]) = min(2, 4) = 2
```

**第一次扩展**（向左，因为左边更低）：
```
      ║
  ════║══
████████
3 1 2 4 2 1 3
    ↑新边界

水量 = (4-2) × min(H[2], H[4]) = 2 × min(1, 4) = 2
```

**第二次扩展**（继续向左）：
```
      ║
  ════║══
██████████
3 1 2 4 2 1 3
  ↑新边界

水量 = (4-1) × min(H[1], H[4]) = 3 × min(3, 4) = 9
```

**第三次扩展**（向右）：
```
      ║
  ════║════
██████████████
3 1 2 4 2 1 3
            ↑新边界

水量 = (7-1) × min(H[1], H[7]) = 6 × min(3, 3) = 18
```

**最终答案**：18（或根据题目要求可能需要乘以2）

### 2.2 核心观察

从样例可以看出：
1. **水总是向较低的一侧流动**
2. **水在两个"阻挡柱"之间形成矩形区域**
3. **中间较低的柱子可以"跳过"，不影响水的形状**

---

## 三、暴力思路与优化

### 3.1 暴力模拟（TLE）

**思路**：每次水增加一个单位，判断向哪边流动，逐步扩展。

```cpp
// 伪代码
while (can_expand) {
    if (left_height <= right_height) {
        expand_left_by_1();
    } else {
        expand_right_by_1();
    }
    water_volume++;
}
```

**问题**：
- 时间复杂度 O(答案值)，可能达到 10^6 以上
- 效率太低，无法通过

### 3.2 优化思路

**关键发现**：水在两个"有用柱子"之间会形成完整的矩形。

**什么是"有用柱子"**？
- 能够阻挡水流的柱子
- 即：高度 **严格大于** 当前水位的柱子

**什么是"无用柱子"**？
- 不影响水流形状的柱子
- 即：高度 ≤ 当前水位的柱子
- 这些柱子可以直接跳过！

**优化策略**：
1. 每次直接找到下一个"有用柱子"
2. 计算矩形区域的水量：`宽度 × 高度`
3. 向较低的一侧扩展
4. 重复直到无法扩展

**复杂度降低**：从 O(答案值) 降到 O(n × 有用柱子数量)

---

## 四、核心算法

### 4.1 算法框架

```cpp
// 维护当前水覆盖的区间 [nowl, nowr]
nowl = 水龙头左侧位置;
nowr = 水龙头右侧位置;
ans = min(H[nowl], H[nowr]);  // 初始水量

while (true) {
    // 1. 找到左右两侧下一个有用柱子
    nxtL = GetNxt_L(nowl, false);
    nxtR = GetNxt_R(nowr, false);

    // 2. 判断是否到达边界
    if (nxtL == 0 || nxtR == n+1) {
        // 特殊情况处理（见后文）
        break;
    }

    // 3. 向较低的一侧扩展
    if (H[nowl] <= H[nowr]) {
        nowl = nxtL;  // 左边更低，向左扩展
    }
    if (H[nowl] >= H[nowr]) {
        nowr = nxtR;  // 右边更低，向右扩展
    }

    // 4. 更新水量（矩形面积）
    ans = (nowr - nowl) × min(H[nowl], H[nowr]);
}
```

### 4.2 关键函数：寻找有用柱子

**GetNxt_R**：向右找下一个有用柱子

```cpp
inline int GetNxt_R(int now, bool isSame) {
    for (int i = now + 1; i <= n + 1; i++)
        if (H[i] > H[now] || (H[i] == H[now] && isSame))
            return i;
    return n + 1;  // 找不到返回右边界
}
```

**参数说明**：
- `now`：当前位置
- `isSame`：是否接受相同高度的柱子
  - `false`：只找**严格更高**的柱子（扩展时使用）
  - `true`：也接受**相同高度**的柱子（计算楼梯时使用）

**GetNxt_L**：向左找（对称实现）

```cpp
inline int GetNxt_L(int now, bool isSame) {
    for (int i = now - 1; i >= 0; i--)
        if (H[i] > H[now] || (H[i] == H[now] && isSame))
            return i;
    return 0;  // 找不到返回左边界
}
```

### 4.3 为什么要区分 isSame？

**场景1：区间扩展时**（isSame = false）
```
高度: 3  2  2  2  4
     [nowl    nowr]
```
- 如果 `isSame = true`，会在第一个 2 就停下
- 如果 `isSame = false`，会跳过所有 2，找到 3 或 4
- **扩展时需要跳过相同高度，所以用 false**

**场景2：计算楼梯水量时**（isSame = true）
```
高度: 3  2  2  2  1
楼梯: ═  ══ ══ ══
```
- 需要在每个高度变化处计算一层楼梯
- **所以需要在相同高度处也停下，用 true**

### 4.4 扩展策略详解

**问题**：当 `H[nowl] == H[nowr]` 时，向哪边扩展？

**答案**：两边同时扩展！

```cpp
if (H[nowl] <= H[nowr]) {
    nowl = nxtL;  // 左边更低或相等，向左扩展
}
if (H[nowl] >= H[nowr]) {
    nowr = nxtR;  // 右边更低或相等，向右扩展
}
```

**注意**：这里用的是两个独立的 if，不是 if-else！

**例子**：
```
高度: 4  2  1  1  2  4
         [nowl nowr]
```
- `H[nowl] = H[nowr] = 1`
- 同时满足 `<=` 和 `>=`
- 两边都扩展：`nowl → 2, nowr → 2`
- 新状态：`[2, 2, 1, 1, 2, 2]`，水量 = `(5-2) × 2 = 6`

---

## 五、代码实现详解

### 5.1 输入处理

```cpp
int tmpL, tmpR;  // 水龙头位置
while (scanf("%d%d", &tmpL, &tmpR) == 2 && tmpL != 0 && tmpR != 0) {
    // 计算柱子数量
    n = ((abs(tmpL) + abs(tmpR)) >> 1) + 1;

    // 读入柱子高度
    for (int i = 1; i <= n; i++)
        H[i] = read();

    // 处理...
}
```

**为什么 `n = (|L| + |R|) / 2 + 1`？**

假设 L = -3, R = 5：
- 区间长度 = |L| + |R| = 3 + 5 = 8
- 柱子间有 8 个间隔
- 柱子数量 = 8/2 + 1 = 5

### 5.2 边界哨兵

```cpp
H[0] = H[n + 1] = inf;  // 设置无穷大哨兵
```

**作用**：
1. 避免数组越界
2. 简化边界判断逻辑
3. 当找不到更高柱子时，会返回 0 或 n+1

### 5.3 初始化水位

```cpp
int nowl = ((abs(tmpL) + 1) >> 1);  // 水龙头左侧位置
int nowr = nowl + 1;                  // 水龙头右侧位置
int ans = min(H[nowl], H[nowr]);      // 初始水量
```

**计算说明**：
- `tmpL = -3` → `nowl = (3+1)/2 = 2`
- 水龙头在位置 2 和 3 之间
- 初始水量 = 两侧较低的柱子高度

### 5.4 主循环

```cpp
while (true) {
    // 找下一个有用柱子
    int nxtL = GetNxt_L(nowl, false);
    int nxtR = GetNxt_R(nowr, false);

    // 边界判断
    if (nxtL == 0 || nxtR == n + 1) {
        // 特殊处理（见下一节）
        break;
    }

    // 扩展
    int ToVal_L = (H[nowl] <= H[nowr] ? nxtL : nowl);
    int ToVal_R = (H[nowl] >= H[nowr] ? nxtR : nowr);
    nowl = ToVal_L;
    nowr = ToVal_R;

    // 更新答案
    ans = (nowr - nowl) * min(H[nowl], H[nowr]);
}
```

---

## 六、特殊情况处理

当某一侧找不到更高的柱子时（到达边界），水会形成"楼梯状"。

### 6.1 楼梯水量计算

**QueryToL**：向左形成楼梯

```cpp
inline int QueryToL(int L, int R) {
    int ans = 0;
    for (int i = L; i <= R; i = GetNxt_R(i, true))
        ans += H[i] * (GetNxt_R(i, true) - i);
    return ans;
}
```

**图示**：
```
位置: 1  2  3  4  5
高度: 1  2  2  3  4
      ║
    ══║
  ════║
████████

楼梯水量 = 1×1 + 2×2 + 3×1 = 1 + 4 + 3 = 8
```

**算法**：
- 从左到右遍历
- 每次跳到下一个**高度更高或相等**的柱子（isSame=true）
- 计算这一层的水量：`高度 × 宽度`

**QueryToR**：向右形成楼梯（对称实现）

```cpp
inline int QueryToR(int L, int R) {
    int ans = 0;
    for (int i = R; i >= L; i = GetNxt_L(i, true))
        ans += H[i] * (i - GetNxt_L(i, true));
    return ans;
}
```

### 6.2 三种边界情况

#### 情况1：左右都到达边界

```cpp
if (nxtL == 0 && nxtR == n + 1) {
    flag = true;

    if (H[nowl] == H[nowr]) {
        // 高度相等：选较少的一侧，填充两倍
        ans += min(QueryToL(1, nowl-1) << 1,
                   QueryToR(nowr+1, n) << 1);
    } else if (H[nowl] < H[nowr]) {
        // 左边低：水向左流，填充左侧楼梯
        ans += QueryToL(1, nowl-1);
    } else {
        // 右边低：水向右流，填充右侧楼梯
        ans += QueryToR(nowr+1, n);
    }
}
```

**为什么高度相等时要乘2？**

```
高度: 2  1  3  3  1  2
         [nowl nowr]

左侧楼梯: 1×1 = 1
右侧楼梯: 1×1 = 1
```
- 水会同时向两边流
- 但两边都形成楼梯，所以选较少的一侧
- 因为是双向流动，所以要乘2

#### 情况2：左边到边界，且水向左流

```cpp
if (nxtL == 0 && nxtR != n + 1 && H[nowl] <= H[nowr]) {
    flag = true;
    ans += QueryToL(1, nowl-1);

    // 如果高度相等，还要考虑向右的情况
    if (H[nowl] == H[nowr])
        ans += min(QueryToL(1, nowl-1),
                   (nxtR - nowr) * H[nowr]);
}
```

**图示**：
```
高度: 1  2  3  3  ?  ?
      ║  ║ [nowl nowr] →nxtR
```
- 左边已经无法扩展（nxtL = 0）
- 右边还能扩展（nxtR ≠ n+1）
- 但水要向左流（H[nowl] ≤ H[nowr]）
- 先填充左侧楼梯
- 如果两边高度相等，还要比较向右延伸的代价

#### 情况3：右边到边界，且水向右流

```cpp
if (nxtL != 0 && nxtR == n + 1 && H[nowl] >= H[nowr]) {
    flag = true;
    ans += QueryToR(nowr+1, n);

    if (H[nowl] == H[nowr])
        ans += min(QueryToR(nowr+1, n),
                   (nowl - nxtL) * H[nowl]);
}
```

**对称于情况2**，处理右边边界的情况。

### 6.3 为什么需要 flag？

```cpp
bool flag = false;
// ... 处理三种情况，成功时设 flag = true
if (flag) break;
```

**作用**：标记是否成功处理了边界情况。

**可能的情况**：
- 左边到边界，但水向右流 → 不处理，继续循环
- 右边到边界，但水向左流 → 不处理，继续循环
- 只有当真正无法扩展时，才设置 flag 并退出

---

## 七、完整代码注释

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define inf 0x7fffffff
using namespace std;
const int _ = 1e4 + 100;

// 快速读入优化
inline int read() {
    char c = getchar();
    int sign = 1;
    int x = 0;
    while (c > '9' || c < '0') {
        if (c == '-') sign = -1;
        c = getchar();
    }
    while (c <= '9' && c >= '0') {
        x *= 10;
        x += c - '0';
        c = getchar();
    }
    return x * sign;
}

int tmpL, tmpR;  // 水龙头位置
int n;           // 柱子数量
int H[_];        // 柱子高度数组

/**
 * 向左找下一个有用柱子
 * @param now 当前位置
 * @param isSame 是否接受相同高度
 * @return 下一个有用柱子的位置，找不到返回0
 */
inline int GetNxt_L(int now, bool isSame) {
    for (int i = now - 1; i >= 0; i--)
        if (H[i] > H[now] || (H[i] == H[now] && isSame))
            return i;
    return 0;
}

/**
 * 向右找下一个有用柱子
 * @param now 当前位置
 * @param isSame 是否接受相同高度
 * @return 下一个有用柱子的位置，找不到返回n+1
 */
inline int GetNxt_R(int now, bool isSame) {
    for (int i = now + 1; i <= n + 1; i++)
        if (H[i] > H[now] || (H[i] == H[now] && isSame))
            return i;
    return n + 1;
}

/**
 * 计算向左流动时的楼梯水量
 * @param L 左边界
 * @param R 右边界
 * @return 楼梯总水量
 */
inline int QueryToL(int L, int R) {
    int ans = 0;
    // 从左到右，每次跳到下一个高度台阶
    for (int i = L; i <= R; i = GetNxt_R(i, true))
        ans += H[i] * (GetNxt_R(i, true) - i);
    return ans;
}

/**
 * 计算向右流动时的楼梯水量
 * @param L 左边界
 * @param R 右边界
 * @return 楼梯总水量
 */
inline int QueryToR(int L, int R) {
    int ans = 0;
    // 从右到左，每次跳到下一个高度台阶
    for (int i = R; i >= L; i = GetNxt_L(i, true))
        ans += H[i] * (i - GetNxt_L(i, true));
    return ans;
}

void doit() {
    // 1. 计算柱子数量
    n = ((abs(tmpL) + abs(tmpR)) >> 1) + 1;

    // 2. 读入柱子高度
    for (int i = 1; i <= n; i++)
        H[i] = read();

    // 3. 设置边界哨兵
    H[0] = H[n + 1] = inf;

    // 4. 初始化水位
    int nowl = ((abs(tmpL) + 1) >> 1);  // 水龙头左侧
    int nowr = nowl + 1;                  // 水龙头右侧
    int ans = min(H[nowl], H[nowr]);      // 初始水量

    // 5. 主循环：不断扩展水域
    while (true) {
        // 5.1 找到左右两侧下一个有用柱子
        int nxtL = GetNxt_L(nowl, false);
        int nxtR = GetNxt_R(nowr, false);

        // 5.2 判断是否到达边界
        if (nxtL == 0 || nxtR == n + 1) {
            bool flag = false;  // 是否成功处理边界

            // 情况1：两边都到达边界
            if (nxtL == 0 && nxtR == n + 1) {
                flag = true;
                ans += (H[nowl] == H[nowr]
                    ? min(QueryToL(1, nowl-1) << 1,
                          QueryToR(nowr+1, n) << 1)
                    : (H[nowl] < H[nowr]
                        ? QueryToL(1, nowl-1)
                        : QueryToR(nowr+1, n)));
            }

            // 情况2：左边到边界，且水向左流
            if (nxtL == 0 && nxtR != n + 1 && H[nowl] <= H[nowr]) {
                flag = true;
                ans += QueryToL(1, nowl-1) +
                       (H[nowl] == H[nowr]
                           ? min(QueryToL(1, nowl-1),
                                 (nxtR - nowr) * H[nowr])
                           : 0);
            }

            // 情况3：右边到边界，且水向右流
            if (nxtL != 0 && nxtR == n + 1 && H[nowl] >= H[nowr]) {
                flag = true;
                ans += QueryToR(nowr+1, n) +
                       (H[nowl] == H[nowr]
                           ? min(QueryToR(nowr+1, n),
                                 (nowl - nxtL) * H[nowl])
                           : 0);
            }

            if (flag) break;  // 成功处理，退出循环
        }

        // 5.3 向较低的一侧扩展
        int ToVal_L = (H[nowl] <= H[nowr] ? nxtL : nowl);
        int ToVal_R = (H[nowl] >= H[nowr] ? nxtR : nowr);

        // 注意：高度相等时，两边都扩展
        nowl = ToVal_L;
        nowr = ToVal_R;

        // 5.4 更新水量（矩形面积）
        ans = (nowr - nowl) * min(H[nowl], H[nowr]);
    }

    // 6. 输出答案（乘以2，题目要求）
    printf("%d\n", ans << 1);
    return;
}

int main() {
    // 多组测试数据
    while (scanf("%d%d", &tmpL, &tmpR) == 2 &&
           tmpL != 0 && tmpR != 0)
        doit();
    return 0;
}
```

---

## 八、复杂度分析

### 8.1 时间复杂度

**GetNxt_L / GetNxt_R**：O(n)
- 最坏情况：从头扫到尾

**主循环**：O(n) 次
- 每次至少扩展一侧
- 最多扩展到两边边界

**QueryToL / QueryToR**：O(n)
- 只在边界时调用一次
- 遍历剩余柱子

**总复杂度**：O(n²)
- 主循环 O(n) × 查找 O(n) = O(n²)

**实际性能**：
- 大部分情况下，有用柱子数量远小于 n
- 实际运行接近 O(n)

### 8.2 空间复杂度

**数组存储**：O(n)
- H[_]：存储柱子高度

**临时变量**：O(1)
- 常数个整型变量

**总复杂度**：O(n)

---

## 九、总结与技巧

### 9.1 核心思想

1. **跳过无用柱子**：只关注能阻挡水流的柱子
2. **矩形面积计算**：直接计算区域水量，避免逐步模拟
3. **双向扩展**：高度相等时同时扩展两侧
4. **边界特判**：到达边界时计算楼梯水量

### 9.2 编程技巧

1. **边界哨兵**：`H[0] = H[n+1] = inf` 简化判断
2. **位运算优化**：`<< 1` 代替 `× 2`，`>> 1` 代替 `÷ 2`
3. **快速读入**：手写 `read()` 函数优化 IO
4. **函数封装**：GetNxt、Query 等函数提高代码可读性

### 9.3 易错点

| 易错点 | 正确做法 |
|--------|----------|
| 高度相等时只扩展一侧 | 应该两侧同时扩展 |
| 忘记处理边界情况 | 三种边界情况都要考虑 |
| 楼梯水量计算错误 | 注意 isSame 参数的使用 |
| 最后输出忘记乘2 | `printf("%d\n", ans << 1)` |
| GetNxt 函数的 isSame 用错 | 扩展用 false，楼梯用 true |

### 9.4 调试技巧

1. **打印区间**：输出每次扩展后的 `[nowl, nowr]`
2. **打印水量**：输出每次更新后的 `ans`
3. **画图理解**：手动画出柱子和水的形状
4. **小数据测试**：用简单例子验证逻辑

### 9.5 扩展思考

**相似问题**：
- 接雨水问题（LeetCode 42）
- 柱状图最大矩形（LeetCode 84）
- 盛最多水的容器（LeetCode 11）

**变种**：
- 如果水从多个位置流入？
- 如果柱子高度动态变化？
- 如果要求最少水量覆盖所有柱子？

---

## 参考资料

- 洛谷题解：https://www.luogu.com.cn/article/1uo46z8b
- UVA Online Judge：Problem 10366

**编写时间**：2025-12-09
**算法标签**：模拟、双指针、区间处理、贪心
