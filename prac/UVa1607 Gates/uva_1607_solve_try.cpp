// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=4482
// UVa1607 Gates
#include <bits/stdc++.h>
using namespace std;
#define MAXM 200000
#define MAXN 100000

int input[MAXN + 1];     // 1 means 1, 0 means 0, -1 means from x
int gates[2 * MAXM + 1]; // gates[2*i-1] and gates[2*i] are inputs to gate i
int m, n;

// 使用局部缓存，避免每次清空
bool get_output(int g, int x, vector<int>& cache) {
    // 检查缓存
    if (cache[g] != -1) {
        return cache[g];
    }

    int l = gates[2 * g - 1];
    int r = gates[2 * g];

    int li, ri;

    // 获取左输入
    if (l > 0) {
        li = get_output(l, x, cache);
    } else {
        li = input[-l] < 0 ? x : input[-l];
    }

    // 获取右输入
    if (r > 0) {
        ri = get_output(r, x, cache);
    } else {
        ri = input[-r] < 0 ? x : input[-r];
    }

    // NAND 运算并缓存结果
    int result = !(li && ri);
    cache[g] = result;
    return result;
}

bool test(int x) {
    vector<int> cache(m + 1, -1); // 每次test创建新缓存
    return get_output(m, x, cache);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> n >> m;

        for (int i = 1; i <= 2 * m; i++) {
            cin >> gates[i];
        }

        // 初始化：所有输入都连接到 x
        for (int i = 1; i <= n; i++) {
            input[i] = -1;
        }

        bool f0 = test(0);
        bool f1 = test(1);

        if (f0 == f1) {
            // 电路是常量，所有输入都可以设为同一个值
            for (int i = 1; i <= n; i++) {
                cout << (f0 ? '1' : '0');
            }
        } else {
        }
        cout << "\n";
    }

    return 0;
}
