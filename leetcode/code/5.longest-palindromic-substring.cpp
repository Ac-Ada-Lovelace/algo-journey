#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n <= 1)
            return s;
        int bestL = 0, bestLen = 1;

        auto expand = [&](int L, int R) {
            while (L >= 0 && R < n && s[L] == s[R]) {
                --L;
                ++R;
            }
            int len = R - L - 1; // 回退后长度
            int start = L + 1;
            if (len > bestLen) {
                bestLen = len;
                bestL = start;
            }
        };

        for (int i = 0; i < n; ++i) {
            expand(i, i);     // 奇数中心
            expand(i, i + 1); // 偶数中心
        }
       return s.substr(bestL, bestLen);
    }
};
