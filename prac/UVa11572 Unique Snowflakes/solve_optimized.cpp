// UVa 11572 - Unique Snowflakes (优化版)
// 时间复杂度: O(n)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<long long> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        // 记录每个元素最后出现的位置
        unordered_map<long long, int> last_pos;

        int L = 0; // 窗口左边界
        int maxLen = 0;

        for (int R = 0; R < n; R++) {
            // 如果 arr[R] 之前出现过，且在当前窗口内
            if (last_pos.count(arr[R]) && last_pos[arr[R]] >= L) {
                // 直接跳到重复位置的下一个
                L = last_pos[arr[R]] + 1;
            }

            // 更新当前元素的位置
            last_pos[arr[R]] = R;

            // 更新最大长度
            maxLen = max(maxLen, R - L + 1);
        }

        cout << maxLen << '\n';
    }

    return 0;
}
