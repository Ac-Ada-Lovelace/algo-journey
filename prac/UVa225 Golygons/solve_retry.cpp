#include <bits/stdc++.h>
using namespace std;
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const noexcept {
        return (static_cast<size_t>(p.first) << 32) |
               static_cast<size_t>(p.second);
    }
};

array<array<int, 2>, 4> directions = {
    {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}}; // right, down, left, up

array<vector<int>, 4> possbile_next = {{{3, 1}, {0, 2}, {1, 3}, {2, 0}}};

unordered_set<pair<int, int>, pair_hash> blocks;

vector<string> dir_str = {"e", "s", "w", "n"};
vector<string> path;
vector<vector<string>> paths;

// @brief DFS search for golygon paths
int dfs(int cur_x, int cur_y, int dir, int step, int max_step) {
    if (step > max_step) {
        if (cur_x == 0 && cur_y == 0) {
            paths.push_back(path);
            return 1;
        } else {
            return 0;
        }
    }

    int blocked = 0;
    int dy = directions[dir][0];
    int dx = directions[dir][1];

    for (int i = 0; i <= step; i++) {
        int ny = cur_y + dy * (i + 1);
        int nx = cur_x + dx * (i + 1);
        if (blocks.count({nx, ny})) {
            blocked = 1;
            break;
        }
    }

    if (!blocked) {
        auto possible_dirs = possbile_next[dir];
        for (auto pd : possible_dirs) {
            path.push_back(dir_str[pd]);
            dfs(cur_x + dx * step, cur_y + dy * step, pd, step + 1, max_step);
            path.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
