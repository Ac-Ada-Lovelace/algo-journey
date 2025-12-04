// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=3259
// UVa12107 Digit Puzzle
#include <bits/stdc++.h>
using namespace std;

int calc() {
    return 1;
}
int is_good(int curr_n, int pos, const array<string, 3>& exp) {
    int cnt = 0;

    if (curr_n == 3) {
        return calc();
    }

    if (exp[curr_n][pos] == '*') {
        for (int i = 0; i <= 9; i++) {
            if (i == 0 && pos == 0)
                continue;
            // exp[curr_n][pos] = '0' + i;
            cnt += is_good(curr_n + (pos == exp[curr_n].size() - 1 ? 1 : 0),
                           (pos + 1) % exp[curr_n].size(), exp);
            if (cnt > 1)
                break;
        }
        // exp[curr_n][pos] = '*';
    } else {
        cnt = is_good(curr_n + (pos == exp[curr_n].size() - 1 ? 1 : 0),
                      (pos + 1) % exp[curr_n].size(), exp);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
