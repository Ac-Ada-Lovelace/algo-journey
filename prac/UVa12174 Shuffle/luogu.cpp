#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int t, n, s, pd, ans, a[100010], book[100010], bj[100010];
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &s, &n);
        memset(a, 0, sizeof a);
        memset(book, 0, sizeof book);
        memset(bj, 0, sizeof bj);
        pd = 0;
        ans = s;
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        for (int i = 1; i <= n + s; i++) {
            if (i > s) {
                book[a[i - s]]--;
                if (book[a[i - s]] == 1)
                    pd--;
            }
            book[a[i]]++;
            if (book[a[i]] > 1 && a[i])
                pd++;
            if (pd > 0)
                bj[i % s] = 1;
        }
        for (int i = 0; i < s; i++)
            ans -= bj[i];
        printf("%d\n", ans);
    }
    return 0;
}
