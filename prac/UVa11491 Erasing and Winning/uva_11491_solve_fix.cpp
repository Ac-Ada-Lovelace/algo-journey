// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=2486
// UVa11491 Erasing and Winning
// 使用单调递减栈的贪心算法
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    int N, D;
    string num;

    while (cin >> N >> D && (N || D)) {
        cin >> num;  // 一次性读入整个数字字符串

        string result;  // 作为栈使用
        int toRemove = D;  // 还需要删除的数字个数

        // 遍历每个数字
        for (char c : num) {
            // 如果当前数字比栈顶大，且还有删除配额
            // 就持续删除栈顶较小的数字
            while (!result.empty() &&
                   result.back() < c &&
                   toRemove > 0) {
                result.pop_back();
                toRemove--;
            }
            result.push_back(c);
        }

        // 如果遍历完还没删够（说明数字是递减的）
        // 删除末尾的字符
        // 例如：54321 删除 2 个 → 应该保留前 3 位 543
        result.resize(N - D);

        cout << result << "\n";
    }
    cout << '\n';

    return 0;
}
