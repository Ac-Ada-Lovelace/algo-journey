#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] != b[0])
                     return a[0] < b[0];
                 return a[1] > b[1];
             });

        vector<int> lis;
        lis.reserve(envelopes.size());
        for (const auto& e : envelopes) {
            int h = e[1];
            auto it = lower_bound(lis.begin(), lis.end(), h);

            if (it == lis.end()) {
                lis.push_back(h);
            } else {
                *it = h;
            }
        }
        return static_cast<int>(lis.size());
    }
};
