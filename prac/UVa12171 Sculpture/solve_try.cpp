#include <bits/stdc++.h>
#define MAX_BORDER 1000
using namespace std;
void fill_block_surface(
    array<array<array<bool, MAX_BORDER + 2>, MAX_BORDER + 2>, MAX_BORDER + 2>& world, int x, int y,
    int z, int l, int w, int h) {
    // by six surface;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < w; j++) {
            world[x + i][y + j][z] = 1;
            world[x + i][y + j][z + h - 1] = 1;
        }
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < h; j++) {
            world[x + i][y][z + j] = 1;
            world[x + i][y + w - 1][z + j] = 1;
        }
    }
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            world[x][y + i][z + j] = 1;
            world[x + l - 1][y + i][z + j] = 1;
        }
    }
}

array<int, 3> add_block(array<int, 3> a, array<int, 3>& b) {
    array<int, 3> nb;
    for (int i = 0; i < 3; i++) {
        nb[i] = b[i] + a[i];
    }
    return nb;
}

bool is_empty_block(
    const array<array<array<bool, MAX_BORDER + 2>, MAX_BORDER + 2>, MAX_BORDER + 2>& world,
    array<int, 3>& b) {
    return world[b[0]][b[1]][b[2]] == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    while (cases--) {
        array<array<array<bool, MAX_BORDER + 2>, MAX_BORDER + 2>, MAX_BORDER + 2> world{};

        int n = 0;
        cin >> n;
        if (cin.peek() == '\n') {
            cin.ignore();
        }
        while (n--) {
            int x, y, z, l, w, h;
            cin >> x >> y >> z >> l >> w >> h;
            fill_block_surface(world, x, y, z, l, w, h);
            if (cin.peek() == '\n') {
                cin.ignore();
            }
        }

        array<array<array<bool, MAX_BORDER + 2>, MAX_BORDER + 2>, MAX_BORDER + 2> visited{};
        // find six start from six dir;

        int empty_area = 0;
        int faces = 0;
        queue<array<int, 3>> q;
        for (int i = 1; i <= MAX_BORDER; i++) {
            for (int j = 1; j <= MAX_BORDER; j++) {
                if (world[i][j][1] == 0 && visited[i][j][1] == 0) {
                    q.push({i, j, 1});
                    empty_area++;
                    visited[i][j][1] = 1;
                }
                if (world[i][j][MAX_BORDER] == 0 && visited[i][j][MAX_BORDER] == 0) {
                    q.push({i, j, MAX_BORDER});
                    visited[i][j][MAX_BORDER] = 1;
                }
            }
        }
        for (int i = 1; i <= MAX_BORDER; i++) {
            for (int j = 1; j <= MAX_BORDER; j++) {
                if (world[i][1][j] == 0 && visited[i][1][j] == 0) {
                    q.push({i, 1, j});
                    visited[i][1][j] = 1;
                    empty_area++;
                }
                if (world[i][MAX_BORDER][j] == 0 && visited[i][MAX_BORDER][j] == 0) {
                    q.push({i, MAX_BORDER, j});
                    visited[i][MAX_BORDER][j] = 1;
                    empty_area++;
                }
            }
        }
        for (int i = 1; i <= MAX_BORDER; i++) {
            for (int j = 1; j <= MAX_BORDER; j++) {
                if (world[1][i][j] == 0 && visited[1][i][j] == 0) {
                    q.push({1, i, j});
                    visited[1][i][j] = 1;
                    empty_area++;
                }
                if (world[MAX_BORDER][i][j] == 0 && visited[MAX_BORDER][i][j] == 0) {
                    q.push({MAX_BORDER, i, j});
                    visited[MAX_BORDER][i][j] = 1;
                    empty_area++;
                }
            }
        }

        array<array<int, 3>, 6> dir = {
            {{{0, 0, 1}}, {{0, 0, -1}}, {{0, 1, 0}}, {{0, -1, 0}}, {{1, 0, 0}}, {{-1, 0, 0}}}};
        while (!q.empty()) {
            auto b = q.front();
            q.pop();

            for (int i = 0; i < 6; i++) {
                auto nb = add_block(dir[i], b);
                auto is_empty = is_empty_block(world, nb);
                auto is_visited = visited[nb[0]][nb[1]][nb[2]] == 1;
                if (is_empty && !is_visited && nb[0] >= 1 && nb[0] <= MAX_BORDER && nb[1] >= 1 &&
                    nb[1] <= MAX_BORDER && nb[2] >= 1 && nb[2] <= MAX_BORDER) {
                    empty_area++;
                    visited[nb[0]][nb[1]][nb[2]] = 1;
                    q.push(nb);
                }
                if (!is_empty) {
                    faces++;
                }
            }
        }
        cout << faces << MAX_BORDER * MAX_BORDER * MAX_BORDER - empty_area << '\n';
    }
}
