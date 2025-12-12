#include <bits/stdc++.h>
using namespace std;

int main() {
    // 设置随机种子
    srand(time(0));
    freopen("input.txt", "w", stdout);

    // 生成的测试用例数量
    int testCases = 10;

    for (int t = 0; t < testCases; t++) {
        // 随机生成 n (范围 1 到 20，可以调整)
        int n = rand() % 20 + 1;

        // 生成 1 到 n 的排列
        vector<int> perm;
        for (int i = 1; i <= n; i++) {
            perm.push_back(i);
        }

        // 随机打乱
        random_shuffle(perm.begin(), perm.end());

        // 输出：n 后面跟着排列
        cout << n;
        for (int x : perm) {
            cout << " " << x;
        }
        cout << "\n";
    }

    // 结束标志
    cout << "0\n";

    return 0;
}
