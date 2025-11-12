#include <bits/stdc++.h>
using namespace std;

bool is_subsequence(const string &s, const string &t) {
  size_t i = 0;
  for (size_t j = 0; j < t.size() && i < s.size(); j++) {
    if (t[j] == s[i]) i++;
  }
  return i == s.size();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  while (cin >> s >> t) {
    cout << (is_subsequence(s, t) ? "Yes" : "No") << '\n';
  }
  return 0;
}
