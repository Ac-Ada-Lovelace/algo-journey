#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> s;
        int tail = n - 1;
        int head = 0;
        while (head <= tail) {
            if (s.count(nums[tail])) {
                tail--;
                continue;
            }
            if (s.count(nums[head])) {
                swap(nums[head], nums[tail]);
                tail--;
            } else {
                s.insert(nums[head]);
                head++;
            }
        }

        sort(nums.begin(), nums.begin() + head);
        return head;
    }
};
