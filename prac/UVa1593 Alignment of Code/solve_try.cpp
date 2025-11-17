#include <bits/stdc++.h>
using namespace std;
string fix_width(string raw, int width, char fill_char = ' ') {
    string fixed = raw;
    while ((int)fixed.size() < width) {
        fixed += fill_char;
    }
    return fixed;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<string>> codes;
    string line;
    int line_count = 0;
    int max_col = 0;
    vector<int> longest_word_by_col = {0};
    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }
        codes.emplace_back();

        string word = "";
        for (auto c : line) {
            if (c != ' ') {
                word += c;
            } else {
                codes[line_count].push_back(word);
                word.clear();

                continue;
            }
        }
        if (codes[line_count].size() > max_col) {
            max_col = codes[line_count].size();
            longest_word_by_col.resize(max_col, 0);
        }
        line_count++;
    }
    for (int i = 0; i < line_count; i++) {
        codes[i].resize(max_col, "");
    }
    longest_word_by_col.resize(max_col, 0);
    for (int l = 0; l < max_col; l++) {
        for (int i = 0; i < line_count; i++) {
            if (longest_word_by_col[l] < (int)codes[i][l].size()) {
                longest_word_by_col[l] = codes[i][l].size();
            }
        }
    }
    for(int i = 0; i < line_count; i++) {
        for (int l = 0; l < max_col; l++) {
            if(codes[i][l].empty()) {
                continue;
            }
            cout << fix_width(codes[i][l], longest_word_by_col[l]);
            if (l != max_col - 1) {
                cout << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
