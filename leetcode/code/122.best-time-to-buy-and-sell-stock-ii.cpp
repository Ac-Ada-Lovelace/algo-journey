#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int _max = 0;
        auto n = prices.size();
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                _max += prices[i] - prices[i - 1];
            }
        }

        return _max;
    }
};
