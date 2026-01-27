#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    pair<int, int> count(string s) {
        int zeros = 0, ones = 0;
        for (auto c : s) {
            if (c == '0') {
                zeros++;
            } else {
                ones++;
            }
        }

        return pair<int, int>(zeros, ones);
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        return findMaxFormCompact(strs, m, n);
        // int l = strs.size();
        // vector<vector<vector<int>>> dp(
        //     l + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        //
        // for (int i = 0; i < m; i++) {
        //     for (int j = 0; j < n; j++) {
        //         dp[0][i][j] = 0;
        //     }
        // }
        //
        // for (int i = 1; i <= l; ++i) {
        //     auto [zeros, ones] = count(strs[i - 1]);
        //     for (int j = 0; j <= m; j++) {
        //         for (int k = 0; k <= n; k++) {
        //             if (j < zeros || k < ones) {
        //                 dp[i][j][k] = dp[i - 1][j][k];
        //             } else if (j >= zeros && k >= ones) {
        //                 dp[i][j][k] = max(dp[i - 1][j][k],
        //                                   dp[i - 1][j - zeros][k - ones] + 1);
        //             }
        //         }
        //     }
        // }
        //
        // return dp[l][m][n];
    }
    int findMaxFormCompact(vector<string>& strs, int m, int n) {
        int l = strs.size();
        vector<vector<vector<int>>> dp(
            1 + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[0][i][j] = 0;
            }
        }

        int curr;
        int prev;
        for (int i = 1; i <= l; ++i) {
            curr = i % 2;
            prev = curr ? 0 : 1;

            auto [zeros, ones] = count(strs[i - 1]);
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= n; k++) {
                    if (j < zeros || k < ones) {
                        dp[curr][j][k] = dp[prev][j][k];
                    } else if (j >= zeros && k >= ones) {
                        dp[curr][j][k] = max(dp[prev][j][k],
                                             dp[prev][j - zeros][k - ones] + 1);
                    }
                }
            }
        }

        return dp[curr][m][n];
    }
};
