#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  while (cin >> n >> m) {
    cin.ignore();
    vector<vector<string>> rows(n, vector<string>(m));
    for (int i = 0; i < n; ++i) {
      string line;
      getline(cin, line);
      int start = 0;
      for (int j = 0; j < m; ++j) {
        int pos = j == m - 1 ? line.size() : line.find(',', start);
        if (pos == string::npos) pos = line.size();
        rows[i][j] = line.substr(start, pos - start);
        start = pos + 1;
      }
    }

    bool ok = true;
    for (int c1 = 0; c1 < m && ok; ++c1) {
      for (int c2 = c1 + 1; c2 < m && ok; ++c2) {
        unordered_map<string, int> seen;
        seen.reserve(n * 2);
        for (int r = 0; r < n; ++r) {
          string key = rows[r][c1] + '\0' + rows[r][c2];
          auto it = seen.find(key);
          if (it != seen.end()) {
            cout << "NO\n" << it->second + 1 << ' ' << r + 1 << "\n" << c1 + 1 << ' '
                 << c2 + 1 << "\n";
            ok = false;
            break;
          }
          seen[key] = r;
        }
      }
    }
    if (ok) cout << "YES\n";
  }
  return 0;
}
