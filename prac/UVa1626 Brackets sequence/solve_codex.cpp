#include <bits/stdc++.h>
using namespace std;

bool is_match(char open, char close) {
  return (open == '(' && close == ')') || (open == '[' && close == ']');
}

string base_pair(char c) {
  // 最短补全当前字符成为一对括号
  if (c == '(' || c == ')') return "()";
  return "[]";  // '[' or ']'
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

  string line;
  if (!getline(cin, line)) return 0;
  int T = stoi(line);
  getline(cin, line);  // 题面规定首组前有一行空行

  for (int tc = 0; tc < T; ++tc) {
    string s;
    if (!getline(cin, s)) s.clear();  // 允许空串
    if (tc + 1 != T) getline(cin, line);  // 读取分隔空行（若存在）

    int n = s.size();
    if (n == 0) {
      cout << "\n";
      if (tc + 1 != T) cout << "\n";
      continue;
    }

    vector<vector<string>> dp(n, vector<string>(n));
    for (int i = 0; i < n; ++i) dp[i][i] = base_pair(s[i]);

    auto better = [](const string &a, const string &b) {
      if (a.empty()) return b;
      if (b.empty()) return a;
      if (a.size() != b.size()) return (a.size() < b.size()) ? a : b;
      return a;
    };

    for (int len = 2; len <= n; ++len) {
      for (int l = 0; l + len - 1 < n; ++l) {
        int r = l + len - 1;
        string best;

        for (int m = l; m < r; ++m) {
          best = better(best, dp[l][m] + dp[m + 1][r]);
        }

        for (int k = l + 1; k <= r; ++k) {
          if (is_match(s[l], s[k])) {
            string inside = (l + 1 <= k - 1) ? dp[l + 1][k - 1] : "";
            string tail = (k + 1 <= r) ? dp[k + 1][r] : "";
            string cand;
            cand.push_back(s[l]);
            cand += inside;
            cand.push_back(s[k]);
            cand += tail;
            best = better(best, cand);
          }
        }

        dp[l][r] = best;
      }
    }

    cout << dp[0][n - 1] << "\n";
    if (tc + 1 != T) cout << "\n";
  }
  return 0;
}
