#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<string>> lines;
    string s;
    size_t cols = 0;
    while (getline(cin, s)) {
        vector<string> words;
        string cur;
        for (char ch : s) {
            if (ch == ' ') {
                if (!cur.empty()) {
                    words.push_back(cur);
                    cur.clear();
                }
            } else
                cur += ch;
        }
        if (!cur.empty())
            words.push_back(cur);
        cols = max(cols, words.size());
        lines.push_back(move(words));
    }

    vector<size_t> width(cols);
    for (size_t c = 0; c < cols; ++c)
        for (auto& row : lines)
            if (c < row.size())
                width[c] = max(width[c], row[c].size());

    for (auto& row : lines) {
        for (size_t c = 0; c < row.size(); ++c) {
            if (c)
                cout << string(width[c - 1] - row[c - 1].size() + 1, ' ');
            cout << row[c];
        }
        cout << '\n';
    }
    return 0;
}
