#include <bits/stdc++.h>
using namespace std;

/**
 * 巨人与鬼问题 - 分治法实现
 *
 * 核心思想：
 * 1. 将巨人和鬼按x坐标排序
 * 2. 分为两半：左边k个巨人配左边k个鬼，右边n-k个配右边n-k个
 * 3. 递归求解左右两个子问题
 * 4. 由于排序保证了左边的连线不会和右边的交叉，直接合并即可
 *
 * 时间复杂度：O(n log n)
 * - 预排序：O(n log n)
 * - 递归：T(n) = 2T(n/2) + O(1) = O(n)
 * - 总计：O(n log n)
 */

struct Point {
    double x, y;
    int id;  // 原始编号（0-based）
};

bool cmp_x(const Point& a, const Point& b) {
    if (abs(a.x - b.x) > 1e-9) return a.x < b.x;
    return a.y < b.y;
}

vector<Point> giants, ghosts;
vector<int> match;  // match[i] = 巨人i配对的鬼编号

/**
 * 分治求解
 * @param gl, gr: 巨人数组的左右边界 [gl, gr]
 * @param dl, dr: 鬼数组的左右边界 [dl, dr]
 *
 * 前置条件：giants[gl..gr] 和 ghosts[dl..dr] 已按x坐标排序
 */
void divide_and_conquer(int gl, int gr, int dl, int dr) {
    // 递归基：只有一个巨人和一个鬼
    if (gl == gr) {
        match[giants[gl].id] = ghosts[dl].id;
        return;
    }

    // 分治：将当前问题分为两半
    int g_mid = (gl + gr) / 2;
    int d_mid = (dl + dr) / 2;

    // 左半部分：giants[gl..g_mid] 配对 ghosts[dl..d_mid]
    divide_and_conquer(gl, g_mid, dl, d_mid);

    // 右半部分：giants[g_mid+1..gr] 配对 ghosts[d_mid+1..dr]
    divide_and_conquer(g_mid + 1, gr, d_mid + 1, dr);

    // 合并：无需额外操作，因为左右两边的连线不会相交
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    giants.resize(n);
    ghosts.resize(n);
    match.resize(n);

    // 读入巨人坐标
    for (int i = 0; i < n; i++) {
        cin >> giants[i].x >> giants[i].y;
        giants[i].id = i;  // 记录原始编号
    }

    // 读入鬼坐标
    for (int i = 0; i < n; i++) {
        cin >> ghosts[i].x >> ghosts[i].y;
        ghosts[i].id = i;
    }

    // 关键步骤1：按x坐标排序（只需排序一次）
    sort(giants.begin(), giants.end(), cmp_x);
    sort(ghosts.begin(), ghosts.end(), cmp_x);

    // 关键步骤2：分治求解
    divide_and_conquer(0, n - 1, 0, n - 1);

    // 输出结果（编号从1开始）
    for (int i = 0; i < n; i++) {
        cout << match[i] + 1 << "\n";
    }

    return 0;
}
