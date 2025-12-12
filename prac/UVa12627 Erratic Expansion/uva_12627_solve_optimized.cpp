// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=4352
// UVa12627 Erratic Expansion - Optimized Version
// 使用区间递归，O(K) 复杂度
#include <bits/stdc++.h>
using namespace std;

// 预计算：Hour k 时整个网格的红气球总数 = 3^k
long long total_red[31];

void precompute() {
    total_red[0] = 1;
    for (int i = 1; i <= 30; i++) {
        total_red[i] = total_red[i - 1] * 3;
    }
}

// 计算 Hour k 时，第 [A, B] 行的红气球总数
// 行号从 1 开始
long long count_red(int k, long long A, long long B) {
    // Base case
    if (k == 0) {
        return 1; // Hour 0 只有一个红气球
    }

    // 空区间
    if (A > B) {
        return 0;
    }

    long long half = 1LL << (k - 1); // 2^(k-1)

    // 四象限结构：
    // 上半部分 (rows 1 to half):    左上象限 + 右上象限
    // 下半部分 (rows half+1 to 2^k): 左下象限 + 右下象限(全蓝)

    if (B <= half) {
        // 查询区间完全在上半部分
        // 上半部分 = 左上 + 右上，都是 Hour k-1 的完整副本
        // 所以红球数是 Hour k-1 对应行的 2 倍
        return 2 * count_red(k - 1, A, B);
    } else if (A > half) {
        // 查询区间完全在下半部分
        // 下半部分 = 左下 + 右下(全蓝)
        // 左下象限是 Hour k-1 的完整副本
        // 将行号映射到 Hour k-1: [A-half, B-half]
        return count_red(k - 1, A - half, B - half);
    } else {
        // 查询区间跨越上下两部分
        // 分别计算上半部分 [A, half] 和下半部分 [half+1, B]
        long long upper = 2 * count_red(k - 1, A, half);
        long long lower = count_red(k - 1, 1, B - half);
        return upper + lower;
    }
}

int main() {
    
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    precompute();

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int K;
        long long A, B;
        cin >> K >> A >> B;

        long long result = count_red(K, A, B);
        cout << "Case " << t << ": " << result << "\n";
    }

    return 0;
}
