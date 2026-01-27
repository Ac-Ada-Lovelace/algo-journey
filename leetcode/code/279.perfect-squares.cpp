#include<bits/stdc++.h>
#include <cmath>
using namespace std;
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1);

        dp[0] = 0;
        dp[1] = 1;
        for(int i = 2; i <=n; i++){
            int sqi = sqrt(i);
             
            int _min = INT_MAX;
            for(int j = 1; j <= sqi; j++){
                _min = min(_min, dp[i-j*j]);
            }

            dp[i] = 1+ _min;

        }

        return dp[n];
        
    }
};
