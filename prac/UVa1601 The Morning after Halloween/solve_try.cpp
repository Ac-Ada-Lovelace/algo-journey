// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=841&page=show_problem&problem=4476
// UVa1601 The Morning after Halloween
#include <bits/stdc++.h>
using namespace std;

struct ghost {
    int x, y;
    int goal_x, goal_y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;

    while (getline(cin, line)) {
        stringstream ss(line);
        int w, h, n;
        ss >> w >> h >> n;
        string map_line;
        vector<vector<char>> grid(h, vector<char>(w));

        map<string, ghost> ghosts;
        for (int i = 0; i < h; i++) {
            getline(cin, map_line);
            stringstream map_ss(map_line);
            char cell;
            for (int j = 0; j < w; j++) {
                map_ss >> cell;
                if (isalpha(cell)) {
                    if (ghosts.count(string(1, cell)) == 0) {
                        ghosts[string(1, cell)] = {-1, -1, -1, -1};
                    } else if (islower(cell)) {
                        ghosts[string(1, cell)].x = j;
                        ghosts[string(1, cell)].y = i;

                    } else {
                        ghosts[string(1, cell)].goal_x = j;
                        ghosts[string(1, cell)].goal_y = i;
                    }
                }

                grid[i][j] = cell;
            }
        }
    }
}
