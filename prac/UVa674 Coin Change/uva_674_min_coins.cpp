// 硬币找零 - 求最少硬币数量（变种）
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 7490;
const int INF = 1e9;
int coins[5] = {50, 25, 10, 5, 1};
int dp[MAXN];

// 预处理：计算凑出每个金额的最少硬币数
void preprocess() {
    // 初始化：其他金额初始为无穷大（不可达）
    fill(dp, dp + MAXN, INF);
    // 凑出0元需要0个硬币
    dp[0] = 0;

    // 对于每种硬币
    for (int i = 0; i < 5; i++) {
        int coin = coins[i];
        // 更新所有能用到这种硬币的金额
        for (int amount = coin; amount < MAXN; amount++) {
            // 取最小值：要么不用这个硬币，要么用这个硬币
            dp[amount] = min(dp[amount], dp[amount - coin] + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    preprocess();

    int amount;
    while (cin >> amount) {
        cout << dp[amount] << '\n';
    }

    return 0;
}
