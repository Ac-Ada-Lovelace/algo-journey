#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    int T;
    if (!(cin >> T))
        return 0;
    while (T--) {
        string a, b;
        cin >> a >> b;
        int n = a.size(), m = b.size();

        // cnt[c]: total occurrences of color c across both strings
        array<int, 26> cnt{};
        for (char ch : a)
            cnt[ch - 'A']++;
        for (char ch : b)
            cnt[ch - 'A']++;

        // rem1[i][c]: occurrences of color c in a[i..]
        vector<array<int, 26>> rem1(n + 1), rem2(m + 1);
        for (int c = 0; c < 26; ++c)
            rem1[n][c] = 0;
        for (int i = n - 1; i >= 0; --i) {
            rem1[i] = rem1[i + 1];
            rem1[i][a[i] - 'A']++;
        }
        for (int c = 0; c < 26; ++c)
            rem2[m][c] = 0;
        for (int j = m - 1; j >= 0; --j) {
            rem2[j] = rem2[j + 1];
            rem2[j][b[j] - 'A']++;
        }

        const long long INF = (1LL << 60);
        vector<long long> prev(m + 1, INF), cur(m + 1, INF);
        prev[0] = 0;

        for (int i = 0; i <= n; ++i) {
            fill(cur.begin(), cur.end(), INF);
            if (i == 0) cur[0] = 0;
            for (int j = 0; j <= m; ++j) {
                if (i == 0 && j == 0)
                    continue;
                long long best = INF;
                int pos = i + j; // current length before placing new char

                if (i > 0 && prev[j] < INF) {
                    int c = a[i - 1] - 'A';
                    int used_before = cnt[c] - rem1[i - 1][c] - rem2[j][c];
                    int used_after = used_before + 1;
                    long long delta = 0;
                    if (used_before == 0)
                        delta -= (pos);
                    if (used_after == cnt[c])
                        delta += (pos);
                    best = min(best, prev[j] + delta);
                }

                if (j > 0 && cur[j - 1] < INF) {
                    int c = b[j - 1] - 'A';
                    int used_before = cnt[c] - rem1[i][c] - rem2[j - 1][c];
                    int used_after = used_before + 1;
                    long long delta = 0;
                    if (used_before == 0)
                        delta -= (pos);
                    if (used_after == cnt[c])
                        delta += (pos);
                    best = min(best, cur[j - 1] + delta);
                }

                cur[j] = best;
            }
            prev.swap(cur);
        }

        cout << prev[m] << "\n";
    }
    return 0;
}
