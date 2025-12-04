// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=3004
// UVa11882 Biggest Number
#include <bits/stdc++.h>
using namespace std;

int r, c;
char grid[20][20];
bool visited[20][20];
string maxResult;

// 4个方向
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool inBound(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

// 剪枝:检查从当前状态能否超过最优解
bool canBeBetter(const string& current) {
    if (maxResult.empty()) return true;

    // 只有在当前路径长度>=最优解长度,且字典序<=最优解时才剪枝
    if (current.length() >= maxResult.length()) {
        if (current <= maxResult) {
            return false;
        }
    }
    // 如果当前路径较短,还有机会通过后续路径超越,不剪枝

    return true;
}

void dfs(int x, int y, string current) {
    // 标记当前位置已访问
    visited[x][y] = true;
    current += grid[x][y];

    // 更新最优解
    // 比较规则:先比较长度,长度相同再比较字典序
    bool isBetter = false;
    if (current.length() > maxResult.length()) {
        isBetter = true;
    } else if (current.length() == maxResult.length() && current > maxResult) {
        isBetter = true;
    }

    if (isBetter) {
        maxResult = current;
        // cerr << "Found better: " << current << " at (" << x << "," << y << ")" << endl;
    }

    // 尝试4个方向
    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // 检查合法性
        if (!inBound(nx, ny)) continue;
        if (visited[nx][ny]) continue;
        if (grid[nx][ny] == '#') continue;

        // 递归搜索
        dfs(nx, ny, current);
    }

    // 回溯:恢复访问状态
    visited[x][y] = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> r >> c && (r || c)) {
        // 读入网格
        for (int i = 0; i < r; i++) {
            cin >> grid[i];
        }

        // 初始化
        maxResult = "";
        memset(visited, false, sizeof(visited));

        // 枚举所有可能的起点
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] != '#') {
                    dfs(i, j, "");
                }
            }
        }

        cout << maxResult << "\n";
    }

    return 0;
}
