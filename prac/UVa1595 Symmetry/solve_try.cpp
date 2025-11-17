#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    while (cases--) {
        int num;
        cin >> num;
        map<int, vector<int>> pts_by_y;

        int x, y;
        while (num--) {
            cin >> x >> y;
            pts_by_y[y].push_back(x);
        }
        int flag = 0;
        vector<int> symmetries;
        for (const auto& kv : pts_by_y) {
            auto xs = kv.second;
            sort(xs.begin(), xs.end());

            auto xs_num = xs.size();
            if (xs_num % 2 == 1) {
                for (size_t i = 0; i < xs_num / 2; i++) {
                    if (xs[i] + xs[xs_num - i - 1] != 2 * xs[xs_num / 2]) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    symmetries.push_back(2 * xs[xs_num / 2]);
                }
            } else {
                auto symmetry = xs[xs_num / 2 - 1] + xs[xs_num / 2];
                for (size_t i = 0; i < xs_num / 2; i++) {
                    if (xs[i] + xs[xs_num - i - 1] != symmetry) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    symmetries.push_back(symmetry);
                }
            }
        }

        if (flag) {
            cout << "NO" << endl;

        } else {
            int try_symmetry = symmetries[0];
            for (auto s : symmetries) {
                if (s != try_symmetry) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                cout << "NO" << endl;

            } else {
                cout << "YES" << endl;
            }
        }
    }
}
