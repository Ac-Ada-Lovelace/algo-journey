#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int deleteAndEarn(vector<int>& nums) {
    if (nums.empty()) return 0;

    int maxv = 0;
    for (int x : nums) maxv = max(maxv, x);

    vector<int> sum(maxv + 1, 0);
    for (int x : nums) sum[x] += x;

    int prev2 = 0;
    int prev1 = 0;
    for (int i = 1; i <= maxv; ++i) {
      int cur = max(prev1, prev2 + sum[i]);
      prev2 = prev1;
      prev1 = cur;
    }
    return prev1;
  }
};
