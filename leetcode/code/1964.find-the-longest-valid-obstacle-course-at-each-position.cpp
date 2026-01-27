#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        vector<int> d, ans;
        // for (int ob : obstacles) {
        //     if (d.empty() || ob >= d.back()) {
        //         d.push_back(ob);
        //         ans.push_back(d.size());
        //     } else {
        //         int loc = upper_bound(d.begin(), d.end(), ob) - d.begin();
        //         ans.push_back(loc + 1);
        //         d[loc] = ob;
        //     }
        // }
        for (int ob : obstacles) {
            auto it = upper_bound(d.begin(), d.end(), ob);
            if (it == d.end() || d.empty()) {
                d.push_back(ob);
                ans.push_back(d.size());
            } else {
                *it = ob;
                ans.push_back(it - d.begin() + 1);
            }
        }
        return ans;
    }
};
