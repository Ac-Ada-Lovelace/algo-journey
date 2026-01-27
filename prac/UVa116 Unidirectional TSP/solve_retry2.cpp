#include <bits/stdc++.h>
#include <climits>
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

        vector<vector<int>> dp(m, vector<int>(n));
        for (int i = 0; i < n; i++) {
            dp[0][i] = w[0][i];
        }

        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int left_up = dp[(i - 1 + m) % m][(j - 1 + n) % n];
                int left = dp[i][(j - 1 + n) % n];
                int left_down = dp[(i + 1) % m][(j - 1 + n) % n];
                dp[i][j] = w[i][j] + min({left_up, left, left_down});
            }
        }

        int _min = INT_MAX;
        for (int i = 0; i < m; i++) {
            _min = min(_min, dp[i][n - 1]);
        }

    }
}
