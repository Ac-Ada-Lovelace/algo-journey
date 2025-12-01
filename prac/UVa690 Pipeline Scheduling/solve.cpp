#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int TASKS = 10;

int n;
bool forbidden[MAXN]; // forbidden[i] = true 表示间隔 i 会产生冲突
int best_ans;

// 计算禁止的间隔
void compute_forbidden(vector<string>& table) {
    memset(forbidden, false, sizeof(forbidden));

    // 对每个功能单元
    for (int unit = 0; unit < 5; unit++) {
        vector<int> occupied; // 该单元被占用的时刻

        for (int t = 0; t < n; t++) {
            if (table[unit][t] == 'X') {
                occupied.push_back(t);
            }
        }

        // 如果两个任务的启动间隔为 d，它们在时刻 t1 和 t1+d 都需要这个单元
        // 那么 d = t2 - t1（其中 t1, t2 都是该单元被占用的时刻）
        for (int i = 0; i < occupied.size(); i++) {
            for (int j = i + 1; j < occupied.size(); j++) {
                int d = occupied[j] - occupied[i];
                forbidden[d] = true;
            }
        }
    }
}

// DFS搜索最优调度方案
// cnt: 已经调度的任务数
// last_start: 上一个任务的启动时刻
// state: 当前禁止的间隔集合（动态变化）
void dfs(int cnt, int last_start, bitset<512> state) {
    if (cnt == TASKS) {
        // 所有任务都调度完成，最后一个任务在 last_start 启动，需要 n 个周期完成
        best_ans = min(best_ans, last_start + n);
        return;
    }

    // 剪枝：剩余任务即使全部间隔1启动也无法更优
    int remaining = TASKS - cnt;
    if (last_start + remaining - 1 + n >= best_ans) {
        return;
    }

    // 尝试不同的启动间隔
    for (int gap = 1; gap < best_ans; gap++) {
        if (state[gap])
            continue; // 这个间隔会冲突，跳过

        int next_start = last_start + gap;

        // 剪枝：即使后续任务全部间隔1也无法更优
        if (next_start + (remaining - 1) + n >= best_ans) {
            break;
        }

        // 更新状态：state右移gap位（时间推进），然后与原始禁止集合合并
        bitset<512> next_state = (state >> gap);
        for (int i = 1; i < n; i++) {
            if (forbidden[i]) {
                next_state[i] = true;
            }
        }

        dfs(cnt + 1, next_start, next_state);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n) {
        vector<string> table(5);
        for (int i = 0; i < 5; i++) {
            cin >> table[i];
        }

        // 计算禁止的间隔
        compute_forbidden(table);

        // 初始化初始状态
        bitset<512> initial_state;
        for (int i = 1; i < n; i++) {
            if (forbidden[i]) {
                initial_state[i] = true;
            }
        }

        // 搜索最优方案
        best_ans = INT_MAX;
        dfs(1, 0, initial_state); // 第一个任务从时刻0开始

        cout << best_ans << "\n";
    }

    return 0;
}
