// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=114&page=show_problem&problem=52
// UVa116 Unidirectional TSP
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m, n;
    while (cin >> m >> n) {
        vector<vector<int>> w(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> w[i][j];

        const int INF = 1e9;
        vector<vector<int>> dp(m, vector<int>(n));
        vector<vector<int>> nxt(m, vector<int>(n));

        // 初始化最后一列
        for (int r = 0; r < m; r++)
            dp[r][n - 1] = w[r][n - 1];

        // 从右往左 DP
        for (int c = n - 2; c >= 0; c--) {
            for (int r = 0; r < m; r++) {
                // 三个候选行
                vector<int> cand = {(r - 1 + m) % m, r, (r + 1) % m};
                sort(cand.begin(), cand.end()); // 按字典序排序

                // 找最优
                int best = INF;
                int best_row = -1;
                for (int nr : cand) {
                    if (dp[nr][c + 1] < best) {
                        best = dp[nr][c + 1];
                        best_row = nr;
                    }
                }

                dp[r][c] = w[r][c] + best;
                nxt[r][c] = best_row;
            }
        }

        // 从 dp[*][0] 找最小起点
        int start = 0;
        for (int r = 1; r < m; r++)
            if (dp[r][0] < dp[start][0])
                start = r;

        // 输出路径
        vector<int> path;
        int r = start;
        for (int c = 0; c < n; c++) {
            path.push_back(r + 1); // 行号从1开始
            r = nxt[r][c];
        }

        for (int i = 0; i < n; i++) {
            if (i)
                cout << " ";
            cout << path[i];
        }
        cout << "\n" << dp[start][0] << "\n";
    }
    return 0;
}
