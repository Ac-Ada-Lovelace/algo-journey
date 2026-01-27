#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();

        if (n == 0)
            return 0;
        sort(pairs.begin(), pairs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });
        vector<int> dp(n, 1);
        int _max = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (pairs[i][0] > pairs[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                    _max = max(_max, dp[i]);
                }
            }
        }

        return _max;
    }
};
