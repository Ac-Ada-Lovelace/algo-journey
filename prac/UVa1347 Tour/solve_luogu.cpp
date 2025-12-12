#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int N = 1e3 + 7;
int n;
struct node {
    int x, y;
} a[N];
double f[N][N];   // f[i][j]表示走过了1~i,还需走多少距离
double dis[N][N]; // dis[i][j]表示i到j的距离

void init() {
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].x, &a[i].y);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dis[i][j] = sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) +
                             (a[i].y - a[j].y) * (a[i].y - a[j].y));

    for (int i = 1; i < n - 1; i++) // 边界条件
        f[n - 1][i] = dis[n - 1][n] + dis[i][n];
}

int main() {
    while (scanf("%d", &n) == 1) {
        // 读入、预处理
        init();

        for (int i = n - 2; i >= 1; i--)
            for (int j = 1; j < i; j++)
                f[i][j] = min(f[i + 1][j] + dis[i + 1][i],
                              f[i + 1][i] + dis[i + 1][j]);

        printf("%.2lf\n", dis[2][1] + f[2][1]);
    }
    return 0;
}
