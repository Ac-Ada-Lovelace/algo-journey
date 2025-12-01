// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=841&page=show_problem&problem=4120
// UVa1374 Power Calculus
#include <bits/stdc++.h>
using namespace std;

int is_finished = 0;
int reached_depth = INT_MAX;
void dfs(int depth, int target, vector<int>& curr) {
    if (is_finished) {
        return;
    }
    vector<int> possible_nxt;
    for (int i = 0; i < curr.size(); i++) {
        for (int j = i; j < curr.size(); j++) {
            if (find(curr.begin(), curr.end(), curr[i] + curr[j]) !=
                curr.end()) {
                continue;
            }
            if (find(possible_nxt.begin(), possible_nxt.end(),
                     curr[i] + curr[j]) != possible_nxt.end()) {
                continue;
            }
            possible_nxt.push_back(curr[i] + curr[j]);
        }
    }
    for (int i = 0; i < curr.size(); i++) {
        for (int j = i; j < curr.size(); j++) {
            if (find(curr.begin(), curr.end(), curr[i] - curr[j]) !=
                curr.end()) {
                continue;
            }
            if (find(possible_nxt.begin(), possible_nxt.end(),
                     curr[i] - curr[j]) != possible_nxt.end()) {
                continue;
            }
            possible_nxt.push_back(curr[i] - curr[j]);
        }
    }
    for (auto i : possible_nxt) {
        if (is_finished) {
            return;
        }
        curr.push_back(i);
        if (i == target) {
            reached_depth = min(reached_depth, depth + 1);
            is_finished = 1;
            return;
        }
        dfs(depth + 1, target, curr);
        if (is_finished) {
            return;
        }
        curr.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            break;
        }
        is_finished = 0;
        reached_depth = INT_MAX;

        vector<int> curr = {1};
        dfs(0, n, curr);
        cout << reached_depth << "\n";
    }
}
