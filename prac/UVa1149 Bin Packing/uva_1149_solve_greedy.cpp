// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=3590
// UVa1149 Bin Packing - 贪心双指针解法
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int tc = 0; tc < T; tc++) {
        // 测试用例之间输出空行（第一个测试用例之前不输出）
        if (tc > 0)
            cout << "\n";

        int n, l;
        cin >> n >> l;

        vector<int> items(n);
        for (int i = 0; i < n; i++) {
            cin >> items[i];
        }

        // 核心：排序，让物品从小到大排列
        sort(items.begin(), items.end());

        int bins = 0;
        int left = 0;      // 指向最小的未处理物品
        int right = n - 1; // 指向最大的未处理物品

        // 双指针贪心
        while (left <= right) {
            // 特殊情况：只剩一个物品
            if (left == right) {
                bins++;
                break;
            }

            // 贪心策略：尝试让最大和最小配对
            if (items[left] + items[right] <= l) {
                // 可以配对：两个物品装入一个箱子
                left++;
                right--;
                bins++;
            } else {
                // 最大的太大，无法和最小的配对
                // 让它单独占一个箱子
                right--;
                bins++;
            }
        }

        cout << bins << "\n";
    }

    return 0;
}
