#include <bits/stdc++.h>
using namespace std;

int main() {
    int game;
    string ans;
    string guess;

    while (true) {
        cin >> game;
        if (game == -1)
            break;

        char char_set[26];
        cout << "Round" << game << endl;
        cin >> ans;
        cin >> guess;
        int wrong = 0;
        for (auto c : ans) {
            char_set[c - 'a'] = 1;
        }
        for (auto c : guess) {
            if (char_set[c - 'a'] == 1) {
                char_set[c - 'a'] = -1;
            } else if (char_set[c - 'a'] == 0) {
                wrong++;
                if (wrong == 7) {
                    cout << "You lose." << endl;
                    continue;
                }
            }
        }
        for (int i = 0; i < 26; i++) {
            if (char_set[i] == 1) {
                cout << "You chickened out." << endl;
                continue;
            }
        }
        cout << "You win." << endl;
        return 0;
    }
}
