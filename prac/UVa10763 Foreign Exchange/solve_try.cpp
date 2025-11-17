#include <bits/stdc++.h>
using namespace std;
typedef struct {
    int src;
    int dest;
} exchange_willing;
bool operator<(const exchange_willing& a, const exchange_willing& b) {
    if (a.src == b.src) {
        return a.dest < b.dest;
    }
    return a.src < b.src;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int student_num;
    while (cin >> student_num) {
        if (student_num == 0) {
            break;
        }

        map<exchange_willing, int> exchange_map;
        while (student_num--) {
            int src, dest;
            cin >> src >> dest;
            exchange_willing ex_will = {(src < dest) ? src : dest, (src < dest) ? dest : src};
            if (exchange_map.find(ex_will) != exchange_map.end()) {
                if (src < dest) {
                    exchange_map[ex_will] += 1;
                } else {
                    exchange_map[ex_will] += -1;
                }
            } else {
                if (src < dest) {
                    exchange_map[ex_will] = 1;
                } else {
                    exchange_map[ex_will] = -1;
                }
            }
        }

        int flag = 0;
        for (auto ex_w : exchange_map) {
            if (ex_w.second != 0) {
                cout << "NO\n";
                flag = 1;
                break;
            }
        }
        if (!flag)
            cout << "YES\n";
    }
}
