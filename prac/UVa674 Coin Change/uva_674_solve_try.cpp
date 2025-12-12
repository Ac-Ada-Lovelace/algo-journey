// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=114&page=show_problem&problem=615
// UVa674 Coin Change
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 7490;
int coins[5] = {50, 25, 10, 5, 1};
int dp[MAXN];

// 预处理：计算凑出每个金额的方法数
void preprocess() {
    // 初始化：凑出0元有1种方法（什么都不选）
    dp[0] = 1;

    // 对于每种硬币
    for (int i = 0; i < 5; i++) {
        int coin = coins[i];
        // 更新所有能用到这种硬币的金额
        for (int amount = coin; amount < MAXN; amount++) {
            dp[amount] += dp[amount - coin];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // 预处理一次，后续查询O(1)返回
    preprocess();

    int amount;
    while (cin >> amount) {
        cout << dp[amount] << '\n';
    }

    return 0;
}
