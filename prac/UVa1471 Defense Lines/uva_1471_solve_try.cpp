// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=4217
// UVa1471 Defense Lines
#include <bits/stdc++.h>
using namespace std;

// Fenwick tree for range max query on prefix.
struct BIT {
    vector<int> t;
    explicit BIT(int n = 0) { init(n); }
    void init(int n) { t.assign(n + 1, 0); }
    void update(int idx, int val) {
        for (int i = idx; i < (int)t.size(); i += i & -i) t[i] = max(t[i], val);
    }
    int query(int idx) const {
        int res = 0;
        for (int i = idx; i > 0; i -= i & -i) res = max(res, t[i]);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n + 2, 0);
        for (int i = 1; i <= n; i++) cin >> a[i];

        // L[i]: length of increasing contiguous segment ending at i
        // R[i]: length of increasing contiguous segment starting at i
        vector<int> L(n + 2, 1), R(n + 2, 1);
        for (int i = 2; i <= n; i++) {
            if (a[i] > a[i - 1]) L[i] = L[i - 1] + 1;
        }
        for (int i = n - 1; i >= 1; i--) {
            if (a[i] < a[i + 1]) R[i] = R[i + 1] + 1;
        }

        int ans = 1;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, max(L[i], R[i]));
        }

        // Coordinate compress heights for BIT.
        vector<long long> comp(a.begin() + 1, a.begin() + n + 1);
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        auto idx_of = [&](long long x) {
            return int(lower_bound(comp.begin(), comp.end(), x) - comp.begin()) + 1;
        };

        BIT bit((int)comp.size());
        for (int i = 1; i <= n; i++) {
            int idx = idx_of(a[i]);
            // Choose a split between some position before i and i (inclusive),
            // delete the middle to connect prefix ending before i with suffix starting at i.
            int best_prefix = bit.query(idx - 1);  // max L[k] where a[k] < a[i] and k < i
            ans = max(ans, best_prefix + R[i]);
            bit.update(idx, L[i]);
        }

        cout << ans << "\n";
    }
    return 0;
}
