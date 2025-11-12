#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int round;
    while (cin >> round && round != -1) {
        cout << "Round " << round << '\n';
        string answer, guess;
        cin >> answer >> guess;

        array<bool, 26> inAnswer{};
        array<bool, 26> used{};
        int remaining = 0;
        for (char c : answer) {
            int idx = c - 'a';
            if (!inAnswer[idx]) {
                inAnswer[idx] = true;
                ++remaining; // 顺便计数不同字母的数量
            }
        }

        int wrong = 0;
        bool win = false;
        bool lose = false;
        for (char c : guess) {
            int idx = c - 'a';
            if (used[idx] || win || lose)
                continue;
            used[idx] = true;
            if (inAnswer[idx]) {
                inAnswer[idx] = false;
                if (--remaining == 0)
                    win = true;
            } else {
                if (++wrong == 7)
                    lose = true;
            }
        }

        if (win) {
            cout << "You win.\n";
        } else if (lose) {
            cout << "You lose.\n";
        } else {
            cout << "You chickened out.\n";
        }
    }

    return 0;
}
