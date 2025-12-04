// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=108&page=show_problem&problem=144
// UVa208 Firetruck
#include <bits/stdc++.h>
using namespace std;

void dfs(int target, int u, vector<vector<int>>& routes, vector<int>& path,
         array<vector<int>, 21>& adj, array<int, 21>& vis,
         array<int, 21>& canReach, int& cnt) {
    if (u == target) {
        routes.push_back(path);
        ++cnt;
        return;
    }
    for (int v : adj[u]) {
        if (vis[v])
            continue;
        if (!canReach[v])
            continue; // 剪枝：从 v 到 target 不可达则跳过
        vis[v] = 1;
        path.push_back(v);
        dfs(target, v, routes, path, adj, vis, canReach, cnt);
        path.pop_back();
        vis[v] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    int case_num = 1;
    while (true) {
        if (!getline(cin, line))
            break;
        if (line.empty())
            continue;
        stringstream ss(line);
        int target;
        ss >> target;

        array<vector<int>, 21> adj{};
        while (getline(cin, line)) {
            if (line == "0 0")
                break;
            stringstream ls(line);
            int a, b;
            ls >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        for (int i = 1; i <= 20; ++i)
            sort(adj[i].begin(), adj[i].end());

        // 预先判断能否到达 target，避免无谓搜索
        array<int, 21> canReach{};
        queue<int> q;
        canReach[target] = 1;
        q.push(target);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!canReach[v]) {
                    canReach[v] = 1;
                    q.push(v);
                }
            }
        }

        vector<vector<int>> routes;
        vector<int> path{1};
        array<int, 21> vis{};
        vis[1] = 1;
        int cnt = 0;
        if (canReach[1]) {
            dfs(target, 1, routes, path, adj, vis, canReach, cnt);
        }

        cout << "CASE " << case_num << ":\n";
        for (auto& r : routes) {
            for (size_t i = 0; i < r.size(); ++i) {
                if (i)
                    cout << " ";
                cout << r[i];
            }
            cout << "\n";
        }
        cout << "There are " << cnt
             << " routes from the firestation to streetcorner " << target
             << ".\n";
        ++case_num;
        if (!cin.eof())
            cout << "\n";
    }
    return 0;
}
