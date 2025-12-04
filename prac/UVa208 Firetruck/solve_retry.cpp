#include <bits/stdc++.h>
using namespace std;

#define MAXN 21

array<vector<int>, MAXN> adj; // adj[r][c] r < c. upper triangular matrix
array<bool, MAXN> visited;
int n;

vector<int> path;
vector<vector<int>> all_paths;

int dfs(int cur, int target) {
    if (cur == target) {
        all_paths.push_back(path);
        return 1;
    }

    for (auto pnxt : adj[cur]) {
        if (!visited[pnxt]) {
            visited[pnxt] = true;
            path.push_back(pnxt);
            dfs(pnxt, target);
            path.pop_back();
            visited[pnxt] = false;
        }
    }
    return 0;
}

int is_reachable(int start, int target) {
    queue<int> q;
    q.push(start);
    array<bool, MAXN> _visited;
    _visited.fill(false);
    _visited[start] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (cur == target) {
            return 1;
        }
        for (auto nxt : adj[cur]) {
            if (!_visited[nxt]) {
                _visited[nxt] = true;
                q.push(nxt);
            }
        }
    }

    return 0;
}

int case_num = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty())
            break;

        int target;
        target = stoi(line);

        unordered_set<int> nodes;
        while (getline(cin, line) && !line.empty()) {
            stringstream ss(line);
            int u, v;
            ss >> u >> v;
            if (u == 0 && v == 0) {
                break;
            }
            nodes.insert(u);
            nodes.insert(v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        n = nodes.size();

        for (auto& ns : adj) {
            sort(ns.begin(), ns.end());
        }
        bool solvable = is_reachable(1, target);

        if (solvable) {
            visited[1] = true;
            path.push_back(1);
            int res = dfs(1, target);
        }
        sort(all_paths.begin(), all_paths.end());
        cout << "CASE " << case_num << ":" << endl;
        for (auto p : all_paths) {
            for (int i = 0; i < p.size(); i++) {
                if (i)
                    cout << " ";
                cout << p[i];
            }
            cout << endl;
        }

        cout << "There are " << all_paths.size()
             << " routes from the firestation to streetcorner " << target << "."
             << endl;
        case_num++;
        adj.fill(vector<int>());
        path.clear();
        all_paths.clear();
        visited.fill(false);
    }
    cout << endl;
}
