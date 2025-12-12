
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    if (!(cin >> T))
        return 0;
    while (T--) {
        int N, W, H;
        cin >> N >> W >> H;

        vector<Point> trees(N);
        for (int i = 0; i < N; i++)
            cin >> trees[i].x >> trees[i].y;

        // ----------------------------------------------------------
        // 1. 离散化 x 坐标：0、所有树的x、W
        //    我们之后枚举竖条带 [xs[i], xs[j]]
        // ----------------------------------------------------------
        vector<int> xs;
        xs.push_back(0);
        for (auto& p : trees)
            xs.push_back(p.x);
        xs.push_back(W);

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        // ----------------------------------------------------------
        // 2. 按 y 升序排列树（空区间扫描时用）
        // ----------------------------------------------------------
        vector<Point> sortedTrees = trees;
        sort(sortedTrees.begin(), sortedTrees.end(),
             [](const Point& a, const Point& b) {
                 if (a.y != b.y)
                     return a.y < b.y;
                 return a.x < b.x;
             });

        // ----------------------------------------------------------
        // 最优答案
        // ----------------------------------------------------------
        int bestL = 0;
        int bestX = 0, bestY = 0;

        // ----------------------------------------------------------
        // 3. 枚举所有竖条带：左边界 xs[i]，右边界 xs[j]
        //    条带宽度 = width = xs[j] - xs[i]
        //    在条带内部的树是 x ∈ (xs[i], xs[j]) 的树
        // ----------------------------------------------------------
        int XN = xs.size();
        for (int i = 0; i < XN; i++) {
            for (int j = i + 1; j < XN; j++) {
                int leftX = xs[i];
                int rightX = xs[j];
                int width = rightX - leftX; // 正方形最大可能宽度

                // 竖条带内部的树，会在 y 方向上“打断”空区间
                // 我们将移动一个指针扫描 sortedTrees

                int lastY = 0; // 当前空区间下端 y

                for (auto& p : sortedTrees) {
                    // 若树 p 不在条带内部，则不会截断空区间
                    if (!(p.x > leftX && p.x < rightX))
                        continue;

                    // p 在条带内部，它的 y 划出空段 [lastY, p.y]
                    int emptyHeight = p.y - lastY;

                    if (emptyHeight > 0) {
                        int side = min(width, emptyHeight);
                        if (side > bestL) {
                            bestL = side;
                            bestX = leftX;
                            bestY = lastY;
                        }
                    }

                    // 更新下一个空区间起点
                    lastY = p.y;
                }

                // 扫完所有树后，还有一个尾巴空区间 [lastY, H]
                int emptyHeight = H - lastY;
                if (emptyHeight > 0) {
                    int side = min(width, emptyHeight);
                    if (side > bestL) {
                        bestL = side;
                        bestX = leftX;
                        bestY = lastY;
                    }
                }
            }
        }

        cout << bestX << " " << bestY << " " << bestL;
        if (T)
            cout << "\n\n";
    }

    return 0;
}
