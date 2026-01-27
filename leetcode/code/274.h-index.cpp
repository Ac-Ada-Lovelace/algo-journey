#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int n = citations.size();
        int maxh = 0;
        for (int i = n - 1; i >= 0; i--) {
            int h = n - i;
            if(citations[i] >= h) {
                maxh = h;
            } else {
                break;
            }
            
        }
        return maxh;
    }
};
