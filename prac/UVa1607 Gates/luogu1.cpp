#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 200000 + 5;
int n, m;
struct node {
    int a, b, w;
} q[maxn];
int work(int k) {
    for (int i = 1; i <= m; i++) {
        int x = q[i].a;
        int y = q[i].b;
        int va = x < 0 ? -x > k : q[x].w;
        int vb = y < 0 ? -y > k : q[y].w;
        q[i].w = !(va && vb);
    }
    return q[m].w;
}
int solve(int vx) {
    int l = 1, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (work(mid) == vx)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
int main() {
    int T;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
            scanf("%d%d", &q[i].a, &q[i].b);
        int v0 = work(0);
        int vx = work(n);
        if (v0 == vx) {
            for (int i = 1; i <= n; i++)
                printf("0");
        } else {
            int x = solve(vx);
            for (int i = 1; i < x; i++)
                printf("0");
            printf("x");
            for (int i = x + 1; i <= n; i++)
                printf("1");
        }
        printf("\n");
    }
    return 0;
}
