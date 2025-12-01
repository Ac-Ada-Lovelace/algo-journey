// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=161
// UVa225 Golygons
#include <bits/stdc++.h>
using namespace std;

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const noexcept {
        return (static_cast<size_t>(p.first) << 32) |
               static_cast<size_t>(p.second);
    }
};
map<string, vector<string>> possible_dirs = {
    {"e", {"n", "s"}},
    {"w", {"n", "s"}},
    {"n", {"e", "w"}},
    {"s", {"e", "w"}},
};

void dfs(int len, vector<string>& path, vector<vector<string>>& paths,
         unordered_set<pair<int, int>, pair_hash>& blocks, int x, int y,
         int max_l) {
    if (len == max_l) {
        if (x == 0 && y == 0) {
            paths.push_back(path);
        }
        return;
    }
    string prev_dir = path.back();
    auto possible_next_dirs = possible_dirs[prev_dir];
    for (auto pnd : possible_next_dirs) {
        int nx = x, ny = y;
        if (pnd == "e")
            nx += len + 1;
        else if (pnd == "w")
            nx -= len + 1;
        else if (pnd == "n")
            ny += len + 1;
        else if (pnd == "s")
            ny -= len + 1;
        bool blocked = false;
        if (pnd == "e" || pnd == "w") {
            for (int i = min(x, nx); i <= max(x, nx); i++) {
                if (blocks.count({i, y})) {
                    blocked = true;
                    break;
                }
            }
        } else {
            for (int i = min(y, ny); i <= max(y, ny); i++) {
                if (blocks.count({x, i})) {
                    blocked = true;
                    break;
                }
            }
        }
        if (blocked)
            continue;
        path.push_back(pnd);
        dfs(len + 1, path, paths, blocks, nx, ny, max_l);
        path.pop_back();
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int cases;
    cin >> cases;
    while (cases--) {
        int max_l;
        cin >> max_l;
        int block_num;
        cin >> block_num;
        unordered_set<pair<int, int>, pair_hash> blocks;
        for (int i = 0; i < block_num; i++) {
            int x, y;
            cin >> x >> y;
            blocks.insert({x, y});
        }

        vector<string> path;
        vector<vector<string>> paths;
        vector<string> start_dirs = {"e", "w", "n", "s"};
        for (auto sd : start_dirs) {
            path.push_back(sd);
            int x = 0, y = 0;
            if (sd == "e")
                x += 1;
            else if (sd == "w")
                x -= 1;
            else if (sd == "n")
                y += 1;
            else if (sd == "s")
                y -= 1;
            dfs(1, path, paths, blocks, x, y, max_l);
            path.pop_back();
        }

        for (auto p : paths) {
            for (auto dir : p) {
                cout << dir;
            }
            cout << "\n";
        }
        cout << "Found " << paths.size() << " golygon(s).\n";
        cout << "\n";
    }
}
