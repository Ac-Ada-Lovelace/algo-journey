// UVa 225 - Golygons
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 20;
const int MAX_SUM = MAX_N * (MAX_N + 1) / 2; // 1+...+20 = 210
const int BASE = MAX_SUM + 5;                // 原点平移
const int GRID = BASE * 2 + 5;               // 网格大小

// 方向编码: 0 = E, 1 = W, 2 = N, 3 = S
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
char dch[4] = {'e', 'w', 'n', 's'};

// 障碍点 & 终点访问标记（只标记每一步的“终点”交叉口）
bool obs[GRID][GRID];
bool vis[GRID][GRID];

int n;                    // 最后一段长度
vector<string> solutions; // 所有方案
char pathArr[MAX_N + 1];  // pathArr[step-1] 存这一段的方向

inline bool insideReachable(int x, int y) {
    // 理论上不会需要 |x|,|y| > MAX_SUM 的坐标
    return (abs(x) <= MAX_SUM && abs(y) <= MAX_SUM);
}

void dfs(int step, int x, int y, int prevDir) {
    // step: 下一段要走的长度（前面已经走完 1..step-1）

    if (step > n) {
        // 所有段走完，检查是否回到原点
        if (x == 0 && y == 0) {
            pathArr[n] = '\0';
            solutions.emplace_back(pathArr);
        }
        return;
    }

    // 剩余步长总和：step + (step+1) + ... + n
    int rem = (step + n) * (n - step + 1) / 2;
    int dist = abs(x) + abs(y);

    // 剪枝1：就算剩下的全部直线冲回去也不够距离
    if (dist > rem)
        return;

    // 剪枝2：奇偶性不匹配，一定到不了原点
    if ((rem - dist) & 1)
        return;

    // 决定本步可以的方向集合
    int cand[4];
    int cnt = 0;
    if (prevDir == -1) {
        // 第一步：四个方向都可以
        cand[cnt++] = 0; // e
        cand[cnt++] = 1; // w
        cand[cnt++] = 2; // n
        cand[cnt++] = 3; // s
    } else {
        // 之后的每一步必须是 90 度转弯
        if (prevDir == 0 || prevDir == 1) { // 之前是水平 → 现在选垂直
            cand[cnt++] = 2;                // n
            cand[cnt++] = 3;                // s
        } else {                            // 之前是垂直 → 现在选水平
            cand[cnt++] = 0;                // e
            cand[cnt++] = 1;                // w
        }
    }

    for (int i = 0; i < cnt; ++i) {
        int d = cand[i];
        int nx = x;
        int ny = y;
        bool ok = true;

        // 这一段走 step 格，检查中途是否踩到障碍
        for (int t = 0; t < step; ++t) {
            nx += dx[d];
            ny += dy[d];

            if (!insideReachable(nx, ny)) {
                ok = false;
                break;
            }
            if (obs[BASE + nx][BASE + ny]) {
                ok = false;
                break;
            }
        }
        if (!ok)
            continue;

        // 到达终点 (nx, ny)
        // 不能重复作为“终点”到达同一交叉口
        if (vis[BASE + nx][BASE + ny])
            continue;

        // 若提前回到原点且还没走完所有步数，直接剪掉
        if (nx == 0 && ny == 0 && step < n)
            continue;

        vis[BASE + nx][BASE + ny] = true;
        pathArr[step - 1] = dch[d];

        dfs(step + 1, nx, ny, d);

        vis[BASE + nx][BASE + ny] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T))
        return 0;

    while (T--) {
        int k;
        cin >> n >> k;

        memset(obs, 0, sizeof(obs));
        memset(vis, 0, sizeof(vis));
        solutions.clear();

        int maxDisp = n * (n + 1) / 2; // 当前测试用例真正能走到的最大坐标

        // 读入障碍点：超出可达范围的直接忽略
        for (int i = 0; i < k; ++i) {
            int bx, by;
            cin >> bx >> by;
            if (abs(bx) <= maxDisp && abs(by) <= maxDisp) {
                obs[BASE + bx][BASE + by] = true;
            }
        }

        // 从 (0,0) 出发，step=1，上一方向 prevDir=-1（表示不存在）
        dfs(1, 0, 0, -1);

        // 按字典序输出
        sort(solutions.begin(), solutions.end());
        for (const string& s : solutions) {
            cout << s << '\n';
        }
        cout << "Found " << solutions.size() << " golygon(s).\n\n";
    }

    return 0;
}
