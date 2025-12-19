#include <bits/stdc++.h>
using namespace std;

struct Category {
    int V, K, C, L;
};

int main() {
    ios::sync_with_stdio(false);

    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    while (cin >> n && n) {
        vector<Category> cats(n);
        for (auto& c : cats)
            cin >> c.V >> c.K >> c.C >> c.L;

        // 按电压升序排序
        sort(cats.begin(), cats.end(),
             [](const Category& a, const Category& b) {
                 return a.V < b.V;
             });

        // 合并相同电压档：灯数累加，成本取最小（电源成本、单灯成本）
        vector<Category> merged;
        for (const auto& c : cats) {
            if (!merged.empty() && merged.back().V == c.V) {
                merged.back().L += c.L;
                merged.back().K = min(merged.back().K, c.K);
                merged.back().C = min(merged.back().C, c.C);
            } else {
                merged.push_back(c);
            }
        }

        int m = merged.size();
        vector<long long> prefixL(m + 1, 0);
        for (int i = 1; i <= m; ++i)
            prefixL[i] = prefixL[i - 1] + merged[i - 1].L;

        const long long INF = (1LL << 60);
        vector<long long> dp(m + 1, INF);
        dp[0] = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= i; ++j) {
                long long lamps = prefixL[i] - prefixL[j - 1];
                long long cost =
                    dp[j - 1] + merged[i - 1].K + lamps * merged[i - 1].C;
                // cost if we dont replace low V lamps with this
                dp[i] = min(dp[i], cost);
            }
        }

        cout << dp[m] << '\n';
    }
    return 0;
}
