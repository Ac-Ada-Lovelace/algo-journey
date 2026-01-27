#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int right_most = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i <= right_most) {
                right_most = max(right_most, i + nums[i]);
                if (right_most >= n - 1) {
                    return true;
                }
            } else {
                return false;
            }
        }
        return false;
    }
};
