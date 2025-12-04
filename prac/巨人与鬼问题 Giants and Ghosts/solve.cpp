#include <bits/stdc++.h>
using namespace std;

/**
 * 巨人与鬼问题 - 质子流版本（无交叉匹配）
 *
 * 问题：n个巨人和n个鬼，找到一种配对使得所有连线不相交
 * 算法：排序法 - 按x坐标排序后顺序配对
 * 时间复杂度：O(n log n)
 */

struct Point {
    double x, y;
    int id; // 原始编号（1-based）
};

// 按x坐标排序，x相同时按y坐标排序
bool cmp_x(const Point& a, const Point& b) {
    if (abs(a.x - b.x) > 1e-9)
        return a.x < b.x;
    return a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> giants(n), ghosts(n);

    // 读入巨人坐标
    for (int i = 0; i < n; i++) {
        cin >> giants[i].x >> giants[i].y;
        giants[i].id = i + 1; // 编号从1开始
    }

    // 读入鬼坐标
    for (int i = 0; i < n; i++) {
        cin >> ghosts[i].x >> ghosts[i].y;
        ghosts[i].id = i + 1;
    }

    // 关键步骤：按x坐标排序
    sort(giants.begin(), giants.end(), cmp_x);
    sort(ghosts.begin(), ghosts.end(), cmp_x);

    // 建立配对映射：第i个巨人（原始编号）→ 配对的鬼编号
    vector<int> match(n + 1);
    for (int i = 0; i < n; i++) {
        match[giants[i].id] = ghosts[i].id;
    }

    // 输出配对方案
    for (int i = 1; i <= n; i++) {
        cout << match[i] << "\n";
    }

    return 0;
}
