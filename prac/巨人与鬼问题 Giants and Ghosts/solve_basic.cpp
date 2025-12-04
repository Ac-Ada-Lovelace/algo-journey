#include <iostream>
using namespace std;

/**
 * 巨人与鬼问题 - 基础版本
 *
 * 问题：n个巨人和n个鬼排成一圈，要求交替排列
 * 解法：直接输出 G g G g ... G g
 * 时间复杂度：O(n)
 */

int main() {
    int n;
    cin >> n;

    // 输出交替序列
    for (int i = 0; i < n; i++) {
        cout << "G g";
        if (i < n - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
