# 快速排序笔记

## 核心思想

- 分治：选一个枢轴，将区间分成“小于枢轴”“大于枢轴”的两段，再递归排序两侧。
- 目标是原地完成排序，平均 O(n log n)，但枢轴极端偏斜时会退化到 O(n^2)。

## 分区策略

- 枢轴选择：右端、随机、三数取中均可；随机或三数取中能显著降低最坏情况概率。
- Lomuto 分区：用一个指针维护“已放好小于 pivot 的末端”，线性扫描交换。
- Hoare 分区：双指针从两端向内走，找到逆序对就交换，停在交叉处。
- 三路分区：将区间切成 `< pivot`、`== pivot`、`> pivot` 三段，适合大量重复值。

## 基础流程（Lomuto 伪代码）

```text
quickSort(a, l, r):
  if l >= r: return
  pivot = a[r]
  i = l
  for j in [l, r):
    if a[j] < pivot:
      swap(a[i], a[j]); i++
  swap(a[i], a[r])
  quickSort(a, l, i - 1)
  quickSort(a, i + 1, r)
```

## Hoare 分区要点

- `pivot = a[l]` 常见；`i = l - 1, j = r + 1`，循环：
  - `do i++ while a[i] < pivot`
  - `do j-- while a[j] > pivot`
  - 若 `i >= j` 返回 `j`，否则交换 `a[i], a[j]`
- 递归时区间划分为 `[l, p]` 与 `[p + 1, r]`。

## 随机化与三路

- 随机化：在分区前交换 `a[r]` 与区间内随机元素，平摊复杂度保持 O(n log n)。
- 三路快排伪代码核心：
  - 维护 `lt`（< pivot 的尾）、`i`（扫描指针）、`gt`（> pivot 的头）。
  - `a[i] < pivot` → 交换到 `lt` 区，`lt++、i++`；`a[i] > pivot` → 交换到 `gt` 区，`gt--`；相等则 `i++`。

## 复杂度与性质

- 平均时间 O(n log n)，最坏 O(n^2)（枢轴极度偏斜）。
- 额外空间 O(log n)（递归栈）；原地、不稳定。
- 常数因子小，实际表现优秀；尾递归可转换或总是优先递归较小段以压栈深。

## 实用细节

- 小区间（如 ≤16）可改用插入排序以提升常数。
- Hoare 分区与 Lomuto 返回值不同，递归边界不能混用。
- 若数据近乎有序且枢轴选择固定端点，退化风险大；务必随机化或三数取中。
- 若需要稳定性，应换别的排序或额外存储位置。

## 常见坑

- 递归边界写错：Lomuto 分区枢轴最终在 `i`，递归应跳过它。
- Hoare 分区返回位置和 pivot 值分离，错误的边界会导致死循环或越界。
- 重复值多而仍用二路分区，可能造成深递归；三路分区更稳。
- 随机数取模用错区间或忘记包含端点，导致偏置。

## 简洁 C++ 示例（随机 + Lomuto）

```cpp
void quicksort(vector<int>& a, int l, int r) {
  if (l >= r) return;
  int p = l + rand() % (r - l + 1);
  swap(a[p], a[r]);  // 随机化枢轴
  int pivot = a[r], i = l;
  for (int j = l; j < r; ++j) {
    if (a[j] < pivot) swap(a[i++], a[j]);
  }
  swap(a[i], a[r]);
  quicksort(a, l, i - 1);
  quicksort(a, i + 1, r);
}
```

