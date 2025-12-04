// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=4479
// UVa1604 Cubic Eight-Puzzle - BFS Solution
#include <bits/stdc++.h>
using namespace std;

// Color encoding: 00=Blue(B), 01=White(W), 10=Red(R)
struct cubic {
    // vertical: [bottom(7-6)][back(5-4)][top(3-2)][front(1-0)]
    char vertical;
    // horizontal: [bottom(7-6)][left(5-4)][top(3-2)][right(1-0)]
    char horizontal;

    static const char BLUE = 0b00;
    static const char WHITE = 0b01;
    static const char RED = 0b10;

    cubic() {
        // Initial: Top=White, Bottom=White, Front=Red, Back=Red, Left=Blue, Right=Blue
        vertical = (WHITE << 6) | (RED << 4) | (WHITE << 2) | RED;
        horizontal = (WHITE << 6) | (BLUE << 4) | (WHITE << 2) | BLUE;
    }

    char get_top() const {
        return (vertical >> 2) & 0b11;
    }

    char color_to_char(char color) const {
        if (color == BLUE) return 'B';
        if (color == WHITE) return 'W';
        if (color == RED) return 'R';
        return '?';
    }

    void roll(int dx, int dy) {
        if (dx != 0) {
            // Vertical roll
            if (dx == 1) {
                char front = vertical & 0b11;
                vertical >>= 2;
                vertical |= (front << 6);
            } else {
                char bottom = (vertical >> 6) & 0b11;
                vertical = ((vertical << 2) & 0b11111111) | bottom;
            }
            char v_top = (vertical >> 2) & 0b11;
            char v_bottom = (vertical >> 6) & 0b11;
            horizontal = (horizontal & 0b00110011) | (v_bottom << 6) | (v_top << 2);
        } else {
            // Horizontal roll
            if (dy == 1) {
                char right = horizontal & 0b11;
                horizontal >>= 2;
                horizontal |= (right << 6);
            } else {
                char bottom = (horizontal >> 6) & 0b11;
                horizontal = ((horizontal << 2) & 0b11111111) | bottom;
            }
            char h_top = (horizontal >> 2) & 0b11;
            char h_bottom = (horizontal >> 6) & 0b11;
            vertical = (vertical & 0b00110011) | (h_bottom << 6) | (h_top << 2);
        }
    }
};

struct State {
    array<cubic, 9> cubes;  // cubes[0] unused, cubes[1-8] are the 8 cubes
    char grid[3][3];        // grid[i][j] = cube index (0 = empty)
    int ex, ey;             // empty position (0-indexed)
    int steps;

    string get_hash() const {
        string hash;
        hash.reserve(18);
        for (int i = 1; i <= 8; i++) {
            hash.push_back(cubes[i].vertical);
            hash.push_back(cubes[i].horizontal);
        }
        hash.push_back(static_cast<char>(ex));
        hash.push_back(static_cast<char>(ey));
        return hash;
    }

    bool check_goal(const char target[3][3]) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == 0) {
                    if (target[i][j] != 'E') return false;
                } else {
                    char top_color = cubes[grid[i][j]].color_to_char(cubes[grid[i][j]].get_top());
                    if (top_color != target[i][j]) return false;
                }
            }
        }
        return true;
    }
};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int bfs(State initial, const char target[3][3]) {
    if (initial.check_goal(target)) {
        return 0;
    }

    queue<State> q;
    unordered_set<string> visited;

    q.push(initial);
    visited.insert(initial.get_hash());

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.steps >= 30) {
            continue;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nx = curr.ex + dx[dir];
            int ny = curr.ey + dy[dir];

            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) {
                continue;
            }

            // Create new state
            State next = curr;
            next.steps = curr.steps + 1;

            // Roll the cube at (nx, ny)
            int cube_id = curr.grid[nx][ny];
            next.cubes[cube_id].roll(dx[dir], dy[dir]);

            // Move empty space
            swap(next.grid[curr.ex][curr.ey], next.grid[nx][ny]);
            next.ex = nx;
            next.ey = ny;

            // Check if visited
            string hash = next.get_hash();
            if (visited.count(hash)) {
                continue;
            }
            visited.insert(hash);

            // Check goal
            if (next.check_goal(target)) {
                return next.steps;
            }

            q.push(next);
        }
    }

    return -1;
}

array<string,3> visualize_target(const char target[3][3]) {
    array<string,3> visual;
    for (int i = 0; i < 3; i++) {
        visual[i] = "";
        for (int j = 0; j < 3; j++) {
            visual[i] += target[i][j];
        }
    }
    return visual;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int ex, ey;
    while (cin >> ex >> ey && (ex || ey)) {
        char target[3][3];
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                cin >> target[i][j];
            }
        }

        // Initialize state
        State initial;
        initial.steps = 0;
        initial.ex = ex - 1;
        initial.ey = ey - 1;

        for (int i = 0; i < 9; i++) {
            initial.cubes[i] = cubic();
        }

        int count = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == ex - 1 && j == ey - 1) {
                    initial.grid[i][j] = 0;
                } else {
                    initial.grid[i][j] = count++;
                }
            }
        }

        int result = bfs(initial, target);
        cout << result << "\n";
    }
}
