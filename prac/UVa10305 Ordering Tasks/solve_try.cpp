#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (true) {
        cin >> n >> m;
        if (!n && !m) {
            break;
        }

        map<int, vector<int>> adj;
        map<int, int> indeg;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            
            
            indeg[b] += 1;
        }

        queue<int> tq;
        for (int i = 1; i <= n; i++) {
            if (indeg[i] == 0) {
                tq.push(i);
            }
        }

        int flag = 0;
        while (!tq.empty()) {
            auto t = tq.front();
            tq.pop();
            if (flag) {
                cout << " ";
            }
            cout << t;
            flag = 1;
            for (auto task : adj[t]) {
                indeg[task] -= 1;
                if (indeg[task] == 0) {
                    tq.push(task);
                }
            }
        }
        cout << endl;
    }
}
