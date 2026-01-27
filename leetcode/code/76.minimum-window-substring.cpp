#include <bits/stdc++.h>
#include <climits>
using namespace std;
class Solution {
public:
    unordered_map<char, int> ori, cnt;
    bool check() {
        for (const auto& p : ori) {
            if (cnt[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        for (const auto& c : t) {
            ++ori[c];
        }

        int l = 0, r = -1;
        int len = INT_MAX, ansL = -1, ansR = -1;
        while (r < int(s.size())) {
        }
    }
};
