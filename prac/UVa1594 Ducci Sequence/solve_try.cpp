#include <bits/stdc++.h>
using namespace std;

vector<int> get_next(vector<int> seq) {
    vector<int> next_seq(seq.size());
    for (size_t i = 0; i < seq.size(); i++) {
        next_seq[i] = abs(seq[i] - seq[(i + 1) % seq.size()]);
    }

    return next_seq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    while (cases--) {
        size_t num;
        cin >> num;
        vector<int> seq(num);
        set<vector<int>> seen;
        for (size_t i = 0; i < num; i++) {
            cin >> seq[i];
        }
        seen.insert(seq);

        while (true) {
            auto nxt_s = get_next(seq);
            int flag = 0;
            for (auto i : nxt_s) {
                flag += i;
            }
            if (!flag) {
                cout << "ZERO\n";
                break;
            }

            if (seen.count(nxt_s)) {
                cout << "LOOP\n";
                break;
            }
            seen.insert(nxt_s);
            seq = nxt_s;
        }
    }
}
