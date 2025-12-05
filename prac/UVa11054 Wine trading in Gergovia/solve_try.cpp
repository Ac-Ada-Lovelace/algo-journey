// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=113&page=show_problem&problem=1995
// UVa11054 Wine trading in Gergovia
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000

long long houses[MAXN + 1];
long long n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        for (int i = 1; i <= n; i++) {
            cin >> houses[i];
        }

        long long a = 0, b = 0;
        for (int i = 1; i <= n; i++) {
            a += houses[i];
            b += abs(a);
        }

        cout << b << "\n";
    }
}
