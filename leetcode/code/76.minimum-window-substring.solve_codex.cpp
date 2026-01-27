#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  string minWindow(string s, string t) {
    if (t.empty() || s.empty()) {
      return "";
    }

    int need[128] = {};
    for (char c : t) {
      need[static_cast<unsigned char>(c)]++;
    }

    int have[128] = {};
    int missing = static_cast<int>(t.size());
    int best_len = INT_MAX;
    int best_l = 0;

    int l = 0;
    for (int r = 0; r < static_cast<int>(s.size()); r++) {
      unsigned char rc = static_cast<unsigned char>(s[r]);
      have[rc]++;
      if (have[rc] <= need[rc]) {
        missing--;
      }

      while (missing == 0) {
        int len = r - l + 1;
        if (len < best_len) {
          best_len = len;
          best_l = l;
        }

        unsigned char lc = static_cast<unsigned char>(s[l]);
        have[lc]--;
        if (have[lc] < need[lc]) {
          missing++;
        }
        l++;
      }
    }

    if (best_len == INT_MAX) {
      return "";
    }
    return s.substr(best_l, best_len);
  }
};
