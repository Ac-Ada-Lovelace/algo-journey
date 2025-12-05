// UVa 1606 - O(n³) 但经过优化
// 关键优化：提前break、减少重复计算
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

struct Point {
    long long x, y;
    int type;
} p[MAXN];

int n;

int solve() {
    int ans = 1;

    for (int i = 0; i < n; i++) {
        // 枚举基准点 i
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            // 枚举直线方向（经过 i 和 j）
            long long dx = p[j].x - p[i].x;
            long long dy = p[j].y - p[i].y;

            int cnt = 2; // i 和 j 都在直线上

            // 统计其他点
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;

                long long px = p[k].x - p[i].x;
                long long py = p[k].y - p[i].y;
                long long cross = dx * py - dy * px;

                if (cross == 0) {
                    cnt++; // 在直线上
                } else if (cross > 0) {
                    if (p[k].type == 0) cnt++; // 左侧水，亲水溶解
                } else {
                    if (p[k].type == 1) cnt++; // 右侧丙酮，疏水溶解
                }
            }

            ans = max(ans, cnt);

            // 剪枝：如果已经达到 n，不可能更好
            if (ans == n) return n;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n) {
        for (int i = 0; i < n; i++) {
            cin >> p[i].x >> p[i].y >> p[i].type;
        }

        cout << solve() << endl;
    }

    return 0;
}
