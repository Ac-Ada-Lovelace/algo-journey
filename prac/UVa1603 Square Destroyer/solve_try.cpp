// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=841&page=show_problem&problem=4478
// UVa1603 Square Destroyer
#include <bits/stdc++.h>
using namespace std;

struct GridMaps {
    map<int, vector<int>> square_stick_static; // square_id -> sticks
    map<int, vector<int>> stick_square_static; // stick_id -> squares
    int total_stick_num = 0;
};

void build_grid_maps(int grid_size, GridMaps& gm) {
    // 题面编号：每行先横边，再竖边，最后一行横边单独编号。
    int h[6][5] = {}; // n<=5
    int v[5][6] = {};
    int id = 1;
    for (int r = 0; r < grid_size; ++r) {
        for (int c = 0; c < grid_size; ++c)
            h[r][c] = id++; // 横
        for (int c = 0; c <= grid_size; ++c)
            v[r][c] = id++; // 竖
    }
    for (int c = 0; c < grid_size; ++c)
        h[grid_size][c] = id++; // 最后一行横边
    gm.total_stick_num = id - 1;

    for (int square_size = 1; square_size <= grid_size; square_size++) {
        for (int row = 0; row <= grid_size - square_size; row++) {
            for (int col = 0; col <= grid_size - square_size; col++) {
                vector<int> sticks_in_square;

                for (int k = 0; k < square_size; k++) {
                    sticks_in_square.push_back(h[row][col + k]); // 上
                    sticks_in_square.push_back(
                        h[row + square_size][col + k]);          // 下
                    sticks_in_square.push_back(v[row + k][col]); // 左
                    sticks_in_square.push_back(
                        v[row + k][col + square_size]); // 右
                }

                int square_id =
                    (square_size << 16) | (row << 8) | col; // 唯一标识
                gm.square_stick_static[square_id] = sticks_in_square;
                for (int stick_id : sticks_in_square) {
                    gm.stick_square_static[stick_id].push_back(square_id);
                }
            }
        }
    }
}

int limitDepth;
vector<vector<int>> gSquares; // 方形 -> 边列表

bool dfs(vector<char>& present, int depth) {
    int target_idx = -1;
    for (int i = 0; i < (int)gSquares.size(); ++i) {
        bool full = true;
        for (int e : gSquares[i]) {
            if (!present[e]) {
                full = false;
                break;
            }
        }
        if (full) {
            target_idx = i;
            break;
        }
    }
    if (target_idx == -1)
        return true; // 没有完整方形
    if (depth == limitDepth)
        return false;

    for (int e : gSquares[target_idx]) {
        if (!present[e])
            continue;
        present[e] = 0;
        if (dfs(present, depth + 1))
            return true;
        present[e] = 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    if (!(cin >> cases))
        return 0;

    vector<GridMaps> cache(6); // n<=5

    while (cases--) {
        int grid_size;
        cin >> grid_size;

        if (cache[grid_size].total_stick_num == 0) {
            build_grid_maps(grid_size, cache[grid_size]);
        }
        const GridMaps& gm = cache[grid_size];
        gSquares.clear();
        gSquares.reserve(gm.square_stick_static.size());
        for (auto& kv : gm.square_stick_static)
            gSquares.push_back(kv.second);

        int removed_stick_num;
        cin >> removed_stick_num;
        vector<int> removed_sticks(removed_stick_num);
        for (int i = 0; i < removed_stick_num; i++)
            cin >> removed_sticks[i];

        vector<char> present(gm.total_stick_num + 1, 1); // 1-based
        for (int id : removed_sticks)
            present[id] = 0;

        int answer = 0;
        for (limitDepth = 0;; ++limitDepth) {
            if (dfs(present, 0)) {
                answer = limitDepth;
                break;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
