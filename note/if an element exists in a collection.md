- std::set / std::multiset / std::map / std::multimap：用 find(key) != end() 或 count(key) > 0。
  count 在 set/map 返回 0/1，在 multi 容器返回出现次数。
- std::unordered_set / std::unordered_multiset / std::unordered_map / std::unordered_multimap：同
  上，用 find 或 count；平均 O(1)，遇哈希冲突退化。
- std::vector / std::deque / std::list：用 std::find(begin, end, value) != end()；若已排序的顺序容器
  可用 std::binary_search(begin, end, value)（需要 <algorithm>）。
- std::array：同 vector，用 std::find 或对已排序的用 std::binary_search。
- std::string：用 find(sub) 判断是否含子串：pos != npos。
- std::bitset<N>：用 test(i) 判断第 i 位是否为 1。
- std::priority_queue：无直接存在性查询，需额外数据结构（如 unordered_set 记录存在）。
- std::queue / std::stack：无直接查找接口，需遍历或辅助容器。
- 迭代器失效或访问前需确保容器非空，避免解引用 end()。
