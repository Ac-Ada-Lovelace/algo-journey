#include <bits/stdc++.h>
using namespace std;
int min(vector<int> vec) {
    int res = INT_MAX;
    for (auto v : vec) {
        res = min(res, v);
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        map<int, map<int, vector<int>>> mp;
        for (int i = 0; i < m; i++) {
            int ai, bi, ci;
            cin >> ai >> bi >> ci;
            mp[ai][bi].push_back(ci);
            mp[bi][ai].push_back(ci);
        }

        map<int, int> dists{};

        queue<int> q;
        q.push(n);
        dists[n] = 0;
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            if (node == 1) {
                continue;
            }

            for (auto w : mp[node]) {
                if (dists.count(w.first) == 0 || dists[w.first] > dists[node] + 1) {
                    dists[w.first] = dists[node] + 1;
                    q.push(w.first);
                }
            }
        }
        int len = dists[1];
        cout << len << "\n";
        if (len <= 0) {
            cout << "\n";
            continue;
        }

        vector<int> ans{};
        int curr_node = 1;
        int nxt_colr = -1;
        int nxt_node = -1;
        while (curr_node != n) {
            for (auto nn : mp[curr_node]) {
                if (dists[nn.first] == dists[curr_node] - 1) {
                    if (nxt_colr == -1 || min(nn.second) < nxt_colr) {
                        nxt_colr = min(nn.second);
                        nxt_node = nn.first;
                    }
                }
            }
            ans.push_back(nxt_colr);
            curr_node = nxt_node;
        }

        int flag = 0;
        for (auto nn : ans) {
            if (flag) {
                cout << " ";
            }
            cout << nn;
            flag = 1;
        }
    }
}
