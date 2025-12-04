#include <bits/stdc++.h>
using namespace std;

array<array<int, 8>, 7> grid{};
array<array<int, 8>, 7> filled{};
array<int, 29> used_bones{};

int bone_id(int a, int b) {
    if (a > b)
        swap(a, b);
    return a * 7 - (a * (a - 1)) / 2 + (b - a) + 1;
}

array<array<int, 2>, 4> arrounds = {
    {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}}; // up, right, down, left

pair<int, int> find_next_empty() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 8; j++) {
            if (!filled[i][j]) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int dfs(int x, int y, int used_count) {
    if (used_count == 28) {
        return 1;
    }

    int cur_num = grid[x][y];
    for (int i = 0; i < 4; i++) {
        int nx = x + arrounds[i][0];
        int ny = y + arrounds[i][1];
        if (nx < 0 || nx >= 7 || ny < 0 || ny >= 8)
            continue;
        if (filled[nx][ny])
            continue;
        int another_num = grid[nx][ny];
        int possible_bone = bone_id(cur_num, another_num);
        if (used_bones[possible_bone])
            continue;
        filled[x][y] = 1;
        filled[nx][ny] = 1;
        used_bones[possible_bone] = 1;

        pair<int, int> next_empty = find_next_empty();
        if (next_empty.first == -1 && next_empty.second == -1) {
            return 1;
        }
        dfs(next_empty.first, next_empty.second, used_count + 1);

        filled[x][y] = 0;
        filled[nx][ny] = 0;
        used_bones[possible_bone] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    int line_index = 0;
    while (getline(cin, line)) {
        if (line.empty())
            break;

        while (line_index < 7) {
            stringstream ss(line);
            for (int j = 0; j < 8; ++j) {
                ss >> grid[line_index][j];
                filled[line_index][j] = 0;
            }
            line_index++;
            if (line_index < 7)
                getline(cin, line);
        }

        line_index = 0;
    }
}
