#include <bits/stdc++.h>
#include <cinttypes>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int team_num;
    int case_count = 0;
    while (true) {
        cin >> team_num;
        if (team_num == 0) {
            break;
        }

        // first means member id, second means team id
        map<int, int> member_team_map;
        map<int, queue<int>&> team_queue_ref;
        queue<queue<int>> teams_queue;

        int team_count = 0;

        while (team_num--) {
            int member_num;
            cin >> member_num;
            while (member_num--) {
                int member_id;
                cin >> member_id;
                member_team_map[member_id] = team_count;
            }
            team_count++;
        }
        cout << "Scenario #" << ++case_count << "\n";
        string cmd;
        while (true) {
            cin >> cmd;
            if (cmd == "STOP") {
                break;
            } else if (cmd == "ENQUEUE") {
                int member_id;
                cin >> member_id;
                int team_id = member_team_map[member_id];

                if (team_queue_ref.find(team_id) == team_queue_ref.end()) {
                    // New team, create a new queue for it
                    queue<int> new_team_queue;
                    new_team_queue.push(member_id);
                    teams_queue.push(new_team_queue);
                    team_queue_ref[team_id] = teams_queue.back();
                } else {
                    // Existing team, add member to its queue
                    team_queue_ref[team_id].push(member_id);
                }

            } else if (cmd == "DEQUEUE") {
                if (teams_queue.front().empty()) {
                    teams_queue.pop();

                    auto tq = teams_queue.front();
                    cout << tq.front() << "\n";
                    tq.pop();
                } else {
                    auto tq = teams_queue.front();
                    cout << tq.front() << "\n";
                    tq.pop();
                }
            }
        }
    }
}
