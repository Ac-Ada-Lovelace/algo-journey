# 第八章练习题取舍指南

## 核心结论

- 第八章练习题不需要也不应全部完成。
- 建议完成“基础 3 题 + 可选进阶 2 题”；高阶题留到 Volume 2 再做。
- 下方给出精简题单，保证投入产出比。

---

## 题单回顾（源自 `/mnt/data/Beginning_Algorithm_Contests.md`）

书中列出的练习题（按顺序）：

```
8.1  Bin Packing (1149)
8.2  Party Games (1610)
8.3  Bits Equalizer (12545)
8.4  Erasing and Winning (11491)
8.5  Paper Folding (177)
8.6  Crane (1611)
8.7  Generating Permutations (11925)
8.8  Guess (1612)
8.9  K-Graph Oddity (1613)
8.10 Hell on the Markets (1614)
8.11 Highway (1615)
8.12 Keep the Customer Satisfied (1153)
8.13 Meeting with Aliens (10570)
8.14 Caravan Robbers (1616)
8.15 Laptop (1617)
8.16 Weak Key (1618)
8.17 Smallest Sub-Array (11536)
8.18 Feel Good (1619)
8.19 Cricket Field (1312)
8.20 Lazy Susan (1620)
8.21 Jumping Around (1621)
8.22 Robot (1622)
8.23 Enter The Dragon (1623)
8.24 Faucet Flow (10366)
8.25 From D to E and Back (11175)
8.26 Finding Black Circles (12559)
8.27 Pirate Chest (1580)
8.28 Knots (1624)
```

这是一个跨度极大的参考题库，并非需要全部完成。

---

## 分组与优先级

### A 组（强烈推荐，必做）

这些题与例题联系紧密，难度适中。

| 题号 | UVA                              | 关键思想         | 理由                     |
| ---- | -------------------------------- | ---------------- | ------------------------ |
| 8.1  | 1149 Bin Packing                 | 贪心 + 二分或 DP | 经典装箱问题，可迁移性高 |
| 8.3  | 12545 Bits Equalizer             | 贪心 + 分类计数  | 常见技巧紧凑明确         |
| 8.12 | 1153 Keep the Customer Satisfied | 贪心 + 排序      | 与例题形式接近           |
| 8.17 | 11536 Smallest Sub-Array         | 滑动窗口         | 练习滑窗体系             |
| 8.24 | 10366 Faucet Flow                | 二分 + 流体模型  | 二分判定训练的延续       |

做完这 5 题，可完整覆盖“二分 + 贪心 + 滑窗 + 分类计数”。

### B 组（可选做 2～4 题）

稍微抽象但仍属 Volume 1。

| 题号 | UVA                           | 技术点          | 建议           |
| ---- | ----------------------------- | --------------- | -------------- |
| 8.2  | 1610 Party Games              | 排序 + 二分     | 过渡练习       |
| 8.4  | 11491 Erasing and Winning     | 栈 / 贪心       | 字符串贪心典型 |
| 8.7  | 11925 Generating Permutations | 构造            | 脑洞题，可尝试 |
| 8.11 | 1615 Highway                  | 构造 + 数学     | 有趣，可跳过   |
| 8.18 | 1619 Feel Good                | 前缀分布 + 最值 | 中等偏上       |
| 8.19 | 1312 Cricket Field            | 平面区间搜索    | 偏模拟，可做   |

从 B 组选 2～4 题即可，无需全做。

### C 组（暂缓，留到 Volume 2）

难度高、技巧重，当前阶段不建议。

| 题号 | UVA                         | 难点            | 暂缓理由        |
| ---- | --------------------------- | --------------- | --------------- |
| 8.8  | 1612 Guess                  | 深度构造 + 数学 | 超出 Volume 1   |
| 8.9  | 1613 K-Graph Oddity         | 图论结构化      | Volume 1 不处理 |
| 8.10 | 1614 Hell on the Markets    | 财务数学建模    | 非基础算法      |
| 8.13 | 10570 Meeting with Aliens   | 高强度构造      | 作者标注高难    |
| 8.14 | 1616 Caravan Robbers        | 扫描线 + 区间   | Volume 2 再做   |
| 8.20 | 1620 Lazy Susan             | 数学 + 构造     | 当前阶段不合适  |
| 8.21 | 1621 Jumping Around         | 状态设计        | 高阶动态规律    |
| 8.22 | 1622 Robot                  | 几何 + 状态更新 | 高级            |
| 8.23 | 1623 Enter The Dragon       | 状态空间大      | 高级            |
| 8.25 | 11175 From D to E and Back  | 复杂 DP         | 明显 Volume 2   |
| 8.26 | 12559 Finding Black Circles | 图论高级        | 超出范围        |
| 8.27 | 1580 Pirate Chest           | 数学构造        | Volume 2 更合适 |
| 8.28 | 1624 Knots                  | 拓扑几何        | 完全超纲        |

这些题当前做会浪费时间，放到 Volume 2 处理。

---

## 当前建议清单

### 核心必做

1. 1149 Bin Packing
2. 12545 Bits Equalizer
3. 1153 Keep the Customer Satisfied
4. 11536 Smallest Sub-Array
5. 10366 Faucet Flow

### 可选补充（再挑 2～3 题）

6. 1610 Party Games
7. 11491 Erasing and Winning
8. 11925 Generating Permutations
9. 1619 Feel Good

做到 8～10 题即可满足第八章训练需求。

---

## 安排理由

- 当前处于 Volume 1 向 Volume 2 的过渡阶段，目标是形成算法范式。
- 重点培养二分、滑窗、构造、排序 + 贪心的直觉，以及“数据结构替代 DP”的思路。
- 避免在高阶数学构造题上消耗时间和挫败感。书中作者也未要求 Volume 1 全部练习做完。

---

## 可以提供的后续支持

- 每道练习题的问题分析、算法设计关键、分步骤推理。
- C++ STL 模板代码与例题思想关联。
- 或提供一个“第八章练习题 10 天计划”。

---

## 下一步

想先讲解哪一题？Bin Packing（1149）、Bits Equalizer（12545），还是 Smallest Sub-Array（11536）？
