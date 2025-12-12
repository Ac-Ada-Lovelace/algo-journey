// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=4485
// UVa1610 Party Games
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    while (true) {
        int n;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<string> names(n);

        for (int i = 0; i < n; i++) {
            cin >> names[i];
        }

        sort(names.begin(), names.end());

        string lm = names[n / 2 - 1];
        string rm = names[n / 2];

        string S{};

        int i;
        int flag = 0;
        for (i = 0; i < min(lm.size(), rm.size()); i++) {
            if (abs(lm[i] - rm[i]) > 1) {
                if (lm[i] == 'Z') {
                    S += string(1, 'Z');
                } else {
                    S += string(1, lm[i] + 1);
                }

                flag = 1;
                break;
            } else if (abs(lm[i] - rm[i]) == 1) {
                S += string(1, lm[i]);
            } else {
                S += string(1, lm[i]);
            }
        }

        if (!flag) {
            if (lm.size() != rm.size()) {
                string t = rm.size() > lm.size() ? rm : lm;
                for (int j = i; j < t.size() - 1; j++) {
                    if (t[j] != 'A') {
                        S += string(1, 'A');
                        flag = 1;
                        break;
                    } else {
                        S += string(1, 'A');
                    }
                }
            } else {
                S += string(1, 'A');
            }
        }
        cout << S << '\n';
    }
}
