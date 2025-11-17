#include <bits/stdc++.h>
#include <cstddef>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l = 0;
    cin >> l;
    while (l--) {
        int I, D;
        cin >> D;
        cin >> I;
        vector<bool> tree((size_t)(2 << D), 0);

        size_t ans = 0;
        for (int i = 1; i <= I; ++i) {
            size_t idx = 1;
            for (int d = 0; d < D; ++d) {
                if (!tree[idx]) {
                    tree[idx] = !tree[idx];
                    idx = idx * 2;
                } else {
                    tree[idx] = !tree[idx];
                    idx = idx * 2 + 1;
                }
            }
            if (i == I) {
                ans = idx;
            }
        }
        cout << ans << endl;
    }
    cin >> l;
}
