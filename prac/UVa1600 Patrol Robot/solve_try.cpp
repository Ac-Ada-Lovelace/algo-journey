// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=839&page=show_problem&problem=4475
// UVa1600 Patrol Robot
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sstream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int m, n;
        cin >> m >> n;
        int k;
        cin >> k;
        cin.ignore();

        vector<vector<int>> grid(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; ++i) {
            string s;
            getline(cin, s);
            stringstream ss(s);
            for (int j = 1; j <= n; ++j) {
                int x = 0;
                ss >> x;
                grid[i][j] = x;
            }
        }

        queue<tuple<int, int, int>> q;
        vector<vector<int>> visited(m + 1, vector<int>(n + 1, -1));
        q.push({1, 1, k});
        visited[1][1] = 0;
        vector<array<int, 2>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            auto curr = q.front();
            auto [x, y, rem] = curr;
            q.pop();
            if (x == m && y == n) {
                continue;
            }
            for (int i = 0; i < 4; i++) {
                auto nx = x + directions[i][0];
                auto ny = y + directions[i][1];
                if (nx < 1 || nx > m || ny < 1 || ny > n)
                    continue;            // out of bound
                if (grid[nx][ny] == 1) { // obstacle
                    if (rem > 0 && (visited[nx][ny] == -1 ||
                                    visited[nx][ny] > grid[x][y] + 1)) {
                        visited[nx][ny] = grid[x][y] + 1;
                        q.push({nx, ny, rem - 1});
                    }
                } else { // free cell
                    if (visited[nx][ny] == -1 ||
                        visited[nx][ny] > grid[x][y] + 1) {
                        visited[nx][ny] = grid[x][y] + 1;
                        q.push({nx, ny, rem});
                    }
                }
            }
        }
        cout<< visited[m][n] << "\n";
    }
}
