#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pos;
int get_cmd_id(const string& cmd) {
    if (cmd == "EX")
        return 1;
    if (cmd == "DR")
        return 2;
    if (cmd == "DC")
        return 3;
    if (cmd == "IR")
        return 4;
    if (cmd == "IC")
        return 5;
    if (cmd == "CC")
        return 6;
    return -1;
}
// key means raw pos, value means current pos
typedef map<pos, pos> raw_to_now;
typedef map<pos, pos> now_to_raw;
int exchange(raw_to_now& rtn, now_to_raw& ntr, const vector<int>& args) {
    pos p1 = {args[0] - 1, args[1] - 1};
    pos p2 = {args[2] - 1, args[3] - 1};
    auto r_p1 = ntr[p1];
    auto r_p2 = ntr[p2];
    rtn[r_p1] = p2;
    rtn[r_p2] = p1;
    ntr[p1] = r_p2;
    ntr[p2] = r_p1;
    return 0;
}

void clear_by_col(raw_to_now& rtn, now_to_raw& ntr, int col, int row_count) {
    for (int r = 0; r < row_count; r++) {
        pos p = {r, col};
        auto r_p = ntr[p];
        rtn.erase(r_p);
        ntr.erase(p);
    }
    for (int r = 0;; r++) {
        pos p = {0, r};
        if (ntr.find(p) == ntr.end())
            break;
        for (int c = 0; c < row_count; c++) {
            pos cur_p = {c, r};
            auto r_p = ntr[cur_p];
            pos new_p = {c, r - 1};
            rtn[r_p] = new_p;
            ntr[new_p] = r_p;
            ntr.erase(cur_p);
        }
    }
}

void clear_by_row(raw_to_now& rtn, now_to_raw& ntr, int row, int col_count) {
    for (int c = 0; c < col_count; c++) {
        pos p = {row, c};
        auto r_p = ntr[p];
        rtn.erase(r_p);
        ntr.erase(p);
    }
    for (int r = row + 1;; r++) {
        pos p = {r, 0};
        if (ntr.find(p) == ntr.end())
            break;
        for (int c = 0; c < col_count; c++) {
            pos cur_p = {r, c};
            auto r_p = ntr[cur_p];
            pos new_p = {r - 1, c};
            rtn[r_p] = new_p;
            ntr[new_p] = r_p;
            ntr.erase(cur_p);
        }
    }
}

void delete_row(raw_to_now& rtn, now_to_raw& ntr, const vector<int>& args, int args_count,
                int col_count) {
    vector<int> deleted_row;
    while (args_count--) {
        deleted_row.push_back(args[args_count]);
    }
    for (auto r : deleted_row) {}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c;
    while (cin >> r >> c && (r && c)) {
        raw_to_now rtn;
        now_to_raw ntr;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                rtn[{i, j}] = {i, j};
                ntr[{i, j}] = {i, j};
            }
        }
        int n = 0;
        cin >> n;
        string cmd;
        vector<int> args(10);
        while (n--) {
            args.clear();
            cin >> cmd;
            switch (get_cmd_id(cmd)) {
                case 1: {
                    for (int i = 0; i < 4; i++) {
                        cin >> args[i];
                    }
                    exchange(rtn, ntr, args);
                    break;
                }
                case 2: {
                    // DELETE ROW
                    string args_s;
                    if (getline(cin, args_s)) {
                        std::istringstream iss(args_s);
                        int count = 0;
                        while (iss >> count) {
                            args[count++] = count;
                        }
                        delete_row(rtn, ntr, args, count, c);
                    }
                }
            }
        }
    }
}
