// Debug version to show algorithm steps
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int n;
        cin >> n;

        vector<pair<int, int>> orders(n);
        for (int i = 0; i < n; i++) {
            cin >> orders[i].first >> orders[i].second;
        }

        // 排序前显示
        cout << "原始订单:\n";
        for (int i = 0; i < n; i++) {
            cout << "  订单" << i+1 << ": 耗时=" << orders[i].first
                 << " 截止=" << orders[i].second << '\n';
        }

        // 按截止日期排序
        sort(orders.begin(), orders.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.second < b.second;
        });

        cout << "\n按截止日期排序后:\n";
        for (int i = 0; i < n; i++) {
            cout << "  位置" << i+1 << ": 耗时=" << orders[i].first
                 << " 截止=" << orders[i].second << '\n';
        }

        priority_queue<int> accepted;
        int current_time = 0;

        cout << "\n贪心选择过程:\n";
        for (int i = 0; i < n; i++) {
            int duration = orders[i].first;
            int deadline = orders[i].second;

            current_time += duration;
            accepted.push(duration);

            cout << "步骤" << i+1 << ": 尝试接受 (耗时=" << duration
                 << ", 截止=" << deadline << ")\n";
            cout << "  当前时间: " << current_time;

            if (current_time > deadline) {
                int longest = accepted.top();
                accepted.pop();
                current_time -= longest;
                cout << " > " << deadline << " 超时！\n";
                cout << "  拒绝耗时最长的订单(耗时=" << longest << ")\n";
                cout << "  调整后时间: " << current_time;
            } else {
                cout << " <= " << deadline << " OK";
            }
            cout << ", 已接受数=" << accepted.size() << '\n';
        }

        cout << "\n最终答案: " << accepted.size() << '\n';
    }

    return 0;
}
