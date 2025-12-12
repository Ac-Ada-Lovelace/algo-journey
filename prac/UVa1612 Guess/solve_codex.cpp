// UVa 1612 - Guess
// 判定给定排名能否由三题得分(每题要么拿到给定分，要么 0)实现，并最大化最后一名的总分。
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  int tc = 0;
  while (cin >> n) {
    if (n == 0) break;
    ++tc;

    vector<vector<int>> scores(n);  // 每个选手的可行总分（升序，单位：分*100）
    for (int i = 0; i < n; ++i) {
      double a, b, c;
      cin >> a >> b >> c;
      int val[3];
      val[0] = static_cast<int>(llround(a * 100));
      val[1] = static_cast<int>(llround(b * 100));
      val[2] = static_cast<int>(llround(c * 100));
      vector<int> s;
      s.reserve(8);
      for (int mask = 0; mask < 8; ++mask) {
        int sum = 0;
        for (int k = 0; k < 3; ++k) {
          if (mask & (1 << k)) sum += val[k];
        }
        s.push_back(sum);
      }
      sort(s.begin(), s.end());
      s.erase(unique(s.begin(), s.end()), s.end());
      scores[i] = move(s);
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
      cin >> order[i];
      --order[i];  // 改为 0-based
    }

    const vector<int>& lastSet = scores[order.back()];
    int best = -1;
    for (auto it = lastSet.rbegin(); it != lastSet.rend(); ++it) {
      int lastScore = *it;
      int nextScore = lastScore;
      bool ok = true;
      for (int idx = n - 2; idx >= 0 && ok; --idx) {
        int currId = order[idx];
        int nextId = order[idx + 1];
        bool mustGreater = currId > nextId;  // ID 大者若在前，必须严格高分
        const auto& arr = scores[currId];
        if (mustGreater) {
          auto p = upper_bound(arr.begin(), arr.end(), nextScore);
          if (p == arr.end()) {
            ok = false;
            break;
          }
          nextScore = *p;
        } else {
          auto p = lower_bound(arr.begin(), arr.end(), nextScore);
          if (p == arr.end()) {
            ok = false;
            break;
          }
          nextScore = *p;
        }
      }
      if (ok) {
        best = lastScore;
        break;  // 已按降序遍历，找到即为最大可行值
      }
    }

    cout << "Case " << tc << ": ";
    if (best < 0) {
      cout << "No solution\n";
    } else {
      cout << fixed << setprecision(2) << (best / 100.0) << "\n";
    }
  }
  return 0;
}
