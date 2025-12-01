#include <bits/stdc++.h>
using namespace std;

struct schedule_case {
    array<vector<int>, 5> tasks{};
    array<vector<int>, 5> timeline{};

    array<int, 5> min_start{};
    int finish_time = 0;
    int last_start = 0;
    int n;

    void build_case(array<string, 5>& rows, int task_len) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rows[i][j] == 'X') {
                    tasks[i].push_back(j);
                }
            }
        }
        n = task_len;
    }

    void dfs(int curr_t) {
        if (curr_t == 10) {
            finish_time = min(finish_time, last_start + n);
        }
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        int n;
        cin >> n;
        cin.ignore();
    }
}
