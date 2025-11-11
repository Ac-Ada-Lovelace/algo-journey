#include "bits/stdc++.h"

using namespace std;

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, c;
  int puzzle_id = 0;
  while (cin >> r && r != 0) {
    cin >> c;
    vector<string> grid(r);
    for (int i = 0; i < r; ++i) {
      cin >> grid[i];
    }

    ++puzzle_id;

    // 编号数组
    vector<vector<int>> num(r, vector<int>(c, 0));
    int cnt = 0;

    // 1) 给 eligible 白格编号
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (grid[i][j] == '*')
          continue;
        bool up_block = (i == 0 || grid[i - 1][j] == '*');
        bool left_block = (j == 0 || grid[i][j - 1] == '*');
        if (up_block || left_block) {
          num[i][j] = ++cnt;
        }
      }
    }

    // 输出
    if (puzzle_id > 1)
      cout << "\n";
    cout << "puzzle #" << puzzle_id << ":\n";

    // 2) Across
    cout << "Across\n";
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (grid[i][j] == '*')
          continue;
        // 是否为 Across 起点：左边越界或黑格
        if (j == 0 || grid[i][j - 1] == '*') {
          cout << num[i][j] << ".";
          int k = j;
          while (k < c && grid[i][k] != '*') {
            cout << grid[i][k];
            ++k;
          }
          cout << "\n";
        }
      }
    }

    // 3) Down
    cout << "Down\n";
    for (int j = 0; j < c; ++j) {
      for (int i = 0; i < r; ++i) {
        if (grid[i][j] == '*')
          continue;
        // 是否为 Down 起点：上边越界或黑格
        if (i == 0 || grid[i - 1][j] == '*') {
          cout << num[i][j] << ".";
          int k = i;
          while (k < r && grid[k][j] != '*') {
            cout << grid[k][j];
            ++k;
          }
          cout << "\n";
        }
      }
    }
  }
  return 0;
}
