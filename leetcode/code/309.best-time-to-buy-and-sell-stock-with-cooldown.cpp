#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0)
            return 0;
        int d0, d1, d2;
        d0 = -prices[0];
        d1 = 0;
        d2 = 0;

        for (int i = 1; i < n; i++) {
            int new_d0 = max(d0, d2 - prices[i]);
            int new_d1 = d0 + prices[i];
            int new_d2 = max(d1, d2);
            d0 = new_d0;
            d1 = new_d1;
            d2 = new_d2;
        }
        return max(d1, d2);
    }
    int maxProfit_dp(vector<int>& prices) {
        int n = prices.size();
        if (n == 0)
            return 0;
        vector<vector<int>> dp(n, vector<int>(3, 0));

        dp[0][0] = -prices[0];

        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]);
            dp[i][1] = dp[i - 1][0] + prices[i];
            dp[i][2] = max(dp[i - 1][1], dp[i - 1][2]);
        }

        return max(dp[n - 1][1], dp[n - 1][2]);
    }
};
