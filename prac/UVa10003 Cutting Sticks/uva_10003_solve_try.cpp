// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=114&page=show_problem&problem=944
// UVa10003 Cutting Sticks
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int l;
    while (cin >> l && l) {
        int n;
        cin >> n;
        vector<int> cuts(n + 2);
        cuts[0] = 0;
        cuts[n + 1] = l;
        for (int i = 1; i <= n; ++i) {
            cin >> cuts[i];
        }

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for (int len = 2; len <= n + 1; ++len) { // 区间长度
            for (int i = 0; i + len <= n + 1; ++i) {
                int j = i + len;
                dp[i][j] = INT_MAX / 2;
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] =
                        min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] - cuts[i]);
                }
            }
        }

        // for (int i = 0; i <= n; ++i) {
        //     for (int j = i + 2; j <= n + 1; ++j) {
        //         dp[i][j] = INT_MAX;
        //         for (int k = i + 1; k < j; ++k) {
        //             dp[i][j] =
        //                 min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] -
        //                 cuts[i]);
        //         }
        //     }
        // }

        cout << "The minimum cutting is " << dp[0][n + 1] << ".\n";
    }
}
