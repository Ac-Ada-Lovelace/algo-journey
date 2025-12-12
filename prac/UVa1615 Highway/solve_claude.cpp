#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, D, N;

    // 多组测试数据，以 EOF 结束
    while (cin >> L >> D >> N) {
        vector<pair<double, double>> intervals;

        // 步骤1：读取村庄并计算区间
        for (int i = 0; i < N; i++) {
            long long x, y;
            cin >> x >> y;

            // 计算可行区间
            double delta = sqrt((double)D * D - (double)y * y);
            double left = x - delta;
            double right = x + delta;

            // 裁剪到 [0, L]
            left = max(0.0, left);
            right = min((double)L, right);

            // 存储区间
            intervals.push_back({left, right});
        }

        // 步骤2：按右端点排序
        sort(intervals.begin(), intervals.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 if (a.second != b.second)
                     return a.second < b.second;
                 return a.first < b.first;
             });

        // 步骤3：贪心选点
        int count = 0;
        double last_point = -1e9;

        for (auto i : intervals) {
            double left = i.first;
            double right = i.second;
            if (last_point < left) {
                // 当前区间未被覆盖，需要新点
                count++;
                last_point = right; // 选择右端点
            }
            // 否则当前区间已被覆盖，跳过
        }

        cout << count << "\n";
    }

    return 0;
}
