// UVa 11572 - 在线算法（边读边处理）
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        unordered_map<long long, int> last_pos;
        int L = 0;
        int maxLen = 0;

        for (int R = 0; R < n; R++) {
            long long x;
            cin >> x;

            if (last_pos.count(x) && last_pos[x] >= L) {
                L = last_pos[x] + 1;
            }

            last_pos[x] = R;
            maxLen = max(maxLen, R - L + 1);
        }

        cout << maxLen << '\n';
    }

    return 0;
}
