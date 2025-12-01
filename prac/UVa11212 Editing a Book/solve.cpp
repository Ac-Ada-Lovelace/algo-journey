#include <bits/stdc++.h>
using namespace std;

static int N;

int heuristic(const vector<int>& a) {
    int breaks = 0;
    int prev = 0;
    for (int v : a) {
        if (prev + 1 != v)
            breaks++;
        prev = v;
    }
    if (prev + 1 != N + 1)
        breaks++;
    return (breaks + 2) / 3; // ceil(breaks / 3)
}

bool is_sorted(const vector<int>& a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] != i + 1)
            return false;
    }
    return true;
}

bool dfs(vector<int>& cur, int depth, int limit) {
    int h = heuristic(cur);
    if (depth + h > limit)
        return false;
    if (is_sorted(cur))
        return true;

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            vector<int> cut(cur.begin() + i, cur.begin() + j + 1);
            vector<int> remain;
            remain.reserve(N - (j - i + 1));
            remain.insert(remain.end(), cur.begin(), cur.begin() + i);
            remain.insert(remain.end(), cur.begin() + j + 1, cur.end());

            for (int k = 0; k <= (int)remain.size(); ++k) {
                if (k == i)
                    continue; // inserting back to original place is a no-op
                vector<int> nxt;
                nxt.reserve(N);
                nxt.insert(nxt.end(), remain.begin(), remain.begin() + k);
                nxt.insert(nxt.end(), cut.begin(), cut.end());
                nxt.insert(nxt.end(), remain.begin() + k, remain.end());
                if (dfs(nxt, depth + 1, limit))
                    return true;
            }
        }
    }
    return false;
}

int solve_case(vector<int>& a) {
    for (int depth = heuristic(a); depth <= 8; ++depth) {
        vector<int> cur = a;
        if (dfs(cur, 0, depth))
            return depth;
    }
    return -1; // should not happen for given constraints
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, tc = 1;
    while (cin >> n && n) {
        N = n;
        vector<int> a(n);
        for (int& v : a)
            cin >> v;
        int ans = solve_case(a);
        cout << "Case " << tc++ << ": " << ans << "\n";
    }
    return 0;
}
