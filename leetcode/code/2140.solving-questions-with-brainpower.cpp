#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        return mostPoints_slow(questions);
        int n = questions.size();
        vector<long long> dp(n + 1);
        for (int i = n - 1; i >= 0; --i) {
            dp[i] = max(dp[i + 1],
                        questions[i][0] + dp[min(n, i + questions[i][1] + 1)]);
        }
        return dp[0];
    }

    long long mostPoints_slow(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n + 1);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            long long _max = 0;
            for (int j = i - 1; j > 0; j--) {
                if (questions[j - 1][1] + j < i) {
                    _max = max(_max, dp[j]);
                }
            }

            dp[i] = max(dp[i - 1], questions[i - 1][0] + _max);
        }

        return dp[n];
    }
};
