#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    while (cin >> m >> n) {
        vector<vector<int>> w(m, vector<int>(n));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> w[i][j];

        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            dp[0][i] = w[0][i];
        }

        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0) {
                    dp[i][j] = w[i][j] + min(dp[i - 1][j], dp[i - 1][j + 1]);
                } else if (j == n - 1) {
                    dp[i][j] = w[i][j] + min(dp[i - 1][j], dp[i - 1][j - 1]);
                } else {
                    dp[i][j] = w[i][j] + min({dp[i - 1][j - 1], dp[i - 1][j],
                                              dp[i - 1][j + 1]});
                }
            }
        }

        int _min = INT_MAX;
        for (int i = 0; i < n; i++) {
            _min = min(_min, dp[m - 1][i]);
        }

        cout<< _min << "\n";
    }
}
