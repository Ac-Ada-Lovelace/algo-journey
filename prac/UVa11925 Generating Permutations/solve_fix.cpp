
#include <bits/stdc++.h>
using namespace std;

/*
  我们做的是“逆向”模拟：
  正向：
      op1: swap front two
      op2: move front to back
  逆向：
      inv(op1) = op1 本身（交换可逆）
      inv(op2) = 把最后一个元素移到最前（rotate right）

  思路：
      给定目标排列 P，把它逆向恢复成 [1,2,...,n]。
      在逆向过程中记录使用的逆操作（操作字符放入 ans）。
      最后把 ans 反转，就是题目需要的正向操作序列。
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    while (cin >> n && n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];

        deque<int> dq(a.begin(), a.end()); // 用 deque 表示队列
        string rev_ops;                    // 保存逆向操作序列（稍后反转）

        auto is_sorted = [&](const deque<int>& q) {
            for (int i = 0; i < (int)q.size(); ++i)
                if (q[i] != i + 1)
                    return false;
            return true;
        };

        /*
           逆向规则（与题解逻辑完全一致）：
             若 dq[0] < dq[1] 或者 (dq[0] == n && dq[1] == 1)
                 → 执行逆向 op2 ：把最后一个移到最前
             否则
                 → 执行 swap 前两项
        */

        while (!is_sorted(dq)) {
            int x = dq[0], y = dq[1];

            bool rising = (x < y) || (x == n && y == 1); // 环形意义下的升序

            if (rising) {
                // === 逆向 op2: move last → front ===
                int last = dq.back();
                dq.pop_back();
                dq.push_front(last);
                rev_ops.push_back('2');
            } else {
                // === 逆向 op1: swap front two ===
                swap(dq[0], dq[1]);
                rev_ops.push_back('1');
            }
        }

        // rev_ops 是逆向操作，所以要反转成为正向输出
        reverse(rev_ops.begin(), rev_ops.end());

        cout << rev_ops << "\n";
    }

    return 0;
}
