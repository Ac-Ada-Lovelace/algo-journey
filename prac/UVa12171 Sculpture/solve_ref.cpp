#include <bits/stdc++.h>
using namespace std;

struct Box {
    int x1, y1, z1;
    int x2, y2, z2; // 右端点开区间：[x1, x2)
};

static bool solid[110][110][110];
static bool vis[110][110][110];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T))
        return 0;
    while (T--) {
        int n;
        cin >> n;

        vector<Box> boxes(n);
        vector<int> xs, ys, zs;

        // 加上外框 0 和 1000（题目坐标与长度范围都在 0..500 之内，最远到 1000）
        xs.push_back(0);
        ys.push_back(0);
        zs.push_back(0);
        xs.push_back(1000);
        ys.push_back(1000);
        zs.push_back(1000);

        for (int i = 0; i < n; ++i) {
            int x0, y0, z0, l, w, h;
            cin >> x0 >> y0 >> z0 >> l >> w >> h;
            boxes[i].x1 = x0;
            boxes[i].y1 = y0;
            boxes[i].z1 = z0;
            boxes[i].x2 = x0 + l;
            boxes[i].y2 = y0 + w;
            boxes[i].z2 = z0 + h;

            xs.push_back(boxes[i].x1);
            xs.push_back(boxes[i].x2);
            ys.push_back(boxes[i].y1);
            ys.push_back(boxes[i].y2);
            zs.push_back(boxes[i].z1);
            zs.push_back(boxes[i].z2);
        }

        // 离散化：排序去重
        auto uniq = [](vector<int>& v) {
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
        };
        uniq(xs);
        uniq(ys);
        uniq(zs);

        int nx = (int)xs.size();
        int ny = (int)ys.size();
        int nz = (int)zs.size();
        int cx = nx - 1; // cell 数
        int cy = ny - 1;
        int cz = nz - 1;

        // 清空 solid / vis
        for (int i = 0; i < cx; ++i)
            for (int j = 0; j < cy; ++j)
                for (int k = 0; k < cz; ++k)
                    solid[i][j][k] = vis[i][j][k] = false;

        auto idx = [](const vector<int>& v, int x) {
            return int(lower_bound(v.begin(), v.end(), x) - v.begin());
        };

        // 把盒子填入 solid 数组
        for (const auto& b : boxes) {
            int ix1 = idx(xs, b.x1);
            int ix2 = idx(xs, b.x2);
            int iy1 = idx(ys, b.y1);
            int iy2 = idx(ys, b.y2);
            int iz1 = idx(zs, b.z1);
            int iz2 = idx(zs, b.z2);

            for (int i = ix1; i < ix2; ++i)
                for (int j = iy1; j < iy2; ++j)
                    for (int k = iz1; k < iz2; ++k)
                        solid[i][j][k] = true;
        }

        // BFS 对空气 flood fill（从 (0,0,0) 外部空气开始）
        static const int dx[6] = {1, -1, 0, 0, 0, 0};
        static const int dy[6] = {0, 0, 1, -1, 0, 0};
        static const int dz[6] = {0, 0, 0, 0, 1, -1};

        queue<tuple<int, int, int>> q;
        vis[0][0][0] = true;
        q.push({0, 0, 0});

        long long airVolume = 0; // 外部空气体积
        long long area = 0;      // 雕塑外表面积

        while (!q.empty()) {
            auto [x, y, z] = q.front();
            q.pop();

            // 当前空气小块体积
            long long cellVol =
                1LL * (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]) * (zs[z + 1] - zs[z]);
            airVolume += cellVol;

            // 6 个方向
            for (int d = 0; d < 6; ++d) {
                int nx_i = x + dx[d];
                int ny_i = y + dy[d];
                int nz_i = z + dz[d];

                // 出界就跳过（外面不需要再 flood）
                if (nx_i < 0 || nx_i >= cx || ny_i < 0 || ny_i >= cy || nz_i < 0 || nz_i >= cz) {
                    continue;
                }

                if (solid[nx_i][ny_i][nz_i]) {
                    // 这一侧是雕塑，增加接触面积
                    long long faceArea = 0;
                    if (dx[d] != 0) { // 法向量是 x 方向
                        faceArea = 1LL * (ys[y + 1] - ys[y]) * (zs[z + 1] - zs[z]);
                    } else if (dy[d] != 0) { // y 方向
                        faceArea = 1LL * (xs[x + 1] - xs[x]) * (zs[z + 1] - zs[z]);
                    } else { // z 方向
                        faceArea = 1LL * (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]);
                    }
                    area += faceArea;
                } else {
                    // 邻居还是空气小块，继续 BFS
                    if (!vis[nx_i][ny_i][nz_i]) {
                        vis[nx_i][ny_i][nz_i] = true;
                        q.push({nx_i, ny_i, nz_i});
                    }
                }
            }
        }

        // 大外包盒总体积
        long long totalVolume =
            1LL * (xs.back() - xs.front()) * (ys.back() - ys.front()) * (zs.back() - zs.front());

        long long sculptureVolume = totalVolume - airVolume;

        // 按题目输出：表面积 体积
        cout << area << ' ' << sculptureVolume << '\n';
    }

    return 0;
}
