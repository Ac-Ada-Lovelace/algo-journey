// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=110&page=show_problem&problem=1544
// UVa10603 Fill — Dijkstra on discrete state space (arrays, no lambdas)
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int cost;
    int x;
    int y;  // amounts in jug 0 and jug 1; jug 2 is derived
    bool operator<(const Node& other) const { return cost > other.cost; }
};

const int INF = 1e9;

int cap[3];
int target;
vector<vector<int>> distv;
int best_vol;
int best_cost;

void maybe_update_best(int x, int y) {
    int z = cap[2] - x - y;
    int vols[3] = {x, y, z};
    for (int v : vols) {
        if (v > target) continue;
        if (v > best_vol || (v == best_vol && distv[x][y] < best_cost)) {
            best_vol = v;
            best_cost = distv[x][y];
        }
    }
}

void relax(int nx, int ny, int ncost, priority_queue<Node>& pq) {
    if (ncost < distv[nx][ny]) {
        distv[nx][ny] = ncost;
        pq.push({ncost, nx, ny});
    }
}

void pour(int src, int dst, int x, int y, priority_queue<Node>& pq) {
    int amt[3] = {x, y, cap[2] - x - y};
    int flow = min(amt[src], cap[dst] - amt[dst]);
    if (flow == 0) return;
    amt[src] -= flow;
    amt[dst] += flow;
    relax(amt[0], amt[1], distv[x][y] + flow, pq);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        cin >> cap[0] >> cap[1] >> cap[2] >> target;

        distv.assign(cap[0] + 1, vector<int>(cap[1] + 1, INF));
        priority_queue<Node> pq;
        distv[0][0] = 0;
        pq.push({0, 0, 0});

        best_vol = -1;
        best_cost = INF;

        while (!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            if (cur.cost != distv[cur.x][cur.y]) continue;  // stale entry

            maybe_update_best(cur.x, cur.y);
            if (best_vol == target) break;  // exact target reached optimally

            pour(0, 1, cur.x, cur.y, pq);
            pour(0, 2, cur.x, cur.y, pq);
            pour(1, 0, cur.x, cur.y, pq);
            pour(1, 2, cur.x, cur.y, pq);
            pour(2, 0, cur.x, cur.y, pq);
            pour(2, 1, cur.x, cur.y, pq);
        }

        cout << best_cost << " " << best_vol << "\n";
    }
    return 0;
}
