#include <bits/stdc++.h>
using namespace std;

// IDA-style search to remove the minimum number of matchsticks so that
// no complete square remains in an n x n grid (n <= 5). Matchsticks are
// indexed left-to-right, top-to-bottom as shown in the PDF.

namespace {

struct Grid {
    int n;
    int edges;                    // total edges = 2n(n+1)
    vector<vector<int>> horiz;    // (n+1) x n
    vector<vector<int>> vert;     // n x (n+1)
    vector<uint64_t> squareMasks; // bitmask of edges forming each square
};

Grid buildGrid(int n) {
    Grid g;
    g.n = n;
    g.horiz.assign(n + 1, vector<int>(n));
    g.vert.assign(n, vector<int>(n + 1));
    int id = 1;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c)
            g.horiz[r][c] = id++;
        for (int c = 0; c <= n; ++c)
            g.vert[r][c] = id++;
    }
    for (int c = 0; c < n; ++c)
        g.horiz[n][c] = id++;
    g.edges = id - 1;

    // Enumerate all squares of size s with top-left (r,c)
    for (int s = 1; s <= n; ++s) {
        for (int r = 0; r + s <= n; ++r) {
            for (int c = 0; c + s <= n; ++c) {
                uint64_t mask = 0;
                for (int k = 0; k < s; ++k) {
                    int e1 = g.horiz[r][c + k];
                    int e2 = g.horiz[r + s][c + k];
                    int e3 = g.vert[r + k][c];
                    int e4 = g.vert[r + k][c + s];
                    mask |= (uint64_t)1 << (e1 - 1);
                    mask |= (uint64_t)1 << (e2 - 1);
                    mask |= (uint64_t)1 << (e3 - 1);
                    mask |= (uint64_t)1 << (e4 - 1);
                }
                g.squareMasks.push_back(mask);
            }
        }
    }
    return g;
}

int limitDepth;
vector<uint64_t> squares;

bool dfs(uint64_t state, int depth) {
    // Find a remaining complete square
    uint64_t target = 0;
    for (uint64_t m : squares) {
        if ((state & m) == m) {
            target = m;
            break;
        }
    }
    if (target == 0)
        return true; // no squares remain
    if (depth == limitDepth)
        return false;

    // Try removing each edge belonging to this square that is still present
    uint64_t edges = state & target;
    while (edges) {
        uint64_t lowbit = edges & -edges;
        edges -= lowbit;
        if (dfs(state & ~lowbit, depth + 1))
            return true;
    }
    return false;
}

int solveCase(const Grid& g, const vector<int>& missing) {
    uint64_t state =
        (g.edges == 64) ? ~uint64_t(0) : ((uint64_t(1) << g.edges) - 1);
    for (int id : missing) {
        state &= ~((uint64_t)1 << (id - 1));
    }
    squares = g.squareMasks;
    for (limitDepth = 0;; ++limitDepth) {
        if (dfs(state, 0))
            return limitDepth;
    }
}

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T))
        return 0;
    vector<Grid> grids(6); // cache by n

    while (T--) {
        int n;
        cin >> n;
        if (grids[n].n == 0)
            grids[n] = buildGrid(n);
        int k;
        cin >> k;
        vector<int> missing(k);
        for (int i = 0; i < k; ++i)
            cin >> missing[i];
        int ans = solveCase(grids[n], missing);
        cout << ans << '\n';
    }
    return 0;
}
