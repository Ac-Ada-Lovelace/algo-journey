// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=631
// UVa690 Pipeline Scheduling
#include <bits/stdc++.h>
using namespace std;

// Maximum latency we care about. With n < 20 and 10 tasks, 512 is plenty.
const int BIT = 512;
const int TASKS = 10;

int n;
bitset<BIT> collision_vector;
int best_time;

void dfs(int scheduled, int last_start, const bitset<BIT>& state) {
  if (scheduled == TASKS) {
    best_time = min(best_time, last_start + n);
    return;
  }

    int remaining = TASKS - scheduled;
    int max_l = best_time - n - last_start - (remaining - 1) - 1;
    if (max_l < 1)
        return;

    for (int l = 1; l <= max_l; ++l) {
    if (state.test(l))
      continue;
    int next_start = last_start + l;
    int lower_bound_finish = next_start + (remaining - 1) + n;
    if (lower_bound_finish >= best_time)
      continue;
    bitset<BIT> next_state = (state >> l) | collision_vector;
    dfs(scheduled + 1, next_start, next_state);
  }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n) {
        if (n == 0)
            break;

        collision_vector.reset();
        for (int unit = 0; unit < 5; ++unit) {
            string row;
            cin >> row;
            vector<int> pos;
            for (int t = 0; t < n; ++t) {
                if (row[t] == 'X')
                    pos.push_back(t);
            }
            for (size_t i = 0; i < pos.size(); ++i) {
                for (size_t j = i + 1; j < pos.size(); ++j) {
                    int d = pos[j] - pos[i];
                    collision_vector.set(d);
                }
            }
        }

        best_time = INT_MAX;
        dfs(1, 0, collision_vector);
        cout << best_time << "\n";
    }
    return 0;
}
