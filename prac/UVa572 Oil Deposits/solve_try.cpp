#include <bits/stdc++.h>
#include <cstddef>
using namespace std;

void dfs_expand(queue<pair<int, int>>& vis_q, vector<vector<int>>& visited, vector<string>& grid,
                size_t rows, size_t cols) {
    if (vis_q.empty())
        return;

    const int row_limit = static_cast<int>(rows);
    const int col_limit = static_cast<int>(cols);

    auto curr = vis_q.front();
    vis_q.pop();
    auto x = curr.first;
    auto y = curr.second;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            int nx = x + i;
            int ny = y + j;
            if (nx < 0 || ny < 0 || nx >= row_limit || ny >= col_limit)
                continue;
            if (grid[nx][ny] == '@' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                vis_q.push({nx, ny});
            }
        }
    }
    dfs_expand(vis_q, visited, grid, rows, cols);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t rows, cols;
    while (cin >> rows >> cols) {
        if (!rows && !cols)
            break;
        vector<string> grid(rows);
        for (size_t i = 0; i < rows; i++)
            cin >> grid[i];
        vector<vector<int>> visited(rows, vector<int>(cols, false));

        int num = 0;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (grid[i][j] == '@' && !visited[i][j]) {
                    num++;
                    visited[i][j] = true;
                    queue<pair<int, int>> vis_q;
                    vis_q.push({i, j});
                    dfs_expand(vis_q, visited, grid, rows, cols);
                }
            }
        }

        cout << num << endl;
    }
}
