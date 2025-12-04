// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=109&page=show_problem&problem=243
// UVa307 Sticks
#include <bits/stdc++.h>
using namespace std;

bool dfs(int count, int curr_len, int target_len, int last,
         vector<int> &sticks) {
    if (count == 0)
        return true;

    if (curr_len == target_len) {
        return dfs(count - 1, 0, target_len, 0, sticks);
    }

    int fail = 0;
    for (int i = last; i < sticks.size(); i++) {
        if (sticks[i] == 0 || sticks[i] == fail)
            continue;

        if (curr_len + sticks[i] > target_len)
            continue;

        int temp = sticks[i];
        sticks[i] = 0;
        if (dfs(count, curr_len + temp, target_len, i + 1, sticks))
            return true;
        sticks[i] = temp;
        fail = temp;

        if (curr_len == 0 || curr_len + temp == target_len)
            break;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        cin >> n;
        if (n == 0)
            break;

        vector<int> sticks;
        int min_len = INT_MAX;
        int max_len = INT_MIN;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int l;
            cin >> l;
            sticks.push_back(l);
            sum += l;
            min_len = min(min_len, l);
            max_len = max(max_len, l);
        }

        sort(sticks.rbegin(), sticks.rend());

    for (int len = max_len; len <= sum; len++) {
            if(sum % len != 0)
                continue;

            int cnt = sum / len;
            if (dfs(cnt, 0, len, 0, sticks)) {
                cout << len << '\n';
                break;
            }
        }
    }
}
