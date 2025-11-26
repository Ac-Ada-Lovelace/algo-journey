#include <bits/stdc++.h>
using namespace std;

struct State {
  int r;
  int c;
  int streak;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  if (!(cin >> T)) return 0;
  while (T--) {
    int m, n;
    cin >> m >> n;
    int k;
    cin >> k;
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        cin >> grid[i][j];

    const int INF = -1;
    vector dist(m, vector(n, vector<int>(k + 1, INF)));
    queue<State> q;
    dist[0][0][0] = 0;
    q.push({0, 0, 0});
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};
    int answer = -1;

    while (!q.empty()) {
      auto [r, c, streak] = q.front();
      q.pop();
      int cur = dist[r][c][streak];
      if (r == m - 1 && c == n - 1) {
        answer = cur;
        break;
      }
      for (int dir = 0; dir < 4; ++dir) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
        int next_streak = (grid[nr][nc] == 1) ? streak + 1 : 0;
        if (next_streak > k) continue;
        if (dist[nr][nc][next_streak] != INF) continue;
        dist[nr][nc][next_streak] = cur + 1;
        q.push({nr, nc, next_streak});
      }
    }

    cout << answer << '\n';
  }
  return 0;
}
