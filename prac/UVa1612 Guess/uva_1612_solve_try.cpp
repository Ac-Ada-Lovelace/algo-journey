// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=4487
// UVa1612 Guess
#include <bits/stdc++.h>
using namespace std;

// 每题要么拿到给定分，要么 0，组合一共 8 种。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    int n;
    int t = 0;
    while (cin >> n) {
        if (n == 0)
            break;
        ++t;

        vector<vector<int>> possible_score(n);
        for (int i = 0; i < n; i++) {
            double p[3];
            cin >> p[0] >> p[1] >> p[2];
            int val[3];
            for (int k = 0; k < 3; ++k)
                val[k] = int(llround(p[k] * 100)); // 保留两位小数
            vector<int> s;
            s.reserve(8);
            for (int mask = 0; mask < 8; ++mask) {
                int sum = 0;
                for (int k = 0; k < 3; ++k) {
                    if (mask & (1 << k))
                        sum += val[k];
                }
                s.push_back(sum);
            }
            sort(s.begin(), s.end());
            s.erase(unique(s.begin(), s.end()), s.end());
            possible_score[i] = move(s);
        }

        vector<int> rank_id(n);
        for (int i = 0; i < n; i++) {
            cin >> rank_id[i];
            --rank_id[i]; // 0-based
        }

        // 从排名第一开始贪心：每个人取不违反前一人的最大可行分，这样能最大化最后一名的分数。
        auto pick_max_leq = [&](const vector<int>& vec, int limit) -> int {
            auto it = upper_bound(vec.begin(), vec.end(), limit);
            if (it == vec.begin())
                return -1; // 全部都大于 limit
            --it;
            return *it;
        };

        int prev_score = -1;
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            int id = rank_id[i];
            int limit;
            if (i == 0) {
                limit = INT_MAX; // 第一名不限
            } else {
                // 若前一名 ID > 当前 ID，当前必须严格更低；否则可相等。
                limit = prev_score - (rank_id[i - 1] > id ? 1 : 0);
            }
            int cur = pick_max_leq(possible_score[id], limit);
            if (cur < 0) {
                ok = false;
                break;
            }
            prev_score = cur;
        }

        cout << "Case " << t << ": ";
        if (!ok) {
            cout << "No solution\n";
        } else {
            cout << fixed << setprecision(2) << prev_score / 100.0 << "\n";
        }
    }
    return 0;
}
