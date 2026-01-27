#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(1001, 1));
        int _max = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int diff = nums[i] - nums[j] + 500;
                dp[i][diff] = max(dp[i][diff], dp[j][diff] + 1);
                _max = max(_max, dp[i][diff]);
            }
        }

        return _max;
    }
};
