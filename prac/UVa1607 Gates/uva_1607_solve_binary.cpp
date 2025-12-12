// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=4482
// UVa1607 Gates - 二分优化版本
#include <bits/stdc++.h>
using namespace std;
#define MAXM 200000
#define MAXN 100000

int input[MAXN + 1]; // 1 means 1, 0 means 0, -1 means from x
int gates[2 * MAXM + 1]; // gates[2*i-1] and gates[2*i] are inputs to gate i
int m, n;

bool get_output(int g, int x, vector<int>& cache) {
    if (cache[g] != -1) {
        return cache[g];
    }

    int l = gates[2 * g - 1];
    int r = gates[2 * g];

    int li = (l > 0) ? get_output(l, x, cache) : (input[-l] < 0 ? x : input[-l]);
    int ri = (r > 0) ? get_output(r, x, cache) : (input[-r] < 0 ? x : input[-r]);

    cache[g] = !(li && ri);
    return cache[g];
}

bool test(int x) {
    vector<int> cache(m + 1, -1);
    return get_output(m, x, cache);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> n >> m;

        for (int i = 1; i <= 2 * m; i++) {
            cin >> gates[i];
        }

        // 初始化：所有输入都连接到 x
        for (int i = 1; i <= n; i++) {
            input[i] = -1;
        }

        int f0 = test(0);
        int f1 = test(1);

        if (f0 == f1) {
            // 常量电路，全部输出相同值
            for (int i = 1; i <= n; i++) {
                cout << f0;
            }
        } else {
            // 需要至少一个 x
            // 二分策略：缩小必须包含 x 的区间

            int left = 1, right = n;

            // 二分查找：找到一个位置 pos，使得只在 pos 放 x 就足够
            while (left < right) {
                int mid = (left + right) / 2;

                // 测试：把 [1, mid] 全设为 f0，[mid+1, n] 全设为 x
                // 看这样是否仍然 f(0) != f(1)
                for (int i = 1; i <= mid; i++) {
                    input[i] = f0;
                }
                for (int i = mid + 1; i <= n; i++) {
                    input[i] = -1;  // 设为 x
                }

                int test_f0 = test(0);
                int test_f1 = test(1);

                if (test_f0 != test_f1) {
                    // 只用 [mid+1, n] 的 x 就够了
                    // x 必须在 [mid+1, n] 中
                    left = mid + 1;
                } else {
                    // 不够，[1, mid] 中也需要有 x
                    // x 必须在 [1, mid] 中
                    right = mid;
                }
            }

            // left 是关键位置，只在这个位置放 x
            for (int i = 1; i <= n; i++) {
                input[i] = f0;
            }
            input[left] = -1;

            // 输出结果
            for (int i = 1; i <= n; i++) {
                if (input[i] == -1) {
                    cout << 'x';
                } else {
                    cout << input[i];
                }
            }
        }
        cout << "\n";
    }

    return 0;
}
