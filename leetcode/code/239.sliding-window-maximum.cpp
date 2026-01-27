#include <bits/stdc++.h>
#include <queue>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        return maxSlidingWindow_deq(nums, k);
        int n = nums.size();
        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < k; i++) {
            pq.emplace(nums[i], i);
        }

        vector<int> ans = {pq.top().first};
        for (int i = k; i < n; i++) {
            pq.emplace(nums[i], i);
            while (pq.top().second <= i - k) {
                pq.pop();
            }
            ans.push_back(pq.top().first);
        }
        return ans;
    }

    vector<int> maxSlidingWindow_deq(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> deq;
        for (int i = 0; i < k; i++) {
            while (!deq.empty() && nums[deq.back()] <= nums[i]) {
                deq.pop_back();
            }
            deq.push_back(i);
        }

        vector<int> ans;
        ans.push_back(nums[deq.front()]);

        for (int i = k; i < n; i++) {
            while (!deq.empty() && nums[deq.back()] <= nums[i]) {
                deq.pop_back();
            }
            deq.push_back(i);
            while (i - deq.front() >= k) {
                deq.pop_front();
            }
            ans.push_back(nums[deq.front()]);
        }
        return ans;
    }
};
