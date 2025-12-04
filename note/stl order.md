STL 容器与算法的顺序 / 比较关系速查：

- 有序关联容器 set/map/multiset/multimap：默认 `std::less`，遍历和 `lower_bound` 等按
  升序；自定义比较器就按该“谁更小”规则有序。
- priority_queue / heap：默认 `std::less` → 最大堆（top 最大）；用 `std::greater` 变小根
  堆；`make_heap/push_heap/pop_heap` 与 `priority_queue` 同步。
- sort/stable_sort/partial_sort：默认 `<` 升序；传比较器时“返回 true 表示在前面”。
- nth_element：把第 n 个放到排序后该在的位置；左右分区都按同一个比较规则。
- lower_bound/upper_bound/equal_range/binary_search：依赖区间当前排序规则；`lower_bound`
  找第一个“非更小”（默认就是 `>=`），`upper_bound` 找第一个“更大”。
- merge、set_union/intersection/difference/symmetric_difference：输入区间必须按同一比较
  规则有序，输出也保持该顺序。
- next_permutation/prev_permutation：按比较器的字典序（默认 `<`）；`min/max/_element` 默认
  `<`，`minmax_element` 同。
- 顺序容器：vector/deque/list/forward_list/array/string 按索引或插入顺序；queue FIFO，
  stack LIFO；unordered\* 容器遍历无序。
