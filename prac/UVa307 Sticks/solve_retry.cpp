#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

vector<int> sticks; // orderd by less
vector<bool> used;
int stick_count;

int dfs(int target_len, int curr_len, int completed_sticks) {
    if (completed_sticks == stick_count) {
        return 1;
    }
    if (curr_len == target_len) {
        return dfs(target_len, 0, completed_sticks + 1);
    }

    for (int i = 0; i < used.size(); i++) {
        if (used[i])
            continue;

        int stick_len = sticks[i];

        if (stick_len + curr_len > target_len)
            continue;

        used[i] = true;
        int nxt_len = stick_len + curr_len;
        dfs(target_len, nxt_len, completed_sticks);
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
