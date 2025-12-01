#include <bits/stdc++.h>
using namespace std;

// Positions for the 8 operations A-H, each rotates the line forward by one.
static const int ops[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},    // A
    {1, 3, 8, 12, 17, 21, 23},    // B
    {10, 9, 8, 7, 6, 5, 4},       // C
    {19, 18, 17, 16, 15, 14, 13}, // D
    {23, 21, 17, 12, 8, 3, 1},    // E
    {22, 20, 15, 11, 6, 2, 0},    // F
    {13, 14, 15, 16, 17, 18, 19}, // G
    {4, 5, 6, 7, 8, 9, 10}        // H
};

// Inverse move mapping to avoid immediate backtracking.
static const int inverse_op[8] = {5, 4, 7, 6, 1, 0, 3, 2};
static const int center_idx[8] = {6, 7, 8, 11, 12, 15, 16, 17};

struct Solver {
    array<int, 24> state{};
    string path;

    int heuristic() const {
        int cnt[4] = {0};
        for (int idx : center_idx)
            cnt[state[idx]]++;
        int best = max({cnt[1], cnt[2], cnt[3]});
        int mismatch = 8 - best;
        return (mismatch + 3) / 4; // one move can fix at most 4 center cells
    }

    bool is_goal() const {
        return heuristic() == 0;
    }

    array<int, 24> apply_move(const array<int, 24>& s, int op) const {
        array<int, 24> t = s;
        int first = s[ops[op][0]];
        for (int i = 0; i < 6; ++i) {
            t[ops[op][i]] = s[ops[op][i + 1]];
        }
        t[ops[op][6]] = first;
        return t;
    }

    bool dfs(int depth, int limit, int last_op) {
        int h = heuristic();
        if (depth + h > limit)
            return false;
        if (is_goal())
            return true;
        for (int op = 0; op < 8; ++op) {
            if (last_op != -1 && inverse_op[op] == last_op)
                continue;
            array<int, 24> next = apply_move(state, op);
            swap(state, next);
            path.push_back('A' + op);
            if (dfs(depth + 1, limit, op))
                return true;
            path.pop_back();
            swap(state, next);
        }
        return false;
    }

    pair<string, int> solve(const array<int, 24>& start) {
        state = start;
        path.clear();
        if (is_goal()) {
            return {"", state[center_idx[0]]};
        }
        for (int limit = 1;; ++limit) {
            if (dfs(0, limit, -1))
                break;
        }
        return {path, state[center_idx[0]]};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solver solver;
    while (true) {
        array<int, 24> start{};
        if (!(cin >> start[0]))
            break;
        if (start[0] == 0)
            break;
        for (int i = 1; i < 24; ++i)
            cin >> start[i];

        auto res = solver.solve(start);
        if (res.first.empty()) {
            cout << "No moves needed\n";
        } else {
            cout << res.first << "\n";
        }
        cout << res.second << "\n";
    }
    return 0;
}
