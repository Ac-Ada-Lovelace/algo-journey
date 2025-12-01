// Simple 8-puzzle solver using BFS (shortest number of moves)
#include <bits/stdc++.h>
using namespace std;

// Read 9 tiles as a single string; accepts spaces/newlines between tiles.
string read_state() {
  string s, token;
  while (cin >> token) {
    for (char c : token) {
      if (c == 'x') c = '0';  // allow 'x' as blank
      if (isdigit(c)) s.push_back(c);
      if (s.size() == 9) return s;
    }
  }
  return s;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const string goal = "123456780";
  const char moves[4] = {'L', 'R', 'U', 'D'};
  const int adj[9][4] = {
      {1, 3, -1, -1}, {0, 2, 4, -1}, {1, 5, -1, -1},
      {0, 4, 6, -1},  {1, 3, 5, 7},  {2, 4, 8, -1},
      {3, 7, -1, -1}, {4, 6, 8, -1}, {5, 7, -1, -1}};

  string start = read_state();
  if (start.size() != 9) return 0;

  auto parity = [](const string& s) {
    int inv = 0;
    for (int i = 0; i < 9; ++i)
      if (s[i] != '0')
        for (int j = i + 1; j < 9; ++j)
          if (s[j] != '0' && s[i] > s[j]) ++inv;
    return inv & 1;
  };

  if (parity(start) != parity(goal)) {
    cout << "unsolvable\n";
    return 0;
  }

  unordered_map<string, pair<string, char>> pre;  // state -> (parent, move)
  queue<string> q;
  pre[start] = {"", 0};
  q.push(start);

  while (!q.empty()) {
    string cur = q.front();
    q.pop();
    if (cur == goal) break;
    int z = cur.find('0');
    for (int k = 0; k < 4 && adj[z][k] != -1; ++k) {
      int nz = adj[z][k];
      string nxt = cur;
      swap(nxt[z], nxt[nz]);
      if (pre.count(nxt)) continue;
      pre[nxt] = {cur, moves[k]};
      q.push(nxt);
    }
  }

  if (!pre.count(goal)) {
    cout << "unsolvable\n";
    return 0;
  }

  string path;
  for (string s = goal; s != start; s = pre[s].first) path.push_back(pre[s].second);
  reverse(path.begin(), path.end());
  cout << path << '\n';
  return 0;
}
