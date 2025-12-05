#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, type;
} p[1010];

struct Polar {
    double x, y, angle;
} a[1010];

bool cmp(Polar a, Polar b) {
    return a.angle < b.angle;
}

bool flag(Polar L, Polar R) {
    return L.x * R.y - L.y * R.x >= 0;
}

int solve(int pos, int n) {
    int tot = 0;

    // 坐标变换
    for (int i = 1; i <= n; i++) {
        if (i == pos)
            continue;

        double dx = p[i].x - p[pos].x;
        double dy = p[i].y - p[pos].y;

        // 黑点取反
        if (p[i].type == 1) {
            dx = -dx;
            dy = -dy;
        }

        a[++tot] = {dx, dy, atan2(dy, dx)};
    }

    sort(a + 1, a + tot + 1, cmp);

    // 双指针
    int L = 1, R = 1, ans = 2, maxn = 0;

    while (L <= tot) {
        if (R == L)
            R = (R % tot) + 1, ans++;

        while (R != L && flag(a[L], a[R]))
            R = (R % tot) + 1, ans++;

        maxn = max(ans, maxn);
        L++;
        ans--;
    }

    return maxn;
}

int main() {
    int n;
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) {
            cin >> p[i].x >> p[i].y >> p[i].type;
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, solve(i, n));
        }

        cout << ans - 1 << endl;
    }
    return 0;
}
