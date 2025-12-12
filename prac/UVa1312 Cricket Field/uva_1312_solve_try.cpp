// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=4058
// UVa1312 Cricket Field
#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, W, H;
        cin >> N >> W >> H;

        vector<point> trees(N);
        vector<int> xs(N + 2);

        xs[0] = 0;
        for (int i = 0; i < N; i++) {
            point& p = trees[i];
            cin >> p.x >> p.y;
            xs[i + 1] = p.x;
        }
        xs[N + 1] = W;

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        sort(trees.begin(), trees.end(), [](const point& a, const point& b) {
            if (a.y != b.y)
                return a.y < b.y;
            return a.x < b.x;
        });

        int bestL = 0;
        int bestX = 0, bestY = 0;

        for (int i = 0; i < xs.size(); i++) {
            for (int j = i + 1; j < xs.size(); j++) {
                int lx = xs[i];
                int rx = xs[j];
                int ideal_width = rx - lx;

                int lastY = 0;
                for (auto& t : trees) {
                    if (t.x > lx && t.x < rx) {
                        int opt_width = t.y - lastY;
                        int side = min(ideal_width, opt_width);
                        if (side > bestL) {
                            bestL = side;
                            bestX = lx;
                            bestY = lastY;
                        }
                        lastY = t.y;
                    }
                }

                int emptyHeight = H - lastY;
                if (emptyHeight > 0) {
                    int side = min(ideal_width, emptyHeight);
                    if (side > bestL) {
                        bestL = side;
                        bestX = lx;
                        bestY = lastY;
                    }
                }
            }
        }
        cout << bestX << " " << bestY << " " << bestL;
        if (T)
            cout << "\n\n";
    }
}
