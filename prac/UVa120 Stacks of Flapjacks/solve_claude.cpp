#include <bits/stdc++.h>
using namespace std;

array<int, 31> pan;
int n;

void flip(int k) {
    // 翻转 pan[k..n]
    for (int i = k, j = n; i < j; i++, j--) {
        swap(pan[i], pan[j]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string line;
    while (getline(cin, line)) {
        // 1. 读取数据
        n = 0;
        stringstream ss(line);
        int p;
        while (ss >> p) {
            n++;
            pan[n] = p;
        }

        // 2. 计算目标状态（升序排列）
        array<int, 31> target(pan);
        sort(target.begin() + 1, target.begin() + n + 1);

        // 3. 执行排序
        vector<int> flips;

        for (int i = 1; i <= n; i++) {
            int goal = target[i]; // 位置i应该放的值

            if (pan[i] == goal) {
                continue; // 已经在正确位置
            }

            // 找到goal在当前pan中的位置
            int pos = 0;
            for (int j = i; j <= n; j++) {
                if (pan[j] == goal) {
                    pos = j;
                    break;
                }
            }

            // 两次翻转移动到位置i
            if (pos != n) {
                // 第一次：翻到顶部
                flip(pos);
                flips.push_back(n - pos + 1);
            }
            // 第二次：翻到目标位置
            flip(i);
            flips.push_back(n - i + 1);
        }

        // 4. 输出结果
        cout << line << endl;
        for (int f : flips) {
            cout << f << " ";
        }
        cout << "0" << endl;
    }

    return 0;
}
