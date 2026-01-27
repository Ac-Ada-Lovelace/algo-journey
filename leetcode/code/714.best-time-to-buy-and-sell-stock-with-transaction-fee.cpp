#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int bought, sold;
        int n = prices.size();
        bought = -prices[0] - fee;
        sold = 0;
        for (int i = 1; i < n; i++) {
            int new_bought = max(bought, sold - prices[i] - fee);
            int new_sold = max(sold, bought + prices[i] );

            bought = new_bought;
            sold = new_sold;
        }

        return sold;
    }
};
