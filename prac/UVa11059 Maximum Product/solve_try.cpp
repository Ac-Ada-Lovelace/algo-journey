// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=841&page=show_problem&problem=2000
// UVa11059 Maximum Product
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  int case_id = 1;
  while (cin >> n) {
    vector<long long> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    long long best = 0;
    for (int i = 0; i < n; i++) {
      long long product = 1;
      for (int j = i; j < n; j++) {
        product *= nums[j];
        if (product > best) best = product;
      }
    }

    cout << "Case #" << case_id++ << ": The maximum product is " << best
         << ".\n\n";
  }
}
