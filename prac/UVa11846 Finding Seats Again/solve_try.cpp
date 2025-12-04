// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=2946
// UVa11846 Finding Seats Again
#include <bits/stdc++.h>
using namespace std;
#define MAX_N 21
#define MAX_K 27

int C[MAX_N][MAX_N];
map<char, array<int, 2>> team_pos;
map<char, int> team_size;
int n, k;
map<int, vector<array<int, 4>>> kf;
void pre() {
    for (int i = 1; i <= 9; i++) {
        for (int pl = 1; pl <= i; pl++) {
            if (i % pl == 0) {
                int pw = i / pl;
                for (int i_a = 0; i_a < pl; i_a++) {
                    for (int j_a = 0; j_a < pw; j_a++) {
                        int lux, luy, rdx, rdy;
                        lux = -i_a;
                        luy = -j_a;
                        rdx = pl - i_a - 1;
                        rdy = pw - j_a - 1;
                        kf[i].push_back({lux, luy, rdx, rdy});
                    }
                }
            }
        }
    }
}

bool is_ok(int x, int y, array<int, 4> offset) {
    int lux = x + offset[0];
    int luy = y + offset[1];
    int rdx = x + offset[2];
    int rdy = y + offset[3];
    bool ok = true;

    for (int i = lux; i <= rdx; i++) {
        for (int j = luy; j <= rdy; j++) {
            if (i < 1 || i > n || j < 1 || j > n || C[i][j] != 0) {
                ok = false;
            }
        }
    }
    return ok;
}
bool draw(char t,int x, int y, array<int, 4> offset) {
    int lux = x + offset[0];
    int luy = y + offset[1];
    int rdx = x + offset[2];
    int rdy = y + offset[3];
    bool ok = true;

    for (int i = lux; i <= rdx; i++) {
        for (int j = luy; j <= rdy; j++) {
            C[i][j] = -1;
        }
    }
    return ok;
}
bool draw_back(char team_id, array<int, 4> offset) {}

int dfs(int cur_t) {
    if (cur_t == k) {
        return true;
    }

    auto possible = kf[team_size['A' + cur_t]];
    int x = team_pos['A' + cur_t][0];
    int y = team_pos['A' + cur_t][1];

    for (auto f : possible) {
        if (is_ok(x, y, f)) {}
    }
}

void disp() {
    for (auto kv : kf) {
        auto [k, v] = kv;
        cout << k << endl;
        for (auto m : v) {
            for (auto x : m) {
                cout << x << " ";
            }
            cout << endl;
        }
        cout << "---------" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("output.txt", "w", stdout);
    pre();
    disp();

    return 0;
    string line;
    while (true) {
        getline(cin, line);
        if (line == "0 0") {
            break;
        }
        stringstream ss(line);
        ss >> n >> k;
        char s;
        char curr_t = 'A';
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> s;
                if (isdigit(s)) {
                    C[i][j] = s - '0';
                    team_pos[curr_t] = {i, j};
                    team_size[curr_t] = C[i][j];
                    curr_t++;

                } else {
                    C[i][j] = 0;
                }
            }
        }
    }
}
