#include <bits/stdc++.h>
using namespace std;

bool compatible(const string &a, const string &b, int shift) {
  for (int i = 0; i < (int)b.size(); ++i) {
    int pos = i + shift;
    if (pos >= 0 && pos < (int)a.size()) {
      if ((a[pos] - '0') + (b[i] - '0') > 3) return false;
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s1, s2;
  while (cin >> s1 >> s2) {
    int m = s1.size();
    int n = s2.size();
    int best = m + n;

    for (int shift = -n; shift <= m; ++shift) {
      if (compatible(s1, s2, shift)) {
        int left = min(0, shift);
        int right = max(m, shift + n);
        best = min(best, right - left);
      }
    }
    cout << best << '\n';
  }
  return 0;
}
