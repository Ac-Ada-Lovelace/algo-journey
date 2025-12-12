// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=114&page=show_problem&problem=378
// UVa437 The Tower of Babylon
#include <bits/stdc++.h>
using namespace std;

struct Block {
    int w, d, h; // w >= d 表示底面的两条边，h 表示高度
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    int tc = 1;
    while (cin >> n) {
        if (n == 0)
            break;

        vector<Block> blocks;
        blocks.reserve(n * 3);
        for (int i = 0; i < n; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            // 生成三种朝向，并将底面两边排序成 (max, min)
            int a = max(x, y), b = min(x, y);
            blocks.push_back({a, b, z});
            a = max(x, z), b = min(x, z);
            blocks.push_back({a, b, y});
            a = max(y, z), b = min(y, z);
            blocks.push_back({a, b, x});
        }

        // 按底面从大到小排序，保证能承载的块排在前面
        sort(blocks.begin(), blocks.end(), [](const Block& p, const Block& q) {
            if (p.w != q.w)
                return p.w > q.w;
            return p.d > q.d;
        });

        int m = blocks.size();
        vector<int> dp(m, 0);
        int ans = 0;
        for (int i = 0; i < m; i++) {
            dp[i] = blocks[i].h;
            for (int j = 0; j < i; j++) {
                if (blocks[j].w > blocks[i].w && blocks[j].d > blocks[i].d) {
                    dp[i] = max(dp[i], blocks[i].h + dp[j]);
                }
            }
            ans = max(ans, dp[i]);
        }

        cout << "Case " << tc << ": maximum height = " << ans << "\n";
        tc++;
    }

    return 0;
}
