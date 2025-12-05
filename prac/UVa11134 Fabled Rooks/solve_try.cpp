// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=2075
// UVa11134 Fabled Rooks
#include <bits/stdc++.h>
using namespace std;

#define MAXN 5000

struct Interval {
    int id, l, r;
    bool operator<(const Interval& other) const {
        return r < other.r;
    }
};

int row[MAXN + 1], col[MAXN + 1];
int n;

vector<Interval> row_limit, col_limit;
int pos[MAXN + 1][2];
int row_placed[MAXN + 1];

int col_placed[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int count;
    while (cin >> count) {
        if (count == 0)
            break;

        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(pos, 0, sizeof(pos));
        memset(row_placed, 0, sizeof(row_placed));
        memset(col_placed, 0, sizeof(col_placed));
        row_limit.clear();
        col_limit.clear();
        n = count;
        int xli, yli, xri, yri;

        for (int i = 1; i <= count; i++) {
            cin >> xli >> yli >> xri >> yri;
            row_limit.push_back({i, xli, xri});
            col_limit.push_back({i, yli, yri});
        }

        sort(row_limit.begin(), row_limit.end());
        sort(col_limit.begin(), col_limit.end());

        bool possible = true;

        // 处理行分配
        for (int i = 0; i < n; i++) {
            int id = row_limit[i].id;
            int l = row_limit[i].l;
            int r = row_limit[i].r;
            bool found = false;
            for (int j = l; j <= r; j++) {
                if (!row[j]) {
                    row[j] = 1;
                    pos[id][0] = j;
                    found = true;
                    break;
                }
            }
            if (!found) {
                possible = false;
                break;
            }
        }

        // 处理列分配
        if (possible) {
            for (int i = 0; i < n; i++) {
                int id = col_limit[i].id;
                int l = col_limit[i].l;
                int r = col_limit[i].r;
                bool found = false;
                for (int j = l; j <= r; j++) {
                    if (!col[j]) {
                        col[j] = 1;
                        pos[id][1] = j;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    possible = false;
                    break;
                }
            }
        }

        if (!possible) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        for (int i = 1; i <= n; i++) {
            cout << pos[i][0] << " " << pos[i][1] << endl;
        }
    }
}
