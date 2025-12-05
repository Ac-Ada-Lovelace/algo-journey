// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=2619
// UVa11572 Unique Snowflakes
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
#define MAXN 1000000

long cases;
long n;
long long arr[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> cases;
    while (cases--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }

        int L = 1;
        int R = 1;

        unordered_set<long long> S;
        int maxn = 0;
        while (R <= n) {
            if (S.count(arr[R])) {
                // 发现重复，先记录当前窗口大小
                maxn = max(maxn, R - L);

                // 移动 L 直到移除重复元素
                while (L <= R) {
                    if (arr[L] == arr[R]) {
                        L++;
                        break;
                    }
                    S.erase(arr[L]);
                    L++; // 移动 L
                }
            }

            // 无论是否重复，都要加入当前元素并移动 R
            S.insert(arr[R]);
            R++;
        }

        // 统计最后一个窗口
        maxn = max(maxn, (int)S.size());

        cout << maxn << '\n';
    }
}
