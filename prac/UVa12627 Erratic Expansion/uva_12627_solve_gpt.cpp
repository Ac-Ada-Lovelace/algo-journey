#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 求：在第 k 层中，区间 [L, R] 的红球数量
ll solve(int k, ll L, ll R) {
    if (L > R)
        return 0;

    if (k == 0) {
        // 第 0 层仅 1 个红球
        return 1;
    }

    ll half = 1LL << (k - 1);

    if (R <= half) {
        // 完全在上半区间：每行红球数 = 2 * f(k-1)
        return 2 * solve(k - 1, L, R);
    } else if (L > half) {
        // 完全在下半区间
        return solve(k - 1, L - half, R - half);
    } else {
        // 跨区间：拆成上半 + 下半
        ll left_part = 2 * solve(k - 1, L, half);
        ll right_part = solve(k - 1, 1, R - half);
        return left_part + right_part;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        ll K, A, B;
        cin >> K >> A >> B;
        cout << "Case " << tc << ": " << solve(K, A, B) << "\n";
    }
    return 0;
}
