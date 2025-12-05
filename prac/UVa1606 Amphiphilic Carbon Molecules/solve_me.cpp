#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000

bool polar_less(long long ax, long long ay, long long bx, long long by) {
    auto quadrant = [](long long x, long long y) {
        return (y > 0 || (y == 0 && x >= 0)) ? 1 : 0;
    };

    int qa = quadrant(ax, ay);
    int qb = quadrant(bx, by);

    if (qa != qb)
        return qa > qb;

    long long cross = ax * by - ay * bx;
    if (cross != 0)
        return cross > 0;

    long long da = ax * ax + ay * ay;
    long long db = bx * bx + by * by;
    return da < db;
}

struct particle {
    long x, y, type;
};

int n;
particle particles[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        if (n == 0) {
            break;
        }

        int x, y, t;
        for (int i = 1; i <= n; i++) {
            cin >> x >> y >> t;
            particles[i] = {x, y, t};
        }

        int ans = 1;
        for (int i = 1; i <= n; i++) {
            int pw = 0;
            int pb = 0;
            int zw = 0;
            int zb = 0;
            int pt = 0;

            particle p_exp_base[MAXN];
            memcpy(p_exp_base, particles + 1, (i - 1) * sizeof(particle));
            memcpy(p_exp_base + i - 1, particles + i + 1,
                   (n - i) * sizeof(particle));

            sort(p_exp_base, p_exp_base + n - 1,
                 [=](const particle& a, const particle& b) {
                     return polar_less(
                         a.x - particles[i].x, a.y - particles[i].y,
                         b.x - particles[i].x, b.y - particles[i].y);
                 });

            // 扫描线算法：O(n log n)
            // 初始状态：直线指向第0个点，统计其他点的位置
            int cnt = 1; // 基准点 i
            if (n > 1) {
                cnt++; // 第0个点在直线上

                // 统计其他点（j=1 到 n-2）相对于第0个点方向的位置
                long long dx0 = p_exp_base[0].x - particles[i].x;
                long long dy0 = p_exp_base[0].y - particles[i].y;

                for (int j = 1; j < n - 1; j++) {
                    long long px = p_exp_base[j].x - particles[i].x;
                    long long py = p_exp_base[j].y - particles[i].y;
                    long long cross = dx0 * py - dy0 * px;

                    if (cross == 0) {
                        cnt++; // 在直线上
                    } else if (cross < 0) {
                        // 右侧（丙酮侧）
                        if (p_exp_base[j].type == 1) cnt++;
                    }
                    // cross > 0: 左侧（水侧），type=0 才溶解，但这些点还没移过来
                }

                pt = max(pt, cnt);

                // 扫描：直线逆时针旋转
                for (int j = 1; j < n - 1; j++) {
                    // 点 j 从右侧移到直线上再移到左侧
                    long long xj = p_exp_base[j].x - particles[i].x;
                    long long yj = p_exp_base[j].y - particles[i].y;
                    long long xj1 = p_exp_base[j - 1].x - particles[i].x;
                    long long yj1 = p_exp_base[j - 1].y - particles[i].y;

                    // 检查是否与前一个点共线
                    if (xj * yj1 - yj * xj1 != 0) {
                        // 不共线，发生了转移
                        if (p_exp_base[j].type == 1) {
                            cnt--; // 疏水从右移到左，不再溶解
                        } else {
                            cnt++; // 亲水从右移到左，开始溶解
                        }
                    } else {
                        // 共线，仍在直线上
                        cnt++;
                    }

                    pt = max(pt, cnt);
                }
            }

            ans = max(ans, pt);
        }

        cout << ans << endl;
    }
}
