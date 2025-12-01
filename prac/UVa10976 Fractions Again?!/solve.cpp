// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=841&page=show_problem&problem=1917
// UVa10976 Fractions Again?!
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long k;
  while (cin >> k) {
    vector<pair<long long, long long>> solutions;
    for (long long y = k + 1; y <= 2 * k; ++y) {
      long long numerator = k * y;
      long long denominator = y - k;
      if (numerator % denominator == 0) {
        long long x = numerator / denominator;
        solutions.emplace_back(x, y);
      }
    }

    cout << solutions.size() << "\n";
    for (auto [x, y] : solutions) {
      cout << "1/" << k << " = 1/" << x << " + 1/" << y << "\n";
    }
  }
}
