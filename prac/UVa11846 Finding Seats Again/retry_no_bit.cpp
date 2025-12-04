#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const int K = 26;

int n, k;
char cinema[N][N];
int team_info[K][3]; // [x, y, size] 每个小组的信息

// 每个小组的所有可行方案
// way[team_id][plan_id] = {start_row, end_row, start_col, end_col}
int way[K][100][4];
int way_num[K]; // 每个小组的可行方案数

int search_order[K]; // 搜索顺序
int ans[K];          // 每个小组选择的方案编号
bool vis[K];

void init() {
    memset(vis, false, sizeof(vis));
    memset(way_num, 0, sizeof(way_num));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cinema[i][j] = '.';
        }
    }
}

// 预处理：为每个小组生成所有可行的放置方案
void preprocess() {
    for (int i = 0; i < k; i++) {
        int leader_x = team_info[i][0];
        int leader_y = team_info[i][1];
        int size = team_info[i][2];

        // 枚举矩形的长和宽
        for (int len = 1; len <= size; len++) {
            if (size % len == 0 && len <= n) {
                int wid = size / len;
                if (wid > n)
                    continue;

                // 枚举起始行，确保包含领导者
                for (int start_row = max(0, leader_x - len + 1);
                     start_row <= min(leader_x, n - len); start_row++) {
                    int end_row = start_row + len - 1;

                    // 枚举起始列，确保包含领导者
                    for (int start_col = max(0, leader_y - wid + 1);
                         start_col <= min(leader_y, n - wid); start_col++) {
                        int end_col = start_col + wid - 1;

                        // 检查这个方案是否覆盖了其他领导者
                        bool ok = true;
                        for (int other = 0; other < k; other++) {
                            if (other != i) {
                                int ox = team_info[other][0];
                                int oy = team_info[other][1];
                                // 如果其他领导者在这个矩形内
                                if (ox >= start_row && ox <= end_row &&
                                    oy >= start_col && oy <= end_col) {
                                    ok = false;
                                    break;
                                }
                            }
                        }

                        if (ok) {
                            way[i][way_num[i]][0] = start_row;
                            way[i][way_num[i]][1] = end_row;
                            way[i][way_num[i]][2] = start_col;
                            way[i][way_num[i]][3] = end_col;
                            way_num[i]++;
                        }
                    }
                }
            }
        }
    }
}

// 检查一个方案是否与当前已放置的矩形冲突
bool check_conflict(int team_id, int plan_id) {
    int sr = way[team_id][plan_id][0];
    int er = way[team_id][plan_id][1];
    int sc = way[team_id][plan_id][2];
    int ec = way[team_id][plan_id][3];

    for (int i = sr; i <= er; i++) {
        for (int j = sc; j <= ec; j++) {
            if (cinema[i][j] != '.' && !isdigit(cinema[i][j])) {
                return true; // 有冲突
            }
        }
    }
    return false; // 无冲突
}

// 放置一个方案
void place(int team_id, int plan_id) {
    int sr = way[team_id][plan_id][0];
    int er = way[team_id][plan_id][1];
    int sc = way[team_id][plan_id][2];
    int ec = way[team_id][plan_id][3];
    char letter = 'A' + team_id;

    for (int i = sr; i <= er; i++) {
        for (int j = sc; j <= ec; j++) {
            cinema[i][j] = letter;
        }
    }
}

// 撤销一个方案
void undo(int team_id, int plan_id) {
    int sr = way[team_id][plan_id][0];
    int er = way[team_id][plan_id][1];
    int sc = way[team_id][plan_id][2];
    int ec = way[team_id][plan_id][3];
    int leader_x = team_info[team_id][0];
    int leader_y = team_info[team_id][1];

    for (int i = sr; i <= er; i++) {
        for (int j = sc; j <= ec; j++) {
            cinema[i][j] = '.';
        }
    }
    cinema[leader_x][leader_y] = team_info[team_id][2] + '0';
}

bool dfs(int depth) {
    if (depth == k) {
        return true;
    }

    int team_id = search_order[depth];

    // 尝试这个小组的每一个可行方案
    for (int plan = 0; plan < way_num[team_id]; plan++) {
        if (!check_conflict(team_id, plan)) {
            place(team_id, plan);
            ans[team_id] = plan;

            if (dfs(depth + 1)) {
                return true;
            }

            undo(team_id, plan);
        }
    }

    return false;
}

void print_answer() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << cinema[i][j];
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> k) {
        if (n == 0)
            break;

        init();

        int t = 0;
        string s;
        for (int i = 0; i < n; i++) {
            cin >> s;
            for (int j = 0; j < n; j++) {
                if (s[j] != '.') {
                    team_info[t][0] = i;
                    team_info[t][1] = j;
                    team_info[t][2] = s[j] - '0';
                    cinema[i][j] = s[j];
                    t++;
                } else {
                    cinema[i][j] = '.';
                }
            }
        }

        // 预处理所有可行方案
        preprocess();

        // 贪心确定搜索顺序：方案数少的先搜索
        for (int i = 0; i < k; i++) {
            int min_ways = 100;
            int best_team = -1;
            for (int j = 0; j < k; j++) {
                if (!vis[j] && way_num[j] < min_ways) {
                    min_ways = way_num[j];
                    best_team = j;
                }
            }
            search_order[i] = best_team;
            vis[best_team] = true;
        }

        // 开始搜索
        dfs(0);

        // 输出结果
        print_answer();
    }

    return 0;
}
