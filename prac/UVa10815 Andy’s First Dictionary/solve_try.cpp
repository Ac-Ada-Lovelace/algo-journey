#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<string> dict;
    string line;
    string current;
    while (getline(cin, line)) {
        current.clear();
        for (char ch : line) {
            if (isalpha(static_cast<unsigned char>(ch))) {
                current.push_back(static_cast<char>(tolower(ch)));
            } else if (!current.empty()) {
                dict.insert(current);
                current.clear();
            }
        }
        if (!current.empty()) {
            dict.insert(current);
            current.clear();
        }
    }

    for (const auto& word : dict) {
        cout << word << '\n';
    }
    return 0;
}
