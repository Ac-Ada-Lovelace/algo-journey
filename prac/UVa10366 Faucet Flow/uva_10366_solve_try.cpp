// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=1307
// UVa10366 Faucet Flow
#include <bits/stdc++.h>
using namespace std;

int lx, rx;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (true) {
        cin >> lx >> rx;
        int n = 0;

        if (lx == 0 && rx == 0)
            break;
    
        vector<pair<int, int>> bs;
        for (int i = lx; i <= rx; i += 2) {
            int h;
            cin >> h;
            bs.emplace_back(i, h);
            n++;
        }

        pair<int, int> a = bs[n - 2];
        pair<int, int> b = bs[n - 1];
        int ax = a.first, ah = a.second;
        int bx = b.first, bh = b.second;
        int v = 0;

        if (ah > bh) {
            int lbx = 0, lbh = 0;
            for (int i = n - 3; i >= 0; i--) {
                if (bs[i].second >= ah) {
                    lbx = bs[i].first;
                    lbh = bs[i].second;
                    break;
                }
            }
            if (lbh == ah) {
                v = 2 * bh * 2 + (ax - lbx) * (lbh);
            } else {
                v = 2 * bh * 1 + (ax - lbx) * (lbh);
            }

        } else {
            int lbx = 0, lbh = 0;
            for (int i = n - 3; i >= 0; i--) {
                if (bs[i].second >= bh) {
                    lbx = bs[i].first;
                    lbh = bs[i].second;
                    break;
                }
            }

            v = (bx - lbx) * (lbh);
        }

        cout << v << '\n';
    }
}
