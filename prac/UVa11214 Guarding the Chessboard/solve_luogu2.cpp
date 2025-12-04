#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, T, a[15][15], b[15][15], ans, c[15][15];
bool dfs(int x, int y, int o1, int o2) {
    /*cout<<x<<" "<<y<<" "<<o1<<" "<<o2<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            cout<<b[i][j]<<" ";
        cout<<endl;
    }*/
    if (x == y)
        return ans > 0 ? false : true;
    if (ceil(ans / 1.0 / (n + m - 1 + min(n, m) * 2 - 2)) > y - x)
        return false;
    o2++;
    if (o2 > m)
        o1++, o2 = 1;
    int i = o1, j = o2;
    for (i = o1; i <= n; i++) {
        for (; j <= m; j++) {
            vector<pair<int, int>> v;
            for (int k = 1; k <= n; k++)
                if (a[k][j] == 1 && b[k][j] == 0)
                    b[k][j] = 1, v.push_back(pair<int, int>(k, j));
            for (int k = 1; k <= m; k++)
                if (a[i][k] == 1 && b[i][k] == 0)
                    b[i][k] = 1, v.push_back(pair<int, int>(i, k));
            for (int k = 1; k <= min(i + j, n); k++)
                if (i + j - k >= 1 && i + j - k <= m && a[k][i + j - k] == 1 &&
                    b[k][i + j - k] == 0)
                    b[k][i + j - k] = 1,
                                 v.push_back(pair<int, int>(k, i + j - k));
            for (int k = 1; k <= n; k++)
                if (k + j - i >= 1 && k + j - i <= m && a[k][k + j - i] == 1 &&
                    b[k][k + j - i] == 0)
                    b[k][k + j - i] = 1,
                                 v.push_back(pair<int, int>(k, k + j - i));
            if (v.size() == 0)
                continue;
            ans -= v.size();
            if (dfs(x + 1, y, i, j))
                return true;
            ans += v.size();
            for (int k = 0; k < v.size(); k++)
                b[v[k].first][v[k].second] = 0;
        }
        j = 1;
    }
    return false;
}
signed main() {
    // freopen("in","r",stdin);
    // freopen("myout.txt","w",stdout);
    while (~scanf("%lld", &n) && n) {
        T++;
        memset(b, 0, sizeof(b));
        memset(a, 0, sizeof(a));
        scanf("%lld", &m);
        ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                char sut;
                cin >> sut;
                if (sut == 'X')
                    a[i][j] = 1, ans++;
            }
        for (int i = 0; i <= 9; i++) {
            if (dfs(0, i, 1, 0)) {
                printf("Case %lld: %lld\n", T, i);
                break;
            }
        }
    }
    return 0;
}
/*
6 6
XXXX..
XX..XX
..X...
X.....
X...XX
.XX...
*/
