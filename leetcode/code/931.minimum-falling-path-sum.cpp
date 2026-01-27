#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0) {
                    dp[i][j] = matrix[i][j];
                } else {
                    int left = (j > 0) ? dp[i - 1][j - 1] : INT_MAX;
                    int up = dp[i - 1][j];
                    int right = (j < n - 1) ? dp[i - 1][j + 1] : INT_MAX;
                    dp[i][j] = matrix[i][j] + min({left, up, right});
                }
            }
        }

        int _min = INT_MAX;
        for (int j = 0; j < n; j++) {
            _min = min(_min, dp[n - 1][j]);
        }
        return _min;
    }
};
