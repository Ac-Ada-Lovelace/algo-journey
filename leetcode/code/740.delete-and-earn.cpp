#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        map<int, int> counts;
        set<int> unique_nums;
        for (auto n : nums) {
            if (counts.count(n)) {
                counts[n]++;
            } else {
                counts[n] = 1;
                unique_nums.insert(n);
            }
        }

        int n = unique_nums.size();
        if (n == 1) {
            int num = *unique_nums.begin();
            return counts[num] * num;
        } else if (n == 2) {
            int first = *unique_nums.begin();
            int second = *(++unique_nums.begin());
            if (first + 1 == second) {
                return max(counts[first] * first, counts[second] * second);
            } else {
                return counts[first] * first + counts[second] * second;
            }
        }
        map<int, int> dp;
        int first = *unique_nums.begin();
        int second = *(++unique_nums.begin());
        dp[first] = counts[first] * first;
        dp[second] = (first + 1 == second)
                         ? max(dp[first], counts[second] * second)
                         : dp[first] + counts[second] * second;
        int third = *(++(++unique_nums.begin()));
        for (auto un : unique_nums) {
            if(un < third){
                continue;
            }
            int p = *prev(unique_nums.find(un));
            int pp = *prev(unique_nums.find(p));
            if (p + 1 == un) {
                dp[un] = max(dp[p], dp[pp] + counts[un] * un);
            } else {
                dp[un] = dp[p] + counts[un] * un;
            }
        }

        int last = *(unique_nums.rbegin());
        return dp[last];
    }
};
