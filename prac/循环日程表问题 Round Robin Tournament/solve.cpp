#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 64;
int table[MAX_N][MAX_N];

/**
 * 循环日程表 - 分治法
 * @param n 选手数量（必须是2的幂次）
 *
 * 核心思想：
 * 1. 递归求解前 n/2 个选手的日程（A块）
 * 2. 通过块拷贝得到其余3块：
 *    - D块（右下）：复制A，编号+n/2
 *    - B块（右上）：A的对手编号+n/2
 *    - C块（左下）：对称关系，直接复制A
 */
void round_robin(int n) {
    // 递归基：2个选手
    if (n == 2) {
        table[0][0] = 1;
        table[0][1] = 2;
        table[1][0] = 2;
        table[1][1] = 1;
        return;
    }

    int half = n / 2;

    // 递归求解前 n/2 个选手的日程（填充左上角A块）
    round_robin(half);

    // 填充其余3个区块
    //
    // 布局：
    //      前half天   后half天
    //     ┌─────────┬─────────┐
    // 前  │    A    │    B    │
    // half├─────────┼─────────┤
    // 选手│    C    │    D    │
    // 后  │         │         │
    // half└─────────┴─────────┘

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int opponent = table[i][j]; // A块中的对手

            // B块（右上）：前half个选手在后half天的对手
            // 对手是后half组的选手，编号+half
            table[i][j + half] = opponent + half;

            // C块（左下）：后half个选手在前half天的内部日程
            // 复制A的结构，但选手编号整体+half
            table[i + half][j] = opponent + half;

            // D块（右下）：后half个选手在后half天的对手
            // 对称关系：对手是前half组的选手（不偏移）
            table[i + half][j + half] = opponent;
        }
    }
}

void print_table(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << table[i][j];
            if (j < n - 1)
                cout << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    int n = pow(2, k);

    round_robin(n);
    print_table(n);

    return 0;
}
