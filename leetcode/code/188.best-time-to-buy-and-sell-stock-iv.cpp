#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<int> dp(2 * k, 0);

        for (int i = 0; i < 2 * k; ++i) {
            if (i % 2 == 0) {
                dp[i] = -prices[0];
            } else {
                dp[i] = 0;
            }
        }

        for (int i = 1; i < prices.size(); ++i) {
            for (int j = 1; j < 2 * k; ++j) {
                if (j % 2 == 0) {
                    dp[j] = max(dp[j], (j == 0 ? 0 : dp[j - 1]) - prices[i]);
                } else {
                    dp[j] = max(dp[j], dp[j - 1] + prices[i]);
                }
            }
        }

        return dp[2 * k - 1];
    }
};
