#include <bits/stdc++.h>
using namespace std;

int chessboard[11][11];
int ida = 0;
int px, py;
int n, m;

int dfs(int depth) {
    if (ida == depth) {
        return 0;
    }
    int nx, ny;

    if (px == m) {
        nx = 1;
        ny = py + 1;
    }
    for (int i = ny;; i++) {
        for (int j = nx; j <= m; j++) {
            if (chessboard[j][i] == 1) {
                // place guard
                vector<pair<int, int>> changed;
                for (int k = 1; k <= n; k++) {
                    if (chessboard[j][k] == 1) {
                        chessboard[j][k] = 0;
                        changed.push_back({j, k});
                    }
                }
                for (int k = 1; k <= m; k++) {
                    if (chessboard[k][i] == 1) {
                        chessboard[k][i] = 0;
                        changed.push_back({k, i});
                    }
                }
                for (int k = 1; k <= n; k++) {
                    int l = i + j - k;
                    if (l >= 1 && l <= m && chessboard[k][l] == 1) {
                        chessboard[k][l] = 0;
                        changed.push_back({k, l});
                    }
                }
                for (int k = 1; k <= n; k++) {
                    int l = k + j - i;
                    if (l >= 1 && l <= m && chessboard[k][l] == 1) {
                        chessboard[k][l] = 0;
                        changed.push_back({k, l});
                    }
                }
                px = j;
                py = i;
                if (dfs(depth + 1) == 0) {
                    return 0;
                }
                // backtrack
                for (auto p : changed) {
                    chessboard[p.first][p.second] = 1;
                }
            }
            nx = 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
