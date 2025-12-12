#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    if (!(cin >> T))
        return 0;
    while (T--) {
        int N, W, H;
        cin >> N >> W >> H;

        vector<int> tx(N), ty(N);
        for (int i = 0; i < N; i++)
            cin >> tx[i] >> ty[i];

        // 离散化候选坐标：必须包含 0
        vector<int> candX = {0}, candY = {0};
        for (int x : tx)
            candX.push_back(x);
        for (int y : ty)
            candY.push_back(y);

        int bestL = -1;
        int bestX = 0, bestY = 0;

        for (int X : candX)
            for (int Y : candY) {
                int L = min(W - X, H - Y); // 边界限制

                for (int i = 0; i < N; i++) {
                    int xx = tx[i], yy = ty[i];
                    // 如果树影响这个区域（树在右上侧）
                    if (xx >= X && yy >= Y) {
                        int limit = min(xx - X - 1, yy - Y - 1);
                        L = min(L, limit);
                    }
                    if (L < 0)
                        break;
                }

                if (L >= 0 && L > bestL) {
                    bestL = L;
                    bestX = X;
                    bestY = Y;
                }
            }

        cout << bestX << " " << bestY << " " << bestL << "\n";
        if (T)
            cout << "\n";
    }
    return 0;
}
