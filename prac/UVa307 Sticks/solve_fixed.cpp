// UVa 307 - Sticks
// 题意：给定n根小木棍，求能拼成的相同长度的大木棍的最小长度
// 思路：枚举目标长度，DFS回溯搜索，关键在于剪枝
#include <bits/stdc++.h>
using namespace std;

// ===== 数据结构设计 =====
// 1. 小木棍：用 vector<int> 存储长度，用 vector<bool> 标记是否使用
// 2. 搜索状态：通过函数参数传递，避免全局变量
// 3. 剪枝信息：fail 变量记录失败的长度

// ===== DFS 搜索函数 =====
// count: 还需要拼接的完整大木棍数量
// curr_len: 当前正在拼接的大木棍的当前长度
// target_len: 目标大木棍长度
// start: 从哪个位置开始搜索（避免重复搜索）
// sticks: 小木棍数组
// used: 标记数组
bool dfs(int count, int curr_len, int target_len, int start,
         vector<int>& sticks) {
    // 终止条件：所有大木棍都拼接完成
    if (count == 0) {
        return true;
    }

    // 当前大木棍拼接完成，开始拼接下一根
    if (curr_len == target_len) {
        return dfs(count - 1, 0, target_len, 0, sticks);
    }

    // 记录本层尝试过且失败的长度
    int fail = -1;

    // 枚举所有未使用的小木棍
    for (int i = start; i < sticks.size(); i++) {
        // 剪枝1：跳过已使用的木棍
        if (sticks[i] == 0)
            continue;

        // 剪枝2：跳过相同长度的木棍（因为已排序，相同长度效果一样）
        if (sticks[i] == fail)
            continue;

        // 剪枝3：长度超过限制
        if (curr_len + sticks[i] > target_len)
            continue;

        // 选择当前木棍
        int temp;
        temp = sticks[i];
        sticks[i] = 0;

        // 递归搜索
        if (dfs(count, curr_len + temp, target_len, i + 1, sticks)) {
            return true;
        }

        // 回溯
        sticks[i] = temp;
        fail = sticks[i];

        // 剪枝4：如果是当前大木棍的第一根就失败，直接返回
        // 因为相同长度的其他木棍作为第一根也会失败
        if (curr_len == 0) {
            break;
        }

        // 剪枝5：如果刚好拼满一根大木棍却失败，说明后续无解
        if (curr_len + sticks[i] == target_len) {
            break;
        }
    }

    return false;
}

// ===== 求解函数 =====
int solve() {
    // 1. 读取输入
    int n;
    cin >> n;

    // 输入结束标记
    if (n == 0)
        return -1;

    // 2. 初始化数据结构
    vector<int> sticks(n);
    int sum = 0;     // 总长度
    int max_len = 0; // 最长的小木棍

    for (int i = 0; i < n; i++) {
        cin >> sticks[i];
        sum += sticks[i];
        max_len = max(max_len, sticks[i]);
    }

    // 3. 预处理：从大到小排序（优先使用长木棍，减少搜索深度）
    sort(sticks.rbegin(), sticks.rend());

    // 4. 枚举目标长度（从小到大，找到的第一个就是答案）
    for (int target_len = max_len; target_len <= sum; target_len++) {
        // 剪枝：目标长度必须能整除总长度
        if (sum % target_len != 0)
            continue;

        // 计算需要拼成的大木棍数量
        int count = sum / target_len;

        // DFS 搜索
        vector<bool> used(n, false);
        if (dfs(count, 0, target_len, 0, sticks)) {
            return target_len;
        }
    }

    // 理论上不会到这里（最坏情况下答案是 sum）
    return sum;
}

// ===== 主函数 =====
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 处理多组测试数据
    while (true) {
        int result = solve();
        if (result == -1)
            break;
        cout << result << '\n';
    }

    return 0;
}
