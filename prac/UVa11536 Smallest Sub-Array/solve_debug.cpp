// Debug version showing sliding window process
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, M, K;
        cin >> N >> M >> K;

        // 生成序列
        vector<int> arr(N);
        arr[0] = 1;
        arr[1] = 2;
        arr[2] = 3;
        for (int i = 3; i < N; i++) {
            arr[i] = (arr[i-1] + arr[i-2] + arr[i-3]) % M + 1;
        }

        cout << "\nCase " << t << ":\n";
        cout << "N=" << N << " M=" << M << " K=" << K << "\n";
        cout << "序列: ";
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
        cout << "目标: 找包含 [1, " << K << "] 所有数字的最短子数组\n\n";

        // 滑动窗口
        vector<int> count(K + 1, 0);
        int covered = 0;
        int min_len = INT_MAX;
        int best_left = -1, best_right = -1;
        int left = 0;

        for (int right = 0; right < N; right++) {
            // 扩展右边界
            if (arr[right] >= 1 && arr[right] <= K) {
                if (count[arr[right]] == 0) {
                    covered++;
                }
                count[arr[right]]++;
            }

            // 收缩左边界
            while (covered == K) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    best_left = left;
                    best_right = right;
                    cout << "找到新的最小窗口: [" << left << ", " << right
                         << "] 长度=" << min_len << " 内容={";
                    for (int i = left; i <= right; i++) {
                        if (i > left) cout << ", ";
                        cout << arr[i];
                    }
                    cout << "}\n";
                }

                // 移除左边界
                if (arr[left] >= 1 && arr[left] <= K) {
                    count[arr[left]]--;
                    if (count[arr[left]] == 0) {
                        covered--;
                    }
                }
                left++;
            }
        }

        // 输出结果
        cout << "\n结果: ";
        if (min_len == INT_MAX) {
            cout << "sequence nai\n";
        } else {
            cout << min_len << '\n';
            cout << "最优子数组: [" << best_left << ", " << best_right << "] = {";
            for (int i = best_left; i <= best_right; i++) {
                if (i > best_left) cout << ", ";
                cout << arr[i];
            }
            cout << "}\n";
        }
        cout << "\n";
    }

    return 0;
}
