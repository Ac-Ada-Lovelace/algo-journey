// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=4479
// UVa1604 Cubic Eight-Puzzle
#include <bits/stdc++.h>
using namespace std;

// Color encoding: 00=Blue(B), 01=White(W), 10=Red(R)
// Based on Figure 3 and Figure 4 in PDF:
// Initial orientation: Top=White, Bottom=White, Front=Red, Back=Red, Left=Blue,
// Right=Blue

struct cubic {
    // vertical: [bottom(7-6)][back(5-4)][top(3-2)][front(1-0)]
    char vertical;

    // horizontal: [bottom(7-6)][left(5-4)][top(3-2)][right(1-0)]
    char horizontal;

    // Color constants
    static const char BLUE = 0b00;
    static const char WHITE = 0b01;
    static const char RED = 0b10;

    // Initial state according to Figure 4
    // Top=White, Bottom=White, Front=Red, Back=Red, Left=Blue, Right=Blue
    cubic() {
        vertical = (WHITE << 6) | (RED << 4) | (WHITE << 2) | RED;
        horizontal = (WHITE << 6) | (BLUE << 4) | (WHITE << 2) | BLUE;
    }

    char get_top() const {
        return (vertical >> 2) & 0b11; // bit 3-2
    }

    char color_to_char(char color) const {
        if (color == BLUE)
            return 'B';
        if (color == WHITE)
            return 'W';
        if (color == RED)
            return 'R';
        return '?';
    }

    // Roll the cube when empty space moves to this cube's position
    // dx: -1=up, 1=down (y direction change)
    // dy: -1=left, 1=right (x direction change)
    void roll(int dx, int dy) {
        if (dx != 0) {
            // Vertical roll: front->top->back->bottom->front cycle
            if (dx == 1) {
                // Roll down
                char front = vertical & 0b11;
                vertical >>= 2;
                vertical |= (front << 6);
            } else {
                // Roll up
                char bottom = (vertical >> 6) & 0b11;
                vertical = ((vertical << 2) & 0b11111111) | bottom;
            }
            // Update horizontal's top and bottom to match vertical
            char v_top = (vertical >> 2) & 0b11;
            char v_bottom = (vertical >> 6) & 0b11;
            horizontal = (horizontal & 0b00110011) | (v_bottom << 6) | (v_top << 2);
        } else {
            // Horizontal roll: left->top->right->bottom->left cycle
            if (dy == 1) {
                // Roll right
                char right = horizontal & 0b11;
                horizontal >>= 2;
                horizontal |= (right << 6);
            } else {
                // Roll left
                char bottom = (horizontal >> 6) & 0b11;
                horizontal = ((horizontal << 2) & 0b11111111) | bottom;
            }
            // Update vertical's top and bottom to match horizontal
            char h_top = (horizontal >> 2) & 0b11;
            char h_bottom = (horizontal >> 6) & 0b11;
            vertical = (vertical & 0b00110011) | (h_bottom << 6) | (h_top << 2);
        }
    }
};

char grid[3][3];       // 0 means space, 1-8 means cube index
char grid_color[3][3]; // top color of each position
array<cubic, 9> cubes; // 8 cubes, drop 0
char target[3][3];
int ex, ey;
int steps;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool check_goal() {
    return memcmp(grid_color, target, 9) == 0;
}

bool found;
unordered_set<string> visited;

string get_state() {
    string state;
    state.reserve(18);  // 8 cubes * 2 bytes + 2 bytes for position
    for (int i = 1; i <= 8; i++) {
        state.push_back(cubes[i].vertical);
        state.push_back(cubes[i].horizontal);
    }
    // Add empty position
    state.push_back(static_cast<char>(ex));
    state.push_back(static_cast<char>(ey));
    return state;
}

void dfs(int x, int y, int depth, int max_depth) {
    if (found)
        return;

    // Check if already visited this state
    string state = get_state();
    if (visited.count(state)) {
        return;
    }
    visited.insert(state);

    if (check_goal()) {
        steps = depth;
        found = true;
        return;
    }

    if (depth >= max_depth) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) {
            continue;
        }

        cubic& c = cubes[grid[nx][ny]];

        // Save state
        char old_v = c.vertical;
        char old_h = c.horizontal;

        // Move empty space
        c.roll(dx[i], dy[i]);
        swap(grid[x][y], grid[nx][ny]);
        grid_color[nx][ny] = 'E';
        grid_color[x][y] = c.color_to_char(c.get_top());

        // Update empty position for state hash
        int old_ex = ex, old_ey = ey;
        ex = nx + 1;
        ey = ny + 1;

        dfs(nx, ny, depth + 1, max_depth);

        // Restore empty position
        ex = old_ex;
        ey = old_ey;

        // Restore state
        grid_color[x][y] = 'E';
        grid_color[nx][ny] = c.color_to_char(c.get_top());
        swap(grid[x][y], grid[nx][ny]);
        c.vertical = old_v;
        c.horizontal = old_h;

        if (found)
            return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    while (cin >> ex >> ey && (ex || ey)) {
        // Read target pattern
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                cin >> target[i][j];
            }
        }

        // Initialize cubes
        for (int i = 0; i < 9; i++) {
            cubes[i] = cubic();
        }

        // Initialize grid
        int count = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == ex - 1 && j == ey - 1) {
                    grid[i][j] = 0; // empty space
                    grid_color[i][j] = 'E';
                } else {
                    grid[i][j] = count;
                    grid_color[i][j] =
                        cubes[count].color_to_char(cubes[count].get_top());
                    count++;
                }
            }
        }

        // Check if already at goal
        if (check_goal()) {
            cout << "0\n";
            continue;
        }

        // Iterative deepening DFS with state clearing between iterations
        found = false;
        steps = -1;
        for (int max_depth = 1; max_depth <= 30; max_depth++) {
            visited.clear();  // Clear visited states for new depth limit
            dfs(ex - 1, ey - 1, 0, max_depth);
            if (found) {
                break;
            }
        }

        cout << steps << "\n";
    }
}
