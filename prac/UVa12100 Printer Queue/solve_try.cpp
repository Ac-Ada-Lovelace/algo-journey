#include <bits/stdc++.h>
#include <queue>
using namespace std;

typedef struct {
    int priority;
    bool is_mine;
} task;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    while (cases--) {
        int n, m;
        cin >> n >> m;
        queue<task> ts;
        priority_queue<int> pq;
        int time = 0;
        for (int i = 0; i < n; i++) {
            int p;
            cin >> p;
            ts.push({p, (i == m)});
            pq.push(p);
        }

        while (true) {
            auto t = ts.front();
            ts.pop();
            if (t.priority == pq.top()) {
                pq.pop();
                time++;
            } else {
                ts.push(t);
                continue;
            }
            if (t.is_mine) {
                cout << time << "\n";
                break;
            }
        }
    }
}
