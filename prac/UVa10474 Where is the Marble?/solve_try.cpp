#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, Q;
  int caseNo = 1;
  while (cin >> N >> Q) {
    if (N == 0 && Q == 0) break;

    vector<int> marbles(N);
    for (int i = 0; i < N; ++i) cin >> marbles[i];
    sort(marbles.begin(), marbles.end());

    cout << "CASE# " << caseNo++ << ":\n";
    while (Q--) {
      int queryValue;
      cin >> queryValue;

      auto it = lower_bound(marbles.begin(), marbles.end(), queryValue);
      if (it == marbles.end() || *it != queryValue) {
        cout << queryValue << " not found\n";
      } else {
        cout << queryValue << " found at " << (it - marbles.begin() + 1) << "\n";
      }
    }
  }
  return 0;
}
