// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=4352
// UVa12627 Erratic Expansion
#include <bits/stdc++.h>
using namespace std;

long long red_of_line(long long k, long long line) {
    if (k == 0) {
        return 1; // Hour 0: 只有一个红气球
    }
    if (k == 1) {
        if (line == 1) {
            return 2; // 第1行: R R
        } else {
            return 1; // 第2行: R B
        }
    }
    long long half = 1LL << (k - 1);
    if (line > half) {
        // 下半部分：只有左下象限有红球
        return red_of_line(k - 1, line - half);
    } else {
        // 上半部分：左上 + 右上象限都有红球
        return 2 * red_of_line(k - 1, line);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        long long K, A, B;
        cin >> K >> A >> B;

        long long red = 0;
        for (long long i = A; i <= B; i++) {
            red += red_of_line(K, i);
        }
        cout << "Case " << t << ": " << red << "\n";
    }
}
