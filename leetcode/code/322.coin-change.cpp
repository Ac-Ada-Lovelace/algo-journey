#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<unsigned long long> dp(amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            unsigned long long _min = INT_MAX;
            for (auto c : coins) {
                if (i - c >= 0) {
                    _min = min(_min, dp[i - c]);
                }
            }
            dp[i] = _min + 1;
        }

        if (dp[amount] > 1e9) {
            return -1;
        }
        return dp[amount];
    }
};
