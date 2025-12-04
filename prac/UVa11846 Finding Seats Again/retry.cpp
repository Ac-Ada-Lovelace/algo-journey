
#include <bits/stdc++.h>
using namespace std;

array<array<char, 21>, 21>
    cinema; // . means empty, A-Z means occupied by team, 1-9 means team size
array<int, 26> team_size;
array<array<int, 2>, 26> team_pos;
int cinema_size;
int team_num;
array<vector<array<int, 4>>, 9> all_possible;

void pre() {
    for (int size = 1; size <= 9; size++) {
        for (int psb_len = 1; psb_len <= size; psb_len++) {
            if (size % psb_len == 0) {
                int psb_wid = size / psb_len;
                // x_offset, y_offset means current left upper offset from
                // leader. ! assert leader pos as (0,0)
                for (int x_offset = 0; x_offset < psb_len; x_offset++) {
                    for (int y_offset = 0; y_offset < psb_wid; y_offset++) {
                        int lux = -x_offset;
                        int luy = -y_offset;
                        int rdx = psb_len - x_offset - 1;
                        int rdy = psb_wid - y_offset - 1;
                        all_possible[size - 1].push_back({lux, luy, rdx, rdy});
                    }
                }
            }
        }
    }
}

bool is_ok(char tieam_id, array<int, 4> offset) {
    int leader_x = team_pos[tieam_id - 'A'][0];
    int leader_y = team_pos[tieam_id - 'A'][1];
    int lux = leader_x + offset[0];
    int luy = leader_y + offset[1];
    int rdx = leader_x + offset[2];
    int rdy = leader_y + offset[3];

    for (int i = lux; i <= rdx; i++) {
        for (int j = luy; j <= rdy; j++) {
            // 边界检查
            if (i < 1 || i > cinema_size || j < 1 || j > cinema_size) {
                return false;
            }

            if (i == leader_x && j == leader_y)
                continue;

            if (cinema[i][j] != '.') {
                return false;
            }
        }
    }

    return true;
}

bool draw(char tieam_id, array<int, 4> offset) {
    int leader_x = team_pos[tieam_id - 'A'][0];
    int leader_y = team_pos[tieam_id - 'A'][1];
    int lux = leader_x + offset[0];
    int luy = leader_y + offset[1];
    int rdx = leader_x + offset[2];
    int rdy = leader_y + offset[3];

    for (int i = lux; i <= rdx; i++) {
        for (int j = luy; j <= rdy; j++) {
            cinema[i][j] = tieam_id;
        }
    }

    return true;
}

bool draw_back(char team_id, array<int, 4> offset) {
    int leader_x = team_pos[team_id - 'A'][0];
    int leader_y = team_pos[team_id - 'A'][1];
    int lux = leader_x + offset[0];
    int luy = leader_y + offset[1];
    int rdx = leader_x + offset[2];
    int rdy = leader_y + offset[3];

    for (int i = lux; i <= rdx; i++) {
        for (int j = luy; j <= rdy; j++) {
            cinema[i][j] = '.';
        }
    }
    cinema[leader_x][leader_y] = team_size[team_id - 'A'] + '0';

    return true;
}

int dfs(int last_t) {
    if (last_t == team_num)
        return 1;

    vector<array<int, 4>> candidates = all_possible[team_size[last_t] - 1];
    for (auto cdt : candidates) {
        if (is_ok(last_t + 'A', cdt)) {
            draw(last_t + 'A', cdt);
            if (dfs(last_t + 1))
                return 1;
            draw_back(last_t + 'A', cdt);
        }
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    pre();

    while (true) {
        getline(cin, line);
        if (line == "0 0") {
            break;
        }
        int curr_t = 0;

        stringstream ss(line);
        ss >> cinema_size;
        ss >> team_num;
        for (int i = 0; i < cinema_size; i++) {
            getline(cin, line);
            for (int j = 0; j < cinema_size; j++) {
                if (line[j] == '.') {
                    cinema[i + 1][j + 1] = '.';
                } else {
                    cinema[i + 1][j + 1] = line[j];
                    team_pos[curr_t] = {i + 1, j + 1};
                    team_size[curr_t] = line[j] - '0';
                    curr_t++;
                }
            }
        }
        dfs(0);

        for (int i = 1; i <= cinema_size; i++) {
            for (int j = 1; j <= cinema_size; j++) {
                cout << cinema[i][j];
            }
            cout << "\n";
        }
    }
}
