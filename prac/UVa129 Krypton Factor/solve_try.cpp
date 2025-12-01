// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=841&page=show_problem&problem=65
// UVa129 Krypton Factor
#include <bits/stdc++.h>
using namespace std;

bool is_valid(string str) {
    if (str.empty()) {
        return true;
    }
    if (str.size() == 1) {
        return true;
    }
    for (int i = 1; i <= str.size() / 2; i++) {
        string post = str.substr(str.size() - i);
        string pre = str.substr(str.size() - 2 * i, i);
        if (post == pre) {
            return false;
        }
    }
    return true;
}

void build(int cur, int target, string& ans, const vector<char>& opt) {
    if (cur == target) {
        return;
    }
    for (auto ch : opt) {
        if (is_valid(ans + ch)) {
            ans.push_back(ch);
            build(cur + 1, target, ans, opt);
            if (ans.size() == target) {
                return;
            }
            ans.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        int n, L;
        stringstream ss(line);
        ss >> n >> L;
        if (n == 0 && L == 0) {
            break;
        }

        string ans = "";
        vector<char> opt;
        for (int i = 0; i < L; i++) {
            opt.push_back('A' + i);
        }
        build(0, n, ans, opt);

        cout << ans << '\n';
        cout << ans.size() << '\n';
    }
}
