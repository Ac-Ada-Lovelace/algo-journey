#include <bits/stdc++.h>
using namespace std;

// Iterative deepening search on addition/subtraction chains of exponents.
// Each step may multiply or divide two previously computed powers:
// x^a * x^b = x^{a+b}, x^a / x^b = x^{a-b} (positive exponent only).

namespace {
int target;
int limitDepth;
int seq[20];  // depth <= 14 for n <= 1000, so 20 is plenty.

bool dfs(int depth, int currentMax) {
  if (seq[depth] == target) return true;
  if (depth == limitDepth) return false;

  // Best we can do is double the maximum each remaining step.
  long long maxReachable = currentMax;
  for (int i = 0; i < limitDepth - depth; ++i) {
    maxReachable <<= 1;
    if (maxReachable >= target) break;
  }
  if (maxReachable < target) return false;

  unordered_set<int> used;  // avoid repeating candidates at this depth
  for (int i = 0; i <= depth; ++i) {
    for (int j = i; j <= depth; ++j) {
      int a = seq[i], b = seq[j];
      int candidates[2] = {a + b, abs(a - b)};
      for (int k = 0; k < 2; ++k) {
        int v = candidates[k];
        if (v <= 0) continue;  // exponents must stay positive
        if (!used.insert(v).second) continue;
        bool duplicate = false;
        for (int t = 0; t <= depth; ++t) {
          if (seq[t] == v) {
            duplicate = true;
            break;
          }
        }
        if (duplicate) continue;

        seq[depth + 1] = v;
        int nextMax = max(currentMax, v);
        if (dfs(depth + 1, nextMax)) return true;
      }
    }
  }
  return false;
}

int solveInstance(int n) {
  if (n == 1) return 0;
  target = n;
  seq[0] = 1;
  for (limitDepth = 1;; ++limitDepth) {
    if (dfs(0, 1)) return limitDepth;
  }
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n && n) {
    cout << solveInstance(n) << '\n';
  }
  return 0;
}
