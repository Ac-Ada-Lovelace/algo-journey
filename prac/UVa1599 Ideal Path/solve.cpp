// https://onlinejudge.org/external/15/1599.pdf
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int color;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<Edge>> adj(n + 1);
        adj.reserve(n + 1);
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            adj[a].push_back({b, c});
            adj[b].push_back({a, c});
        }

        vector<int> dist(n + 1, -1);
        queue<int> q;
        dist[n] = 0;
        q.push(n);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto& e : adj[v]) {
                if (dist[e.to] == -1) {
                    dist[e.to] = dist[v] + 1;
                    q.push(e.to);
                }
            }
        }

        int len = dist[1];
        cout << len << "\n";
        if (len <= 0) {
            cout << "\n";
            continue;
        }

        vector<int> answer(len);
        vector<int> curr;
        vector<int> next;
        vector<char> used(n + 1, 0);
        curr.push_back(1);
        used[1] = 1;
        for (int layer = len - 1; layer >= 0; layer--) {
            int best_color = numeric_limits<int>::max();
            for (int v : curr) {
                for (const auto& e : adj[v]) {
                    if (dist[e.to] == dist[v] - 1) {
                        best_color = min(best_color, e.color);
                    }
                }
            }
            answer[len - 1 - layer] = best_color;
            next.clear();
            fill(used.begin(), used.end(), 0);
            for (int v : curr) {
                for (const auto& e : adj[v]) {
                    if (dist[e.to] == dist[v] - 1 && e.color == best_color && !used[e.to]) {
                        used[e.to] = 1;
                        next.push_back(e.to);
                    }
                }
            }
            curr.swap(next);
        }

        for (int i = 0; i < len; i++) {
            if (i) cout << ' ';
            cout << answer[i];
        }
        cout << "\n";
    }
    return 0;
}
