#include <bits/stdc++.h>

using namespace std;

struct Command {
  string type;
  vector<int> args;
};

vector<Command> readCommands() {
  int n;
  cin >> n;
  vector<Command> cmds;
  cmds.reserve(n);
  while (n--) {
    string op;
    cin >> op;
    Command cmd;
    cmd.type = op;
    if (op == "EX") {
      cmd.args.resize(4);
      for (int i = 0; i < 4; ++i) {
        cin >> cmd.args[i];
      }
    } else {
      int a;
      cin >> a;
      cmd.args.resize(a);
      for (int i = 0; i < a; ++i) {
        cin >> cmd.args[i];
      }
      sort(cmd.args.begin(), cmd.args.end());
    }
    cmds.push_back(std::move(cmd));
  }
  return cmds;
}

pair<bool, pair<int, int>> trackCell(int row, int col,
                                     const vector<Command> &cmds) {
  bool alive = true;
  for (const auto &cmd : cmds) {
    if (!alive)
      break;
    if (cmd.type == "EX") {
      int r1 = cmd.args[0], c1 = cmd.args[1];
      int r2 = cmd.args[2], c2 = cmd.args[3];
      if (row == r1 && col == c1) {
        row = r2;
        col = c2;
      } else if (row == r2 && col == c2) {
        row = r1;
        col = c1;
      }
    } else if (cmd.type == "DR") {
      int removed = 0;
      for (int x : cmd.args) {
        if (x == row) {
          alive = false;
          break;
        }
        if (x < row)
          ++removed;
      }
      if (alive)
        row -= removed;
    } else if (cmd.type == "DC") {
      int removed = 0;
      for (int x : cmd.args) {
        if (x == col) {
          alive = false;
          break;
        }
        if (x < col)
          ++removed;
      }
      if (alive)
        col -= removed;
    } else if (cmd.type == "IR") {
      int added = 0;
      for (int x : cmd.args) {
        if (x <= row)
          ++added;
      }
      row += added;
    } else if (cmd.type == "IC") {
      int added = 0;
      for (int x : cmd.args) {
        if (x <= col)
          ++added;
      }
      col += added;
    }
  }
  return {alive, {row, col}};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  int caseNo = 1;
  while (cin >> rows >> cols && rows && cols) {
    auto cmds = readCommands();
    int q;
    cin >> q;

    if (caseNo > 1)
      cout << "\n";
    cout << "Spreadsheet #" << caseNo++ << "\n";

    while (q--) {
      int r, c;
      cin >> r >> c;
      auto [alive, pos] = trackCell(r, c, cmds);
      if (!alive) {
        cout << "Cell data in (" << r << "," << c << ") GONE\n";
      } else {
        cout << "Cell data in (" << r << "," << c << ") moved to (" << pos.first
             << "," << pos.second << ")\n";
      }
    }
  }

  return 0;
}
