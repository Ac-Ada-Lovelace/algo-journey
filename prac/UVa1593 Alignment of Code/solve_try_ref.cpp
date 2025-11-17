#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<vector<string>> lines;
  string line;
  size_t maxCols = 0;
  while (getline(cin, line)) {
    vector<string> words;
    string word;
    for (size_t i = 0; i <= line.size(); ++i) {
      if (i < line.size() && line[i] != ' ') {
        word += line[i];
      } else {
        if (!word.empty()) {
          words.push_back(word);
          word.clear();
        }
      }
    }
    lines.push_back(words);
    maxCols = max(maxCols, words.size());
  }

  vector<size_t> colWidth(maxCols, 0);
  for (size_t c = 0; c < maxCols; ++c) {
    for (const auto &row : lines) {
      if (c < row.size()) colWidth[c] = max(colWidth[c], row[c].size());
    }
  }

  for (const auto &row : lines) {
    for (size_t c = 0; c < row.size(); ++c) {
      if (c) cout << string(colWidth[c - 1] - row[c - 1].size() + 1, ' ');
      cout << row[c];
    }
    cout << '\n';
  }
  return 0;
}
