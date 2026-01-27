#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int _minP = prices[0];
        int _max;
        for(auto p : prices) {
            _minP = min(_minP, p);
            _max = max(_max, p - _minP);
        }

        return _max;
    }
    int maxProfit_stack(vector<int>& prices) {
        stack<int> minPriceStack;
        int _maxProfit = 0;
        minPriceStack.push(prices[0]);

        for (auto p : prices) {
            if (p < minPriceStack.top()) {
                minPriceStack.push(p);
            } else {
                _maxProfit = max(_maxProfit, p - minPriceStack.top());
            }
        }

        return _maxProfit;
    }
};
