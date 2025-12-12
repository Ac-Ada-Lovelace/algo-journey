// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=3590
// UVa1149 Bin Packing
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    while (T--) {
        int n, l;
        cin >> n >> l;
        vector<int> items(n);
        for (int i = 0; i < n; ++i) {
            cin >> items[i];
        }

        sort(items.begin(), items.end());
        vector<bool> used(n, false);

        int L = 0, R = n - 1;
        int count = 0;
        int count_of_box = 0;
        while (items[R] + items[L] > l) {
            R--;
            count++;
            count_of_box++;
        }
        while (count < n) {
            int s = L;
            if (used[s]) {
                L++;
                continue;
            }
            for (int i = s; !used[i] && i <= R; i++) {
                if (items[i + 1] + items[R] > l) {
                    R--;
                    count += 2;
                    count_of_box++;
                }
            }
            L = s;
        }

        cout << count_of_box << '\n\n';
    }
}
