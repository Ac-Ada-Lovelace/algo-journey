#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numTilings(int n) {
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        if (n == 3) {
            return 5;
        }

        vector<unsigned long long> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;

        unsigned long long MOD = 1e9 + 7;
        for (int i = 4; i <= n; i++) {
            dp[i] = (dp[i-1]*2 + dp[i-3]);
            dp[i] %= MOD;
        }

        return dp[n] % MOD;
    }
};
