#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T))
        return 0;
    while (T--) {
        int n;
        cin >> n;

        array<int, 26> indeg{}, outdeg{};
        array<vector<int>, 26> undirected;
        for (int i = 0; i < 26; i++)
            undirected[i].clear();

        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            int u = s.front() - 'a';
            int v = s.back() - 'a';
            outdeg[u]++;
            indeg[v]++;
            undirected[u].push_back(v);
            undirected[v].push_back(u);
        }

        bool connected = true;
        vector<int> visited(26, 0);
        int start_node = -1;
        for (int i = 0; i < 26; i++) {
            if (indeg[i] + outdeg[i] > 0) {
                start_node = i;
                break;
            }
        }
        if (start_node != -1) {
            queue<int> q;
            q.push(start_node);
            visited[start_node] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : undirected[u]) {
                    if (!visited[v]) {
                        visited[v] = 1;
                        q.push(v);
                    }
                }
            }
            for (int i = 0; i < 26; i++) {
                if ((indeg[i] + outdeg[i] > 0) && !visited[i]) {
                    connected = false;
                    break;
                }
            }
        }

        int start_nodes = 0, end_nodes = 0;
        bool degree_ok = true;
        for (int i = 0; i < 26; i++) {
            int diff = outdeg[i] - indeg[i];
            if (diff == 1) {
                start_nodes++;
            } else if (diff == -1) {
                end_nodes++;
            } else if (diff != 0) {
                degree_ok = false;
                break;
            }
        }
        if (!((start_nodes == 0 && end_nodes == 0) || (start_nodes == 1 && end_nodes == 1))) {
            degree_ok = false;
        }

        if (degree_ok && connected) {
            cout << "Ordering is possible." << '\n';
        } else {
            cout << "The door cannot be opened." << '\n';
        }
    }

    return 0;
}
