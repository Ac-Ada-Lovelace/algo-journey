#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int read() {
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        k = k * 10 + c - 48, c = getchar();
    return k * f;
}

struct zzz {
    int x, y, col;
} p[1010]; // 存初始点
struct hhh {
    double x, y, d;
} a[1010]; // 重新建系后的点

bool cmp(hhh x, hhh y) {
    return x.d < y.d;
}
bool flag(hhh x, hhh y) { // 向量叉积判断x、y相差的角度是否小于180度
    return x.x * y.y - x.y * y.x >= 0;
}
int check(int pos, int n) {         // 以a[pos]为基准点
    int tot = 0, ans = 2, maxn = 0; // 因为分隔线经过两点，所以ans初始值为2
    for (int i = 1; i <= n; ++i) {
        if (i == pos)
            continue; // 去除基准点
        // 以下为 以基准点为坐标原点，重新建系
        a[++tot].x = p[i].x - p[pos].x;
        a[tot].y = p[i].y - p[pos].y;
        if (p[i].col)
            a[tot].x *= -1, a[tot].y *= -1; // 上面提到的小优化
        a[tot].d = atan2(a[tot].y, a[tot].x);
    }
    sort(a + 1, a + tot + 1, cmp); // 按极角排序
    int L = 1, R = 1;              // 两个指针动态维护，保证当前区间的合法性
    // ans存a[L]~a[R]之间在直线同一侧的点的数量
    while (L <= tot) { // 维护答案
        if (R == L)
            R = (R % tot) + 1, ++ans;
        while (R != L && flag(a[L], a[R]))
            R = (R % tot) + 1, ++ans;
        ++L;
        --ans;
        maxn = max(ans, maxn);
    }
    return maxn;
}
int solve() { // 程序框架
    int n = read(), ans = 0;
    if (n == 0)
        exit(0);
    if (n <= 2)
        return 2;
    for (int i = 1; i <= n; ++i)
        p[i].x = read(), p[i].y = read(), p[i].col = read();
    for (int i = 1; i <= n; ++i)
        ans = max(ans, check(i, n));
    return ans;
}
int main() {
    while (1)
        printf("%d\n", solve());
    return 0;
}
