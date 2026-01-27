#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

        vector<bool> dp(s.size() + 1, false);
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < 20 && j < i; ++j) {
                if (dp[i - j - 1] || i - j - 1 == 0) {
                    string sub = s.substr(i - j - 1, j + 1);
                    if (wordSet.count(sub)) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }

        return dp[s.size()];
    }
};
