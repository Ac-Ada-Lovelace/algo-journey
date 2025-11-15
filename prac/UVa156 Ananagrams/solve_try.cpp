#include <bits/stdc++.h>
using namespace std;

//@brief convert a string to lowercase. you should confirm only alpha in string
string lowercase(string::iterator begin, string::iterator end) {
    string res;
    for (auto it = begin; it != end; ++it) {
        res.push_back(tolower(*it));
    }
    return res;
}
string re_shape(string origin_word) {
    lowercase(origin_word.begin(), origin_word.end());

    vector<char> chars(origin_word.begin(), origin_word.end());
    sort(chars.begin(), chars.end());
    return string(chars.begin(), chars.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    map<string, int> dict;
    while (getline(cin, line)) {
        if (line == "#") {
            break;
        }
        string word;
        for (auto c : line) {
            if (isalpha(static_cast<unsigned char>(c))) {
                word.push_back(c);
            } else {
                auto reshaped = re_shape(word);
                if (dict.find(reshaped) == dict.end()) {
                    dict[reshaped] = 1;
                } else {
                    dict[reshaped]++;
                }
            }
        }
    }

    for (auto w : dict) {
        if (w.second == 1) {
            cout << w.first << '\n';
        }
    }
}
