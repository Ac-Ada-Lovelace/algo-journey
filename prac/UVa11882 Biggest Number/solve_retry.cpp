#include <bits/stdc++.h>
using namespace std;

array<vector<pair<int, int>>, 9> possible_start;
array<array<char, 15>, 15> grid;
array<array<bool, 15>, 15> visited;
array<int, 4> dx = {0, 0, 1, -1};
array<int, 4> dy = {1, -1, 0, 0};
int r, c;

string _max;

void dfs(int x, int y, string& curr) {
    int nx, ny;
    vector<pair<int, int>> next_positions;
    for (int i = 0; i < 4; i++) {
        nx = x + dx[i];
        ny = y + dy[i];
        if (nx >= 0 && nx < r && ny >= 0 && ny < c && grid[nx][ny] != '#' &&
            !visited[nx][ny]) {
            next_positions.emplace_back(nx, ny);
        }
    }
    if (next_positions.empty()) {
        if (curr.size() > _max.size() ||
            (curr.size() == _max.size() && curr > _max)) {
            _max = curr;
        }
    }
    for (auto nn : next_positions) {
        curr.push_back(grid[nn.first][nn.second]);
        visited[nn.first][nn.second] = true;
        dfs(nn.first, nn.second, curr);
        visited[nn.first][nn.second] = false;
        curr.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (true) {
        cin >> r >> c;
        if (r == 0 && c == 0)
            break;
        cin.ignore();
        possible_start.fill({});
        grid.fill({});
        _max = "";
        for (int i = 0; i < r; i++) {
            string line;
            getline(cin, line);

            for (int j = 0; j < c; j++) {
                if (isdigit(line[j])) {
                    int digit = line[j] - '0';
                    possible_start[digit - 1].emplace_back(i, j);
                }
                grid[i][j] = line[j];
            }
        }

        for (auto p : possible_start) {
            for (auto start : p) {
                visited.fill({});
                visited[start.first][start.second] = true;
                string curr;
                curr.push_back(grid[start.first][start.second]);
                dfs(start.first, start.second, curr);
            }
        }
        cout << _max << '\n';
    }
    cout << endl;
}
