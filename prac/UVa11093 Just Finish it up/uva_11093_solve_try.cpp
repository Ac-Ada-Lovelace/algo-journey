// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=2034
// UVa11093 Just Finish it up
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000

int p[MAXN + 1];
int q[MAXN + 1];
int n;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> q[i];
        }

        int s = 0;
        while (true) {
            int flag = 0;
            int imp = 0;
            int fuel = 0;
            for (int i = s; i < n + s; i++) {
                fuel += p[i % n + 1];

                if (fuel <= q[i % n + 1]) {
                    if (s != 1 && (i % n + 1) == n) {
                        imp = 1;
                    }
                    flag = i % n + 1;
                    s = i % n + 1;
                    break;
                }
                fuel -= q[i % n + 1];
            }

            if (!flag) {
                cout << "Case " << t << ": Possible from station " << s + 1
                     << "\n";
                break;
            } else {
                if (imp) {
                    cout << "Case " << t << ": Not possible\n";
                    break;
                }
                continue;
            }
        }
    }
}
