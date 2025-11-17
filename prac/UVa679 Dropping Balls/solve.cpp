#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int cases;
  if (!(cin >> cases)) return 0;
  while (cases--) {
    int D;
    long long I;
    cin >> D >> I;
    long long node = 1;
    for (int level = 1; level < D; ++level) {
      if (I % 2 == 1) {
        node = node * 2;
        I = (I + 1) / 2;
      } else {
        node = node * 2 + 1;
        I /= 2;
      }
    }
    cout << node << "\n";
  }
  long long sentinel;
  cin >> sentinel;  // consume trailing -1
  return 0;
}
