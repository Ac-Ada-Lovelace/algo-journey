#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll allRed[35]; // allRed[k] = 第 k 小时整张图的红气球总数 = 3^k

// S(k, i): 第 k 小时，从第 1 行到第 i 行（前 i 行）的红气球总数
ll S(int k, ll i) {
    if (i <= 0)
        return 0; // 前 0 行，红球数为 0
    if (k == 0)
        return 1; // 第 0 小时只有 1 行 1 列，且为红

    ll half = 1LL << (k - 1); // 行数一半 = 2^(k-1)

    if (i <= half) {
        // i 在上半部分：由两个 R(k-1) 组成
        // 上半前 i 行 = 2 * 第 k-1 小时前 i 行
        return 2 * S(k - 1, i);
    } else {
        // i 在下半部分：
        // 1..half 行：完整上半部分 = 2 * allRed[k-1]
        // half+1..i 行：来自左下 R(k-1)，对应到上一层是前 (i-half) 行
        return 2 * allRed[k - 1] + S(k - 1, i - half);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预处理 allRed[k] = 3^k
    allRed[0] = 1;
    for (int k = 1; k <= 30; ++k) {
        allRed[k] = allRed[k - 1] * 3;
    }

    int T;
    if (!(cin >> T))
        return 0;

    for (int tc = 1; tc <= T; ++tc) {
        int K;
        ll A, B;
        cin >> K >> A >> B;

        ll ans = S(K, B) - S(K, A - 1);
        cout << "Case " << tc << ": " << ans << "\n";
    }

    return 0;
}
