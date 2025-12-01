#include <bits/stdc++.h>
using namespace std;

// IDDFS 加/减法链搜索，求最少步数
int target;

bool dfs(int depth, int limit, vector<int>& chain) {
    int cur_max = chain.back();
    if (cur_max == target)
        return true;
    if (depth == limit)
        return false;

    int remain = limit - depth;
    // 即便每步翻倍也达不到目标，剪枝
    if ((cur_max << remain) < target)
        return false;

    vector<int> cand;
    // 只用当前最大值和其他值组合，减少分支
    for (int v : chain) {
        int add = cur_max + v;
        int sub = abs(cur_max - v);
        if (add > 0)
            cand.push_back(add);
        if (sub > 0)
            cand.push_back(sub);
    }
    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());
    for (auto it = cand.rbegin(); it != cand.rend(); ++it) {
        int nxt = *it;
        if (nxt > cur_max * 2)
            continue; // 无需超出两倍范围
        if (find(chain.begin(), chain.end(), nxt) != chain.end())
            continue;
        int new_max = max(cur_max, nxt);
        int next_remain = remain - 1;
        if (next_remain >= 0 && (new_max << next_remain) < target)
            continue; // 即便后续全翻倍也追不上
        chain.push_back(nxt);
        if (dfs(depth + 1, limit, chain))
            return true;
        chain.pop_back();
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> target && target) {
        if (target == 1) {
            cout << 0 << "\n";
            continue;
        }
        vector<int> chain = {1};
        int limit = 0;
        while (true) {
            if (dfs(0, limit, chain)) {
                cout << limit << "\n";
                break;
            }
            ++limit;
        }
    }
    return 0;
}
