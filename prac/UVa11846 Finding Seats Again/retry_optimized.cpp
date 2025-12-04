#include <bits/stdc++.h>
using namespace std;

char cinema[21][21];
int team_size[26];
array<int, 2> team_pos[26];
int cinema_size;
int team_num;
int order[26];  // 搜索顺序

// 获取某个大小的所有可能矩形维度
vector<pair<int, int>> get_dimensions(int size) {
    vector<pair<int, int>> dims;
    for (int len = 1; len <= size; len++) {
        if (size % len == 0) {
            int wid = size / len;
            dims.push_back({len, wid});
            if (len != wid) {
                dims.push_back({wid, len});
            }
        }
    }
    return dims;
}

// 检查并放置矩形，返回是否成功
bool try_place(int team_idx, int lux, int luy, int rdx, int rdy, char team_id) {
    int leader_x = team_pos[team_idx][0];
    int leader_y = team_pos[team_idx][1];

    // 检查领导者是否在矩形内
    if (leader_x < lux || leader_x > rdx || leader_y < luy || leader_y > rdy) {
        return false;
    }

    // 检查边界和占用情况
    for (int i = lux; i <= rdx; i++) {
        for (int j = luy; j <= rdy; j++) {
            if (i < 1 || i > cinema_size || j < 1 || j > cinema_size) {
                return false;
            }
            // 只允许空位或数字（领导者位置）
            if (cinema[i][j] != '.' && !isdigit(cinema[i][j])) {
                return false;
            }
        }
    }

    // 放置
    for (int i = lux; i <= rdx; i++) {
        for (int j = luy; j <= rdy; j++) {
            cinema[i][j] = team_id;
        }
    }

    return true;
}

// 撤销放置
void undo_place(int team_idx, int lux, int luy, int rdx, int rdy) {
    int leader_x = team_pos[team_idx][0];
    int leader_y = team_pos[team_idx][1];

    for (int i = lux; i <= rdx; i++) {
        for (int j = luy; j <= rdy; j++) {
            cinema[i][j] = '.';
        }
    }
    cinema[leader_x][leader_y] = team_size[team_idx] + '0';
}

bool dfs(int depth) {
    if (depth == team_num) {
        return true;
    }

    int team_idx = order[depth];
    char team_id = 'A' + team_idx;
    int size = team_size[team_idx];
    int leader_x = team_pos[team_idx][0];
    int leader_y = team_pos[team_idx][1];

    // 获取所有可能的矩形维度
    auto dims = get_dimensions(size);

    // 对每种维度，枚举所有可能的左上角位置
    for (auto [len, wid] : dims) {
        // 枚举左上角位置
        // 为了包含领导者，左上角必须在一定范围内
        int min_lux = max(1, leader_x - len + 1);
        int max_lux = min(cinema_size - len + 1, leader_x);
        int min_luy = max(1, leader_y - wid + 1);
        int max_luy = min(cinema_size - wid + 1, leader_y);

        for (int lux = min_lux; lux <= max_lux; lux++) {
            for (int luy = min_luy; luy <= max_luy; luy++) {
                int rdx = lux + len - 1;
                int rdy = luy + wid - 1;

                if (try_place(team_idx, lux, luy, rdx, rdy, team_id)) {
                    if (dfs(depth + 1)) {
                        return true;
                    }
                    undo_place(team_idx, lux, luy, rdx, rdy);
                }
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;

    while (true) {
        getline(cin, line);
        if (line == "0 0") {
            break;
        }

        stringstream ss(line);
        ss >> cinema_size >> team_num;

        int curr_t = 0;

        // 初始化电影院
        for (int i = 1; i <= cinema_size; i++) {
            for (int j = 1; j <= cinema_size; j++) {
                cinema[i][j] = '.';
            }
        }

        // 读取地图
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

        // 按小组大小降序排序（大的先放，剪枝效果更好）
        for (int i = 0; i < team_num; i++) {
            order[i] = i;
        }
        sort(order, order + team_num, [](int a, int b) {
            return team_size[a] > team_size[b];
        });

        // 开始搜索
        dfs(0);

        // 输出结果
        for (int i = 1; i <= cinema_size; i++) {
            for (int j = 1; j <= cinema_size; j++) {
                cout << cinema[i][j];
            }
            cout << "\n";
        }
    }

    return 0;
}
