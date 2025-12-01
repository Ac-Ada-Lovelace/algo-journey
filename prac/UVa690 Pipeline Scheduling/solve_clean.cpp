// UVa690 Pipeline Scheduling
// 问题：给定流水线的保留表，求完成10个任务的最少时钟周期数
// 思路：DFS搜索 + 剪枝

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_UNITS = 5;     // 功能单元数量
const int MAX_TASKS = 10;    // 需要完成的任务数
const int MAX_CLOCKS = 200;  // 最大时钟周期
const int MAX_TASK_LEN = 20; // 单个任务最大长度

// ========== 全局变量 ==========
int task_len;                               // 单个任务的长度（时钟周期数）
int table[MAX_UNITS][MAX_CLOCKS];           // 保留表，0表示空闲
vector<int> units_needed[MAX_TASK_LEN];     // units_needed[t] = 第t步需要的功能单元列表
int min_gap;                                // 两任务间的最小间隔
int best_time;                              // 当前最优完成时间

// ========== 核心函数 ==========

// 检查能否在start_time时刻启动一个新任务
bool can_start(int start_time) {
    for (int t = 0; t < task_len; t++) {
        int time = start_time + t;
        for (int unit : units_needed[t]) {
            if (table[unit][time] != 0) {
                return false;
            }
        }
    }
    return true;
}

// 在start_time时刻放置/移除任务
// val=0表示移除，val!=0表示放置（通常用任务编号）
void place_task(int start_time, int val) {
    for (int t = 0; t < task_len; t++) {
        int time = start_time + t;
        for (int unit : units_needed[t]) {
            table[unit][time] = val;
        }
    }
}

// DFS搜索
// depth: 已放置的任务数（从第0个开始计数，第0个任务固定在时刻0）
// start_from: 下一个任务的最早启动时间
void dfs(int depth, int start_from) {
    // 所有10个任务都已放置
    if (depth == MAX_TASKS) {
        // 最后一个任务的完成时间 = 最后一个任务的启动时间 + 任务长度
        // start_from - 1 是最后一个任务的启动时间
        best_time = min(best_time, start_from - 1 + task_len);
        return;
    }

    int remaining = MAX_TASKS - depth;  // 剩余需要放置的任务数

    // 枚举下一个任务的启动时间
    for (int t = start_from; t <= best_time; t++) {
        // 剪枝：乐观估计（剩余任务都以最小间隔启动）仍无法超过当前最优解
        if (t + remaining * min_gap >= best_time) {
            return;
        }

        // 检查能否在时刻t启动任务
        if (!can_start(t)) {
            continue;
        }

        // 放置任务并递归搜索
        place_task(t, depth);
        dfs(depth + 1, t + 1);
        place_task(t, 0);  // 回溯
    }
}

// ========== 主程序 ==========

int main() {
    while (scanf("%d", &task_len) == 1 && task_len != 0) {
        // 初始化
        memset(table, 0, sizeof(table));
        for (int i = 0; i < task_len; i++) {
            units_needed[i].clear();
        }

        // 读取保留表
        for (int unit = 0; unit < MAX_UNITS; unit++) {
            getchar();  // 跳过换行
            for (int t = 0; t < task_len; t++) {
                char ch;
                scanf("%c", &ch);
                if (ch == 'X') {
                    units_needed[t].push_back(unit);
                }
            }
        }

        // 计算最小间隔：第一个任务在时刻0，找第二个任务最早能在何时启动
        place_task(0, 1);
        for (int gap = 1; gap <= task_len; gap++) {
            if (can_start(gap)) {
                min_gap = gap;
                break;
            }
        }
        place_task(0, 0);

        // 搜索最优方案
        best_time = task_len * MAX_TASKS;  // 初始上界
        place_task(0, 1);                  // 第一个任务固定在时刻0
        dfs(1, 1);                         // 搜索后续任务
        place_task(0, 0);

        printf("%d\n", best_time);
    }

    return 0;
}
