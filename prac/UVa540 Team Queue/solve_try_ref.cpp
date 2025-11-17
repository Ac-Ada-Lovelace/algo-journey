#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    int scenario = 1;
    while (cin >> t && t) {
        vector<int> memberTeam(1000000, -1);
        for (int team = 0; team < t; ++team) {
            int cnt;
            cin >> cnt;
            while (cnt--) {
                int member;
                cin >> member;
                memberTeam[member] = team;
            }
        }

        cout << "Scenario #" << scenario++ << "\n";

        vector<queue<int>> teamQueues(t);
        vector<char> inQueue(t, false);
        queue<int> order;

        string cmd;
        while (cin >> cmd && cmd != "STOP") {
            if (cmd == "ENQUEUE") {
                int member;
                cin >> member;
                int team = memberTeam[member];
                if (!inQueue[team]) {
                    order.push(team);
                    inQueue[team] = true;
                }
                teamQueues[team].push(member);
            } else if (cmd == "DEQUEUE") {
                int team = order.front();
                int member = teamQueues[team].front();
                teamQueues[team].pop();
                cout << member << "\n";
                if (teamQueues[team].empty()) {
                    order.pop();
                    inQueue[team] = false;
                }
            }
        }
        cout << "\n";
    }
    return 0;
}
