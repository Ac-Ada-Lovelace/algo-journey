// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=847&page=show_problem&problem=4501
// UVa1626 Brackets sequence
#include <bits/stdc++.h>
using namespace std;

bool match(char c1, char c2) {
    if (c1 == '(' && c2 == ')')
        return true;
    if (c1 == '[' && c2 == ']')
        return true;
    if (c1 == ')' && c2 == '(')
        return true;
    if (c1 == ']' && c2 == '[')
        return true;

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;


        auto n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for(int len = 2; len <= n; ++len) {
            for(int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;

                if (match(s[i], s[j])) {
                    dp[i][j] = dp[i + 1][j - 1];
                }

                for(int k = i; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }

    }
}
