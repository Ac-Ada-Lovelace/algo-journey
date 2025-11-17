#include <bits/stdc++.h>
using namespace std;

bool is_compound_word(const string& word, const set<string>& dicts) {
    for (int i = 1; i < word.size(); i++) {
        string left = word.substr(0, i);
        string right = word.substr(i);
        if (dicts.count(left) && dicts.count(right)) {
            return true;
        }
    }
    return false;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    set<string> dicts;
    set<string> compound_words;

    string word;
    while (cin >> word) {
        if (word.empty()) {
            break;
        }
        dicts.insert(word);
    }
    for (auto w : dicts) {
        if (is_compound_word(w, dicts)) {
            compound_words.insert(w);
        }
    }
    for (auto w : compound_words) {
        cout << w << '\n';
    }
}
