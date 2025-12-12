/*!
 * FileName: uva-10366.cpp
 * This Problem is on uva. The ID of the problem is 10366.
 * Copyright(c) 2019 Shu_Yu_Mo
 * MIT Licensed
 * Luogu: https://www.luogu.org/space/show?uid=44615
 * Github: https://github.com/oldsuold/
 * Gitee: https://gitee.com/Shu_Yu_Mo/
 * These words were created by an amazing tool on 2019-08-01 20:57:59 written by
 * Shu_Yu_Mo.
 */
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define inf 0x7fffffff
using namespace std;
const int _ = 1e4 + 100;
inline int read() {
    char c = getchar();
    int sign = 1;
    int x = 0;
    while (c > '9' || c < '0') {
        if (c == '-')
            sign = -1;
        c = getchar();
    }
    while (c <= '9' && c >= '0') {
        x *= 10;
        x += c - '0';
        c = getchar();
    }
    return x * sign;
}
int tmpL, tmpR;
int n;
int H[_];
inline int GetNxt_L(int now, bool isSame) {
    for (int i = now - 1; i >= 0; i--)
        if (H[i] > H[now] || (H[i] == H[now] && isSame))
            return i;
    return 0;
}
inline int GetNxt_R(int now, bool isSame) {
    for (int i = now + 1; i <= n + 1; i++)
        if (H[i] > H[now] || (H[i] == H[now] && isSame))
            return i;
    return n + 1;
}
inline int QueryToL(int L, int R) {
    int ans = 0;
    for (int i = L; i <= R; i = GetNxt_R(i, true))
        ans += H[i] * (GetNxt_R(i, true) - i);
    return ans;
}
inline int QueryToR(int L, int R) {
    int ans = 0;
    for (int i = R; i >= L; i = GetNxt_L(i, true))
        ans += H[i] * (i - GetNxt_L(i, true));
    return ans;
}
void doit() {
    n = ((abs(tmpL) + abs(tmpR)) >> 1) + 1;
    for (int i = 1; i <= n; i++)
        H[i] = read();
    H[0] = H[n + 1] = inf;
    int nowl = ((abs(tmpL) + 1) >> 1);
    int nowr = nowl + 1;
    int ans = min(H[nowl], H[nowr]);
    while (true) {
        int nxtL = GetNxt_L(nowl, false);
        int nxtR = GetNxt_R(nowr, false);
        if (nxtL == 0 ||
            nxtR == n + 1) // NxtL == 0就代表往左已经找不到有用柱子了。NxtR == n
                           // + 1就代表往右已经找不到有用柱子了
        {
            bool flag = false; // 是否更新成功标记。
            if (nxtL == 0 && nxtR == n + 1)
                flag = true,
                ans +=
                    (H[nowl] == H[nowr]
                         ? min(QueryToL(1, nowl - 1) << 1, QueryToR(nowr + 1, n)
                                                               << 1)
                         : (H[nowl] < H[nowr]
                                ? QueryToL(1, nowl - 1)
                                : QueryToR(
                                      nowr + 1,
                                      n))); // 请仔细查看这里，这里是处理柱子相同和不相同的情况。（第一个特殊情况）
            if (nxtL == 0 && nxtR != n + 1 &&
                H[nowl] <=
                    H[nowr]) // 如果左边找不到有用柱子，且水的确要往左边流
                flag = true,
                ans += QueryToL(1, nowl - 1) +
                       (H[nowl] == H[nowr] ? min(QueryToL(1, nowl - 1),
                                                 (nxtR - nowr) * H[nowr])
                                           : 0); // 这里是处理第二个特殊情况
            if (nxtL != 0 && nxtR == n + 1 &&
                H[nowl] >=
                    H[nowr]) // 如果右边找不到有用柱子，且水的确要往右边流
                flag = true,
                ans += QueryToR(nowr + 1, n) +
                       (H[nowl] == H[nowr] ? min(QueryToR(nowr + 1, n),
                                                 (nowl - nxtL) * H[nowl])
                                           : 0); // 这里是处理第三个特殊情况
            if (flag)
                break;
        }
        int ToVal_L = (H[nowl] <= H[nowr] ? nxtL : nowl);
        int ToVal_R = (H[nowl] >= H[nowr] ? nxtR : nowr);
        // 这种写法，区间两边高度相等的情况时，两边都能完成拓展。
        nowl = ToVal_L;
        nowr = ToVal_R;
        ans = (nowr - nowl) * min(H[nowl], H[nowr]);
    }
    printf("%d\n", ans << 1);
    return;
}
int main() {
    while (scanf("%d%d", &tmpL, &tmpR) == 2 && tmpL != 0 && tmpR != 0)
        doit();
    return 0;
}
