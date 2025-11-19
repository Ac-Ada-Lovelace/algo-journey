// TODO: fuck
#include <bits/stdc++.h>
#include <cstddef>
#include <sstream>
using namespace std;

typedef struct state {
    int pos_r;
    int pos_c;
    string entry_from;
    int dist;
} state;
map<string, pair<int, int>> dir_map = {
    {"N", {-1, 0}}, {"S", {1, 0}}, {"E", {0, 1}}, {"W", {0, -1}}};
map<string, pair<int, int>> turn_map = {
    {"NL", {0, -1}}, {"NF", {-1, 0}}, {"NR", {0, 1}},  {"SL", {0, 1}},
    {"SF", {1, 0}},  {"SR", {0, -1}}, {"EL", {-1, 0}}, {"EF", {0, 1}},
    {"ER", {1, 0}},  {"WL", {1, 0}},  {"WF", {0, -1}}, {"WR", {-1, 0}},
};
map<string, string> entry_map = {
    {"NL", "W"}, {"NF", "N"}, {"NR", "E"}, {"SL", "E"}, {"SF", "S"}, {"SR", "W"},
    {"EL", "N"}, {"EF", "E"}, {"ER", "S"}, {"WL", "S"}, {"WF", "W"}, {"WR", "N"},
};

state calc_next(state curr, string turn) {
    turn = curr.entry_from + turn;

    return state{curr.pos_r + turn_map[turn].first, curr.pos_c + turn_map[turn].second,
                 entry_map[turn], curr.dist + 1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string name;
    while (getline(cin, name)) {
        if (name == "END") {
            break;
        }
        string first_line;
        getline(cin, first_line);
        stringstream ss(first_line);
        int start_r, start_c;
        string face_fwd;
        int goal_r, goal_c;

        ss >> start_r >> start_c >> face_fwd >> goal_r >> goal_c;

        state start_state = state{start_r, start_c, face_fwd, 0};

        string node_line;

        map<pair<int, int>, map<string, vector<string>>> road_rule;
        map<pair<int, int>, int> grid;
        while (getline(cin, node_line)) {
            if (node_line == "0") {
                break;
            }
            if (node_line == "END") {
                break;
            }
            stringstream nss(node_line);
            int node_r, node_c;
            map<string, vector<string>> temp_map;
            nss >> node_r >> node_c;
            grid[pair<int, int>(node_r, node_c)] = 0;
            nss.ignore();
            string token;
            while (getline(nss, token, ' ')) {
                if (token == "*") {
                    break;
                }
                string entry_from = string(1, token[0]);
                for (size_t i = 1; i < token.length(); i++) {
                    temp_map[entry_from].push_back(string(1, token[i]));
                }
            }

            road_rule[{node_r, node_c}] = temp_map;
        }

        queue<state> possible_next;

        vector<string> pns =
            road_rule[pair<int, int>(start_state.pos_r, start_state.pos_c)][start_state.entry_from];

        map<pair<int, int>, pair<int, int>> prev;

        for (auto p : pns) {
            auto n = calc_next(start_state, p);
            possible_next.push(n);
            prev[pair<int, int>(n.pos_r, n.pos_c)] =
                pair<int, int>(start_state.pos_r, start_state.pos_c);
        }

        int flag = 0;
        while (!possible_next.empty()) {
            state curr = possible_next.front();
            possible_next.pop();
            if (curr.pos_r == goal_r && curr.pos_c == goal_c) {
                flag = 1;
                vector<pair<int, int>> full_path;
                pair<int, int> trace = pair<int, int>(curr.pos_r, curr.pos_c);
                while (trace != pair<int, int>(start_state.pos_r, start_state.pos_c)) {
                    full_path.push_back(trace);
                    trace = prev[trace];
                }
                full_path.push_back(trace);
                reverse(full_path.begin(), full_path.end());
                cout << name << endl;
                cout << "  " << endl;
                for (size_t i = 0; i < full_path.size(); i++) {
                    cout << " (" << full_path[i].first << "," << full_path[i].second << ")";
                    if (i != full_path.size() - 1) {
                        if (i % 10 == 9) {
                            cout << endl;
                        }
                    }
                }
                break;
            }

            for (string turn : road_rule[{curr.pos_r, curr.pos_c}][curr.entry_from]) {
                state next_state = calc_next(curr, turn);
                if (grid.find({next_state.pos_r, next_state.pos_c}) != grid.end() &&
                    (grid[{next_state.pos_r, next_state.pos_c}] == 0 ||
                     grid[{next_state.pos_r, next_state.pos_c}] > next_state.dist)) {
                    grid[{next_state.pos_r, next_state.pos_c}] = next_state.dist;
                    prev[pair<int, int>(next_state.pos_r, next_state.pos_c)] =
                        pair<int, int>(curr.pos_r, curr.pos_c);
                    possible_next.push(next_state);
                }
            }
        }
        if (!flag) {
            cout << "No Solution Possible" << endl;
        }
    }
}
