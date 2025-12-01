#include <bits/stdc++.h>
using namespace std;

vector<int> C;
int n = 0;
int tot = 0;

void dfs(int cur) {
    if (cur == n) {
        tot++;
        return;
    }
    for (int i = 0; i < n; i++) {
        C[cur] = i; // 当前行放到第 i 列
        bool ok = true;
        for (int j = 0; j < cur; j++) {
            if (C[j] == C[cur] || abs(C[j] - C[cur]) == abs(j - cur)) {
                ok = false;
                break;
            }
        }
        if (ok)
            dfs(cur + 1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    C.assign(n, 0);
    tot = 0;
    dfs(0);
    cout << tot << "\n";
}
