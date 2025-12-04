# 归并排序完整笔记

## 核心思想

- “分而治之”：把数组递归切成两半，分别排好序，再用线性时间合并成一个有序数组。
- 合并阶段是两个有序序列的“双指针竞速”，每次取更小（或更大）的元素写入临时数组，再拷贝回原数组。
- 全程比较次数上界约为 n log n，且复杂度与输入分布无关（不受逆序或随机性影响）。

## 基础流程（自顶向下递归）

1. 终止条件：区间长度 ≤ 1 直接返回。
2. 分割：mid = (l + r) / 2，递归排好 [l, mid] 与 [mid+1, r]。
3. 合并：用两个指针 i, j 扫描左右两段，用一个写指针 k 写入临时数组 temp。
4. 收尾：把 temp 写回原区间，保证原数组对应位置已排序。

### 伪代码（升序）

```text
mergeSort(a, l, r):
  if l >= r: return
  m = (l + r) / 2
  mergeSort(a, l, m)
  mergeSort(a, m + 1, r)
  merge(a, l, m, r)  // 合并两个有序段
```

### 合并细节

- while i <= m 且 j <= r：如果 a[i] ≤ a[j]，先写 a[i]；否则写 a[j]。用 ≤ 能保持稳定性。
- 把剩余的尾巴直接拷入 temp，最后一次性复制回原数组的 [l, r]。
- temp 的分配方式：
  - 预先全局分配一次，再在合并时复用，避免频繁 new。
  - 若语言支持切片，传入 temp 的子切片也可行，但要注意覆盖区间。

## 复杂度与性质

- 时间：O(n log n)（递归高度 log n，每层合并 O(n)）。
- 空间：O(n) 额外空间，用于临时数组。原地版较复杂，通常不必实现。
- 稳定：只要在比较相等时优先取左段元素，就保持稳定。
- 适合大数据、几乎有序、完全逆序等场景，性能稳定，不会退化。

## 自底向上（迭代版）要点

- 外层循环按步长 step = 1, 2, 4, 8 ...；每次把相邻的两个有序块合并。
- 对长度不足 step 的尾段，合并时注意右端点不能越界：`mid = min(l + step - 1, n-1)`，`r = min(l + 2*step - 1, n-1)`。
- 迭代版省掉递归栈，但仍需 O(n) 的临时数组。

## 常见坑

- 忘记稳定性细节：相等时必须先写左段元素。
- 临时数组复用位置错：应写回原数组的同一 [l, r] 区间，否则覆盖别的部分。
- 中点计算溢出：用 `m = l + (r - l) / 2` 更安全（尤其在 32 位 int 时）。
- 复制回原数组时漏掉区间左偏移：`a[l + t] = temp[t]`。
- 迭代版边界：最后一块不足 2\*step 时，右端点需要取 min；可能存在“只有左块没有右块”的情况，直接跳过合并。

## 与快速排序对比（简洁对照）

- 归并：时间稳定 O(n log n)，需 O(n) 额外空间，天然稳定；最适合链表或需要稳定性的场景。
- 快排：原地、常数因子小，但最坏 O(n^2)；若要稳定需额外结构。

## 实用模板（C++ 思路）

- 全局 `vector<int> a, tmp;`，tmp 大小等于 a。
- `merge_sort(l, r)` 递归；`merge(l, m, r)` 写入 tmp，然后 `copy(tmp.begin()+l, tmp.begin()+r+1, a.begin()+l)`.
- 若要支持自定义比较，只需把“更小”改为比较函数。

## 测试用例建议

- 空数组或单元素（应直接返回）。
- 已排序、完全逆序、含大量重复值。
- 长度为奇数、偶数、小于步长、刚好是 2 的幂。
- 自底向上版：尾段长度介于 step 和 2\*step 之间，验证越界处理。

## 实现示例 （C++）

### 递归实现

```cpp
  void merge_sort(vector<int>& a, vector<int>& buf, int l, int r) {
      if (r - l <= 1) return;
      int m = l + (r - l) / 2;
      merge_sort(a, buf, l, m);
      merge_sort(a, buf, m, r);
      int i = l, j = m, k = l;
      while (i < m && j < r) buf[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
      while (i < m) buf[k++] = a[i++];
      while (j < r) buf[k++] = a[j++];
      for (int t = l; t < r; ++t) a[t] = buf[t];
  }

  // 调用
  vector<int> a = {5,2,4,6,1,3};
  vector<int> buf(a.size());
  merge_sort(a, buf, 0, a.size());

```

### 迭代版本（自底向上）：

```cpp
  void merge_sort_iter(vector<int>& a) {
      vector<int> buf(a.size());
      for (size_t width = 1; width < a.size(); width *= 2) {
          for (size_t l = 0; l < a.size(); l += 2 * width) {
              size_t m = min(l + width, a.size());
              size_t r = min(l + 2 * width, a.size());
              size_t i = l, j = m, k = l;
              while (i < m && j < r) buf[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
              while (i < m) buf[k++] = a[i++];
              while (j < r) buf[k++] = a[j++];
          }
          swap(a, buf);
      }
  }
```
