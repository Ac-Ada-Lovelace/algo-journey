// UVa 1606 - 标准扫描线实现
// 关键：理解"半平面"的概念
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

struct Point {
    long long x, y;
    int type;
} p[MAXN], temp[MAXN];

int n;

// 叉积：判断 c 在向量 ab 的哪一侧
// > 0: 左侧，< 0: 右侧，= 0: 共线
long long cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int solve(int id) {
    int m = 0;
    // 复制除了 id 之外的所有点
    for (int i = 0; i < n; i++) {
        if (i != id) {
            temp[m++] = p[i];
        }
    }

    // 按极角排序
    sort(temp, temp + m, [&](const Point& a, const Point& b) {
        long long c = cross(p[id], a, b);
        return c > 0 || (c == 0 &&
            (a.x - p[id].x) * (a.x - p[id].x) + (a.y - p[id].y) * (a.y - p[id].y) <
            (b.x - p[id].x) * (b.x - p[id].x) + (b.y - p[id].y) * (b.y - p[id].y));
    });

    // 初始：统计所有在右半平面的 type=1
    int cnt = 1; // id 自己
    for (int i = 0; i < m; i++) {
        if (temp[i].type == 1) cnt++;
    }

    int ans = cnt;

    // 扫描：每次让一个点从右半平面移到左半平面
    for (int i = 0; i < m; i++) {
        if (temp[i].type == 1) {
            cnt--; // 疏水离开丙酮侧
        } else {
            cnt++; // 亲水进入水侧
        }
        ans = max(ans, cnt);
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

        int ans = 1;
        for (int i = 0; i < n; i++) {
            ans = max(ans, solve(i));
        }

        cout << ans << endl;
    }

    return 0;
}
