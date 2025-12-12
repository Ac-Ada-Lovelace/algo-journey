// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=2034
// UVa11093 Just Finish it up
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;

        vector<int> p(n), q(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> q[i];
        }

        // 先检查总油量是否足够（必要条件）
        long long total_fuel = 0, total_cost = 0;
        for (int i = 0; i < n; i++) {
            total_fuel += p[i];
            total_cost += q[i];
        }

        if (total_fuel < total_cost) {
            cout << "Case " << t << ": Not possible\n";
            continue;
        }

        // 贪心找起点
        int start = -1;
        int current_try = 0; // 当前尝试的起点（0-based）

        while (current_try < n) {
            long long fuel = 0;
            bool success = true;

            // 从 current_try 出发，尝试跑一圈
            for (int i = 0; i < n; i++) {
                int station = (current_try + i) % n;
                fuel += p[station]; // 加油

                if (fuel < q[station]) {
                    // 油不够到下一站
                    success = false;
                    // 关键优化：下一个可能的起点是 station + 1
                    // 因为从 current_try 到 station
                    // 之间的任何站出发都不可能成功
                    current_try = (current_try + i + 1);
                    break;
                }

                fuel -= q[station]; // 消耗油去下一站
            }

            if (success) {
                start = current_try;
                break;
            }
        }

        if (start != -1) {
            cout << "Case " << t << ": Possible from station " << (start + 1)
                 << "\n";
        } else {
            cout << "Case " << t << ": Not possible\n";
        }
    }

    return 0;
}
