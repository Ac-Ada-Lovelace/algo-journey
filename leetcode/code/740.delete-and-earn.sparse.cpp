#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int deleteAndEarn(vector<int>& nums) {
    if (nums.empty()) return 0;

    unordered_map<int, int> sum;
    sum.reserve(nums.size() * 2);
    for (int x : nums) sum[x] += x;

    vector<int> keys;
    keys.reserve(sum.size());
    for (const auto& kv : sum) keys.push_back(kv.first);
    sort(keys.begin(), keys.end());

    int prev_key = INT_MIN;
    int prev2 = 0;
    int prev1 = 0;
    for (int k : keys) {
      int val = sum[k];
      int cur;
      if (k == prev_key + 1) {
        cur = max(prev1, prev2 + val);
      } else {
        cur = prev1 + val;
      }
      prev2 = prev1;
      prev1 = cur;
      prev_key = k;
    }

    return prev1;
  }
};
