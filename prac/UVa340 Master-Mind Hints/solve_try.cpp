#include <bits/stdc++.h>
using namespace std;

pair<int, int> evaluateHint(const vector<int>& secret, const vector<int>& guess) {
    int strong = 0;
    int n = secret.size();
    vector<int> freqSecret(10), freqGuess(10);
    for (int i = 0; i < n; i++) {
        if (secret[i] == guess[i]) {
            strong++;
        } else {
            freqSecret[secret[i]]++;
            freqGuess[guess[i]]++;
        }
    }
    int weak = 0;
    for (int v = 1; v <= 9; v++) {
        weak += min(freqSecret[v], freqGuess[v]);
    }
    return {strong, weak};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int game = 0;
    while (cin >> n && n) {
        vector<int> secret(n);
        for (int i = 0; i < n; i++)
            cin >> secret[i];

        cout << "Game " << ++game << ":\n";
        vector<int> guess(n);
        while (true) {
            for (int i = 0; i < n; i++)
                cin >> guess[i];
            if (all_of(guess.begin(), guess.end(), [](int x) {
                    return x == 0;
                }))
                break;
            auto [strong, weak] = evaluateHint(secret, guess);
            cout << "(" << strong << "," << weak << ")\n";
        }
    }
    return 0;
}
