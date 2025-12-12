// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=4494
//
// UVa1619 Feel Good - 单调栈优化版本 O(n)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<long long> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        // 前缀和
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + arr[i];
        }

        // left[i]: 左边第一个小于arr[i]的位置（不存在则为-1）
        // right[i]: 右边第一个小于arr[i]的位置（不存在则为n）
        vector<int> left(n), right(n);
        stack<int> st;

        // 计算left数组
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] >= arr[i]) {
                st.pop();
            }
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        // 清空栈，计算right数组
        while (!st.empty())
            st.pop();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] >= arr[i]) {
                st.pop();
            }
            right[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        // 找最大值
        long long max_val = 0;
        int best_l = 1, best_r = 1;

        for (int i = 0; i < n; i++) {
            // 以arr[i]为最小值的区间是(left[i], right[i])
            int l_pos = left[i] + 1;  // 0-indexed
            int r_pos = right[i] - 1; // 0-indexed

            // 使用前缀和计算区间和: sum[l_pos..r_pos] = prefix[r_pos+1] -
            // prefix[l_pos]
            long long sum = prefix[r_pos + 1] - prefix[l_pos];

            long long val = sum * arr[i];
            if (val > max_val) {
                max_val = val;
                best_l = l_pos + 1; // 转换为1-indexed
                best_r = r_pos + 1; // 转换为1-indexed
            }
        }

        cout << max_val << '\n';
        cout << best_l << ' ' << best_r << '\n';
    }
}
