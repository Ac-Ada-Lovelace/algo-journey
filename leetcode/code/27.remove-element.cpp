#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int tail = n - 1;
        int head = 0;
        while (head <= tail) {
            if (nums[tail] == val) {
                tail--;
                continue;

            }
            if (nums[head] == val) {
                swap(nums[head], nums[tail]);
                tail--;
            } else {
                head++;
            }
        }

        return head;
    }
};
