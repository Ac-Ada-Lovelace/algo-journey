// https://onlinejudge.org/index.php?/option=com_onlinejudge&Itemid=8&category=838&page=show_problem&problem=4474
#include <bits/stdc++.h>
#include <sstream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }
        map<int, map<int, int>> road;
        int n, m;
        stringstream ss(line);
        ss>> n >> m;
        for (int i = 0; i < m; i++) {
            int x, y, d;
            cin >> x >> y >> d;
            if (road.count(x) && road[x].count(y)) {
                road[x][y] = min(road[x][y], d);
            } else {
                road[x][y] = d;
            }
            if (x == y) {
                break;
            }
        }

        map<int, pair<int, int>> visited; // node -> {cost, prev}
        queue<int> q;

        for (auto next : road[1]) {
            if (visited.count(next.first) == 0 || visited[next.first].first > 0 + next.second) {
                visited[next.first] = {next.second, 1};
                q.push(next.first);
            }
        }
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            if(curr == n){
                continue;
            }
            
            for(auto nxt : road[curr]){
                if(visited.count(nxt.first) == 0 || visited[nxt.first].first > visited[curr].first + nxt.second){
                    visited[nxt.first] = {visited[curr].first + nxt.second, curr};
                    q.push(nxt.first);
                }
            }
        }

        vector<int> path;
        int prv= n;
        while(true){
            path.push_back(prv);
            if(prv == 1){
                break;
            }
            prv = visited[prv].second;


        }
        int flag = 0;
        for(int i = path.size(); i >=0; i --){
            if(!flag){
                cout << " ";
            }
            cout << path[i];
            flag = 1;
        }
    }
}
