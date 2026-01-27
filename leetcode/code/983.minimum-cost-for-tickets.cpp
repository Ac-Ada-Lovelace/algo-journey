#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<bool> ds(366);
        for (auto d : days) {
            ds[d] = true;
        }
        vector<vector<unsigned long long>> exp = {
            {1, (unsigned long long)costs[0]},
            {7, (unsigned long long)costs[1]},
            {30, (unsigned long long)costs[2]}};
        vector<unsigned long long> dp(366);

        for (int i = 365; i > 0; i--) {
            unsigned long long _min = INT_MAX;
            if (ds[i]) {
                for (auto e : exp) {
                    _min = min(_min, e[1] + dp[min(365ull, i + e[0])]);
                }
                dp[i] = _min;
            } else {
                dp[i] = dp[i + 1 > 365 ? 365 : i + 1];
            }
        }

        return dp[1];
    }
};
