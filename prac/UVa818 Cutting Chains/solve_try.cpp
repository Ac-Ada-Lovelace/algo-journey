// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=759
// UVa818 Cutting Chains
#include <bits/stdc++.h>
#include <cmath>
using namespace std;

array<array<int, 16>, 16> graph;
array<bool, 16> opened;
int n; // 实际的环数量
int min_cuts = 16;
vector<int> best_solution;

bool check() {
    vector<vector<int>> components;

    array<bool, 16> visited{};
    int n_count = 0;
    int open_count = 0;
    for (int i = 1; i <= n; i++) {
        if (opened[i]) {
            open_count++;
            visited[i] = true;
            n_count++;
        }
    }

    queue<int> q;
    while (n_count < n) {
        vector<int> component;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;
                n_count++;
                component.push_back(i);
                break;
            }
        }

        while (!q.empty()) {
            int nn = q.front();
            q.pop();
            for (int j = 1; j <= n; j++) {
                if (graph[nn][j] && !visited[j]) {
                    visited[j] = true;
                    q.push(j);
                    component.push_back(j);
                    n_count++;
                }
            }
        }
        components.push_back(component);
    }

    if (components.size() > open_count + 1)
        return false;

    for (auto& c : components) {
        if (c.size() == 1)
            continue;
        array<int, 16> degree{};
        for (auto nn : c) {
            for (int j = 1; j <= n; j++) {
                if (j != nn && graph[nn][j] && find(c.begin(), c.end(), j) != c.end()) {
                    degree[nn]++;
                    if (degree[nn] > 2)
                        return false;
                }
            }
        }

        int one_nc = 0;
        for (auto i : c) {
            if (degree[i] == 1)
                one_nc++;
        }

        if (one_nc != 2) {
            return false;
        }
    }
    return true;
}

void dfs(int cur_node, int cur_cuts) {
    // 剪枝：如果当前已经超过最优解，直接返回
    if (cur_cuts >= min_cuts) {
        return;
    }

    // 终止条件：遍历完所有环
    if (cur_node > n) {
        if (check()) {
            min_cuts = cur_cuts;
            best_solution.clear();
            for (int i = 1; i <= n; i++) {
                if (opened[i]) {
                    best_solution.push_back(i);
                }
            }
        }
        return;
    }

    // 选择1：打开当前环
    // 保存需要断开的边
    array<bool, 16> to_be_undo{};
    for (int i = 1; i <= n; i++) {
        if (i != cur_node && graph[cur_node][i]) {
            to_be_undo[i] = true;
            graph[cur_node][i] = 0;
            graph[i][cur_node] = 0;  // 保持对称
        }
    }

    opened[cur_node] = true;
    dfs(cur_node + 1, cur_cuts + 1);

    // 回溯
    opened[cur_node] = false;
    for (int i = 1; i <= n; i++) {
        if (to_be_undo[i]) {
            graph[cur_node][i] = 1;
            graph[i][cur_node] = 1;  // 保持对称
        }
    }

    // 选择2：不打开当前环
    dfs(cur_node + 1, cur_cuts);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int set_num = 0;
    while (cin >> n && n) {
        set_num++;

        // 初始化图
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                graph[i][j] = 0;
            }
            opened[i] = false;
        }

        // 读入边 (成对的连接关系)
        int a, b;
        while (cin >> a >> b && (a != -1 || b != -1)) {
            graph[a][b] = 1;
            graph[b][a] = 1;  // 无向图
        }

        // 初始化搜索
        min_cuts = 16;
        best_solution.clear();

        // 开始DFS
        dfs(1, 0);

        // 输出结果
        cout << "Set " << set_num << ": Minimum links to open is " << min_cuts << "\n";
    }

    return 0;
}
