// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=847&page=show_problem&problem=2631
// UVa11584 Partitioning by Palindromes
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;

        int n = s.size();
        vector<vector<bool>> is_pal(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            is_pal[i][i] = true;

            for (int j = 1; i - j >= 0 && i + j < n; j++) {
                if (s[i - j] == s[i + j]) {
                    is_pal[i - j][i + j] = true;
                } else {
                    break;
                }
            }
        }

        vector<int> dp(n, INT_MAX);
        for(int i = 0; i < n; i++) {
            if (is_pal[0][i]) {
                dp[i] = 1;
            } else {
                for (int j = 0; j < i; j++) {
                    if (is_pal[j + 1][i]) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
    }
}
