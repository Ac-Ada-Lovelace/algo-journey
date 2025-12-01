#include <bits/stdc++.h>
using namespace std;

struct Item {
  long long s, v;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  if (!(cin >> T)) return 0;
  for (int tc = 1; tc <= T; ++tc) {
    long long N, S1, V1, S2, V2;
    cin >> N >> S1 >> V1 >> S2 >> V2;
    Item a{S1, V1}, b{S2, V2};

    // Choose which item to enumerate to minimize iterations.
    auto iterations = [&](const Item &x) {
      return min<long long>(N / x.s, 100000);  // cap to 1e5 for speed
    };
    if (iterations(a) > iterations(b)) swap(a, b);

    long long best = 0;
    long long max_cnt = iterations(a);
    for (long long i = 0; i <= max_cnt; ++i) {
      long long used = i * a.s;
      if (used > N) break;
      long long rem = N - used;
      long long j = rem / b.s;
      best = max(best, i * a.v + j * b.v);
    }

    cout << "Case #" << tc << ": " << best << "\n";
  }
  return 0;
}
