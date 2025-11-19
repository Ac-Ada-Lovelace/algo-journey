#include <bits/stdc++.h>
using namespace std;

// 递归读取一棵子树：返回 true 表示成功读完（即便是空子树）
bool readTree(int pos, map<int, int>& piles) {
    int val;
    if (!(cin >> val)) return false;  // 输入意外终止
    if (val == -1) return true;       // 空子树
    piles[pos] += val;
    readTree(pos - 1, piles);
    readTree(pos + 1, piles);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNo = 1;
    while (true) {
        int rootVal;
        if (!(cin >> rootVal)) break;
        if (rootVal == -1) break;  // 读到 sentinel 结束

        map<int, int> piles;
        piles[0] += rootVal;
        readTree(-1, piles);
        readTree(1, piles);

        cout << "Case " << caseNo++ << ":\n";
        bool first = true;
        for (auto& kv : piles) {
            if (!first) cout << ' ';
            cout << kv.second;
            first = false;
        }
        cout << "\n\n";
    }
    return 0;
}
