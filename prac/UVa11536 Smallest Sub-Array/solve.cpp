// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=2531
// UVa11536 Smallest Sub-Array
#include <bits/stdc++.h>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, M, K;
        cin >> N >> M >> K;

        // 生成序列（0-based索引）
        vector<int> arr(N);
        arr[0] = 1; // X₁
        arr[1] = 2; // X₂
        arr[2] = 3; // X₃
        for (int i = 3; i < N; i++) {
            arr[i] = (arr[i - 1] + arr[i - 2] + arr[i - 3]) % M + 1;
        }

        // 滑动窗口：找包含 [1, K] 所有数字的最短子数组
        // count[x] 记录窗口中数字 x 的出现次数
        vector<int> count(K + 1, 0);
        int covered = 0; // 当前窗口包含了多少个 [1, K] 中的数字
        int min_len = INT_MAX;
        int left = 0;

        for (int right = 0; right < N; right++) {
            // 扩展右边界
            if (arr[right] >= 1 && arr[right] <= K) {
                if (count[arr[right]] == 0) {
                    covered++; // 新覆盖了一个数字
                }
                count[arr[right]]++;
            }

            // 收缩左边界：尽量缩小窗口
            while (covered == K) {
                // 更新最小长度
                min_len = min(min_len, right - left + 1);

                // 尝试移除左边界的元素
                if (arr[left] >= 1 && arr[left] <= K) {
                    count[arr[left]]--;
                    if (count[arr[left]] == 0) {
                        covered--; // 失去了一个数字
                    }
                }
                left++;
            }
        }

        // 输出结果
        cout << "Case " << t << ": ";
        if (min_len == INT_MAX) {
            cout << "sequence nai\n";
        } else {
            cout << min_len << '\n';
        }
    }

    return 0;
}
