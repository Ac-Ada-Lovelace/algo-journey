// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=3326
// UVa12174 Shuffle
#include <bits/stdc++.h>
using namespace std;
int s, n;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    while (T--) {
        cin >> s >> n;

        map<int, vector<int>> record;
        int sing = 0;
        int imp = 0;
        vector<pair<int, int>> lrs;
        for (int i = 1; i <= n; i++) {
            cin >> sing;
            if (record.count(sing) && record[sing].size() > 1) {
                if (i - record[sing][0] <= s * record[sing].size()) {
                    imp = 1;
                    break;
                }
            }
            record[sing].push_back(i);
            int _l, _r;
            _r = record[sing][record.size() - 1];
            for (int j = 0; j < record[sing].size() - 1; j++) {
                _l = record[sing][j];
                if (lrs.empty())
                    lrs.push_back({_l, _r});
                for (auto& lr : lrs) {
                    int l = lr.first;
                    int r = lr.second;

                    if (r < _l) {
                        if (_r - l < s) {
                            imp = 1;
                            break;
                        }
                        lrs.push_back({_l, _r});
                        continue;
                    }
                    if (_r < l) {
                        if (r - _l < s) {
                            imp = 1;
                            break;
                        }
                        continue;
                    }
                    if (_l < r) {
                        if (r <= _r) {
                            lr.first = _l;
                        } else {
                            lr.first = _l;
                            lr.second = _r;
                        }
                    }
                    if (_r > l) {
                        if (_l <= l) {
                            lr.second = _r;
                        }
                    }
                }
            }
        }

        if (imp) {
            cout << "0" << '\n';
            continue;
        }
        int sum = 0;
        for (auto lr : lrs) {
            sum += (lr.second - lr.first);
        }

        cout << sum << '\n';
    }
}
