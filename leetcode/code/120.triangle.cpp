#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int depth = triangle.size();
        int maxWidth = triangle[depth - 1].size();

        vector<vector<int>> dp(depth, vector<int>(maxWidth, 0));

        for (int i = 0; i < depth; i++) {
            for (int j = 0; j <= i; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = triangle[i][j];
                } else if (j == 0) {
                    dp[i][j] = dp[i - 1][j] + triangle[i][j];
                } else if (j == i) {
                    dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
                } else {
                    dp[i][j] =
                        min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
                }
            }
        }

        int _min = INT_MAX;

        for (int j = 0; j < maxWidth; j++) {
            _min = min(_min, dp[depth - 1][j]);
        }

        return _min;
    }
};
