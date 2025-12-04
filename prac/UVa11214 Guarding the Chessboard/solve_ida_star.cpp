// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=2155
// UVa11214 Guarding the Chessboard
// 经典IDA*算法
#include <bits/stdc++.h>
using namespace std;

int n, m;
char board[10][10];
bool covered[10][10];

// 8个方向
int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

bool inBound(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

// 放置/移除皇后
void toggle(int r, int c, bool val) {
    if (board[r][c] == 'X') covered[r][c] = val;

    for (int dir = 0; dir < 8; dir++) {
        int nr = r + dx[dir];
        int nc = c + dy[dir];
        while (inBound(nr, nc)) {
            if (board[nr][nc] == 'X') {
                covered[nr][nc] = val;
            }
            nr += dx[dir];
            nc += dy[dir];
        }
    }
}

// 计算位置(r,c)能覆盖多少未覆盖的X
int countCover(int r, int c) {
    int cnt = 0;
    if (board[r][c] == 'X' && !covered[r][c]) cnt++;

    for (int dir = 0; dir < 8; dir++) {
        int nr = r + dx[dir];
        int nc = c + dy[dir];
        while (inBound(nr, nc)) {
            if (board[nr][nc] == 'X' && !covered[nr][nc]) {
                cnt++;
            }
            nr += dx[dir];
            nc += dy[dir];
        }
    }
    return cnt;
}

// 估价函数:还需要至少多少个皇后
int h() {
    int maxCover = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            maxCover = max(maxCover, countCover(i, j));
        }
    }
    if (maxCover == 0) return 0;

    // 统计未覆盖的X数量
    int uncovered = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'X' && !covered[i][j]) {
                uncovered++;
            }
        }
    }

    return (uncovered + maxCover - 1) / maxCover;
}

// IDA*搜索
bool dfs(int depth, int maxDepth) {
    int hval = h();
    if (hval == 0) return true;  // 所有X都被覆盖
    if (depth + hval > maxDepth) return false;  // 剪枝

    // 找到能覆盖最多未覆盖X的位置
    int bestR = -1, bestC = -1, bestScore = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int score = countCover(i, j);
            if (score > bestScore) {
                bestScore = score;
                bestR = i;
                bestC = j;
            }
        }
    }

    if (bestScore == 0) return false;

    //只尝试分数较高的几个位置
    vector<tuple<int,int,int>> cands;  // (score, r, c)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int score = countCover(i, j);
            if (score > 0) {
                cands.push_back({score, i, j});
            }
        }
    }

    sort(cands.rbegin(), cands.rend());

    // 尝试前几个最佳位置 - 优先尝试最优的,减少分支
    // depth=0多试几个,后续层激进贪心
    int tryLimit;
    if (depth == 0) tryLimit = min((int)cands.size(), 20);
    else if (depth == 1) tryLimit = min((int)cands.size(), 8);
    else tryLimit = min((int)cands.size(), 3);

    for (int k = 0; k < tryLimit; k++) {
        auto [score, r, c] = cands[k];
        // 如果分数明显低于最佳,跳过
        if (k >= 3 && score < bestScore * 2 / 3) break;

        toggle(r, c, true);
        if (dfs(depth + 1, maxDepth)) {
            return true;
        }
        toggle(r, c, false);
    }

    return false;
}

int solve() {
    // 检查是否有X
    bool hasX = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'X') {
                hasX = true;
                break;
            }
        }
        if (hasX) break;
    }

    if (!hasX) return 0;

    // 迭代加深
    for (int maxDepth = 1; maxDepth <= 5; maxDepth++) {
        memset(covered, false, sizeof(covered));
        if (dfs(0, maxDepth)) {
            return maxDepth;
        }
    }

    return 5;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int caseNum = 0;
    while (cin >> n && n) {
        cin >> m;
        caseNum++;

        for (int i = 0; i < n; i++) {
            cin >> board[i];
        }

        cout << "Case " << caseNum << ": " << solve() << "\n";
    }

    return 0;
}
