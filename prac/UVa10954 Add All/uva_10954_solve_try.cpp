// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=113&page=show_problem&problem=1895
// UVa10954 Add All
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != 0) {
        priority_queue<int, vector<int>, greater<int>> pq;  // 最小堆

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            pq.push(x);
        }

        long long totalCost = 0;

        while (pq.size() > 1) {
            // 取出最小的两个数
            int a = pq.top();
            pq.pop();
            int b = pq.top();
            pq.pop();

            // 合并代价
            int sum = a + b;
            totalCost += sum;

            // 将结果放回堆
            pq.push(sum);
        }

        cout << totalCost << "\n";
    }

    return 0;
}
