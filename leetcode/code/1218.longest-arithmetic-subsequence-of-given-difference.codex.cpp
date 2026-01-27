#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        unordered_map<int, int> dp;
        dp.reserve(arr.size() * 2);

        int best = 0;
        for (int x : arr) {
            int prev = x - difference;
            int cur = 1;
            auto it = dp.find(prev);
            if (it != dp.end())
                cur = it->second + 1;
            dp[x] = max(dp[x], cur);
            best = max(best, dp[x]);
        }

        return best;
    }
};
