// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=2155
// UVa11214 Guarding the Chessboard
// 动态评分 + IDA* 算法
#include <bits/stdc++.h>
using namespace std;

int n, m;
char board[10][10];
bool covered[10][10];               // 标记哪些X已被覆盖
vector<pair<int, int>> queens;      // 已放置的皇后位置
vector<pair<int, int>> x_positions; // 所有X的位置

// 8个方向: 上下左右 + 4个斜线
int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

// 检查(r,c)是否在棋盘内
bool inBound(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

// 计算从(r,c)放皇后能覆盖多少未覆盖的X
int calcScore(int r, int c) {
    int score = 0;

    // 如果当前位置是未覆盖的X,加1分
    if (board[r][c] == 'X' && !covered[r][c]) {
        score++;
    }

    // 检查8个方向
    for (int dir = 0; dir < 8; dir++) {
        int nr = r + dx[dir];
        int nc = c + dy[dir];

        while (inBound(nr, nc)) {
            if (board[nr][nc] == 'X' && !covered[nr][nc]) {
                score++;
            }
            nr += dx[dir];
            nc += dy[dir];
        }
    }

    return score;
}

// 放置/移除皇后,更新covered数组
void placeQueen(int r, int c, bool place) {
    if (board[r][c] == 'X') {
        covered[r][c] = place;
    }

    for (int dir = 0; dir < 8; dir++) {
        int nr = r + dx[dir];
        int nc = c + dy[dir];

        while (inBound(nr, nc)) {
            if (board[nr][nc] == 'X') {
                covered[nr][nc] = place;
            }
            nr += dx[dir];
            nc += dy[dir];
        }
    }
}

// 检查是否所有X都被覆盖
bool allCovered() {
    for (auto [r, c] : x_positions) {
        if (!covered[r][c])
            return false;
    }
    return true;
}

// 计算未覆盖的X数量
int countUncovered() {
    int cnt = 0;
    for (auto [r, c] : x_positions) {
        if (!covered[r][c])
            cnt++;
    }
    return cnt;
}

// 找到分数最高的格子
pair<int, int> findBestPosition() {
    int best_score = 0;
    pair<int, int> best_pos = {-1, -1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int score = calcScore(i, j);
            if (score > best_score) {
                best_score = score;
                best_pos = {i, j};
            }
        }
    }

    return best_pos;
}

// IDA* 搜索
bool dfs(int depth, int max_depth) {
    // 所有X都被覆盖,成功
    if (allCovered()) {
        return true;
    }

    // 达到深度限制
    if (depth >= max_depth) {
        return false;
    }

    // 剪枝: 估算还需要多少皇后
    int uncovered = countUncovered();
    auto [br, bc] = findBestPosition();
    int best_score = calcScore(br, bc);

    if (best_score == 0)
        return false; // 无法继续覆盖

    // 乐观估计: 假设每个皇后都能覆盖best_score个X
    int need = (uncovered + best_score - 1) / best_score;
    if (depth + need > max_depth) {
        return false;
    }

    // 找出所有分数较高的候选位置(前几名)
    vector<tuple<int, int, int>> candidates; // (score, r, c)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int score = calcScore(i, j);
            if (score > 0) {
                candidates.push_back({score, i, j});
            }
        }
    }

    // 按分数降序排序
    sort(candidates.rbegin(), candidates.rend());

    // 只尝试前几个高分位置,避免搜索空间过大
    // 优先尝试分数最高的位置,但如果分数太低就多试几个
    int try_count = best_score >= 5 ? min((int)candidates.size(), 5)
                                    : min((int)candidates.size(), 15);

    for (int k = 0; k < try_count; k++) {
        auto [score, r, c] = candidates[k];

        // 如果分数太低,跳过
        if (score == 0)
            break;

        // 放置皇后
        placeQueen(r, c, true);

        if (dfs(depth + 1, max_depth)) {
            return true;
        }

        // 回溯
        placeQueen(r, c, false);
    }

    return false;
}

int solve() {
    // 收集所有X的位置
    x_positions.clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'X') {
                x_positions.push_back({i, j});
            }
        }
    }

    // 特判: 没有X
    if (x_positions.empty())
        return 0;

    // 迭代加深搜索
    for (int max_depth = 1; max_depth <= 5; max_depth++) {
        // 初始化covered数组
        memset(covered, false, sizeof(covered));
        queens.clear();

        if (dfs(0, max_depth)) {
            return max_depth;
        }
    }

    return -1; // 不应该到达这里
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int case_num = 0;
    while (cin >> n && n) {
        cin >> m;
        case_num++;

        for (int i = 0; i < n; i++) {
            cin >> board[i];
        }

        int result = solve();
        cout << "Case " << case_num << ": " << result << "\n";
    }

    return 0;
}
