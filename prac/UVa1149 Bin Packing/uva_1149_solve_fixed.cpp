// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=3590
// UVa1149 Bin Packing
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 0; tc < T; tc++) {
        if (tc > 0) cout << "\n";  // 测试用例之间输出空行

        int n, l;
        cin >> n >> l;

        vector<int> items(n);
        for (int i = 0; i < n; i++) {
            cin >> items[i];
        }

        // 排序
        sort(items.begin(), items.end());

        int bins = 0;
        int left = 0, right = n - 1;

        while (left <= right) {
            if (left == right) {
                // 只剩一个物品
                bins++;
                break;
            }

            if (items[left] + items[right] <= l) {
                // 最小和最大可以配对
                left++;
                right--;
                bins++;
            } else {
                // 最大的太大，单独放一个箱子
                right--;
                bins++;
            }
        }

        cout << bins << "\n";
    }

    return 0;
}
