// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=113&page=show_problem&problem=655
// UVa714 Copying Books
#include <bits/stdc++.h>
using namespace std;

int m, K;
long long P[505];

// 检查能否用 k 个抄写员完成，且每个抄写员的最大工作量 <= maxWork
bool canDivide(long long maxWork) {
    int scribers = 1;      // 当前需要的抄写员数量
    long long current = 0; // 当前抄写员的工作量

    for (int i = 1; i <= m; i++) {
        if (current + P[i] > maxWork) {
            // 当前抄写员放不下这本书，需要新的抄写员
            scribers++;
            current = P[i];
        } else {
            // 当前抄写员继续拿这本书
            current += P[i];
        }
    }

    return scribers <= K;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        // freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    while (T--) {
        cin >> m >> K;

        long long maxPage = 0;    // 单本书的最大页数
        long long totalPages = 0; // 总页数

        for (int i = 1; i <= m; i++) {
            cin >> P[i];
            maxPage = max(maxPage, P[i]);
            totalPages += P[i];
        }

        // 二分搜索：找最小的最大工作量
        long long L = maxPage;    // 下界：至少要能放下最大的那本书
        long long R = totalPages; // 上界：最多是所有书给一个人
        long long ans = R;

        while (L <= R) {
            long long mid = L + (R - L) / 2;
            if (canDivide(mid)) {
                ans = mid;   // 可行，记录答案
                R = mid - 1; // 尝试更小的值
            } else {
                L = mid + 1; // 不可行，需要更大的值
            }
        }

        // 根据 ans 构造字典序最小的分配方案
        // 策略：从后往前贪心，尽量让后面的抄写员多干活（工作量接近 ans）

        // 先从后往前确定必须的分隔点
        vector<bool> mustSplit(m + 1,
                               false); // mustSplit[i] 表示第 i 本书后面必须分隔
        int numScribers = 1;
        long long current = 0;

        for (int i = m; i >= 1; i--) {
            if (current + P[i] > ans) {
                // 加上这本书会超过 ans，必须分隔
                mustSplit[i] = true;
                numScribers++;
                current = P[i];
            } else {
                current += P[i];
            }
        }

        // 如果抄写员数量不够 k 个，从前往后补充分隔点
        // 这样可以让前面的抄写员尽量少干活（字典序最小）
        for (int i = 1; i < m && numScribers < K; i++) {
            if (!mustSplit[i]) {
                mustSplit[i] = true;
                numScribers++;
            }
        }

        // 输出结果
        for (int i = 1; i <= m; i++) {
            cout << P[i];
            if (mustSplit[i]) {
                cout << " /";
            }
            if (i < m)
                cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
