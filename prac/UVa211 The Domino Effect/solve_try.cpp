// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=147
// UVa211 The Domino Effect
#include <bits/stdc++.h>
using namespace std;

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const noexcept {
        return (static_cast<size_t>(p.first) << 32) |
               static_cast<size_t>(p.second);
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    queue<string> lines;
    string line;
    unordered_set<pair<int, int>, pair_hash> bone_cards;

    while (getline(cin, line)) {
        lines.push(line);
    }

    while (!lines.empty()) {
        array<array<int, 8>, 7> grid{};
        for (int i = 0; i < 7; ++i) {
            string row = lines.front();
            lines.pop();
            stringstream ss(row);
            for (int j = 0; j < 8; ++j) {
                ss >> grid[i][j];
            }
        }
    }
}
