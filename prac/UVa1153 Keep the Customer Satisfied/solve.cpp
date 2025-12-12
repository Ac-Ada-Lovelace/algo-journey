// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=3594
// UVa1153 Keep the Customer Satisfied
// Hodgson-Moore Algorithm: 最大化完成的订单数
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        if (t > 0)
            cout << '\n'; // 测试用例之间空行

        int n;
        cin >> n;

        // 读取所有订单: (耗时, 截止日期)
        vector<pair<int, int>> orders(n);
        for (int i = 0; i < n; i++) {
            cin >> orders[i].first >> orders[i].second; // q, d
        }

        // 步骤1: 按截止日期排序（非递减）
        // 这是Hodgson-Moore算法的关键：先处理截止日期早的订单
        sort(orders.begin(), orders.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        // 步骤2: 贪心选择 + 最大堆
        // 最大堆存储已接受订单的耗时
        priority_queue<int> accepted; // 最大堆（耗时最长的在顶部）
        int current_time = 0;

        for (int i = 0; i < n; i++) {
            int duration = orders[i].first;  // 订单耗时
            int deadline = orders[i].second; // 订单截止日期

            // 尝试接受当前订单
            current_time += duration;
            accepted.push(duration);

            // 如果会错过截止日期
            if (current_time > deadline) {
                // 移除耗时最长的订单（可能是刚加入的当前订单）
                int longest = accepted.top();
                accepted.pop();
                current_time -= longest;

                // 贪心策略：拒绝耗时长的订单，为后续订单留出更多时间
                // 因为后续订单截止日期更晚，用短订单替换长订单更优
            }
        }

        // 堆中剩余的就是所有被接受的订单
        cout << accepted.size() << '\n';
    }

    return 0;
}
