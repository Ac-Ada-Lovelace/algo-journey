// UVa1347 - Tour
// Bitonic tour DP on points sorted by x-coordinate.
#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    while (cin >> n) {
        vector<Point> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i].x >> p[i].y;
        }

        if (n == 2) {
            double ans = 2.0 * dist(p[0], p[1]);
            cout << fixed << setprecision(2) << ans << "\n";
            continue;
        }

        vector<vector<double>> dp(n, vector<double>(n, 1e100));
        dp[0][1] = dist(p[0], p[1]);

        for (int j = 2; j < n; j++) {
            // cases where i < j-1
            for (int i = 0; i < j - 1; i++) {
                dp[i][j] = dp[i][j - 1] + dist(p[j - 1], p[j]);
            }
            // case i == j-1
            double best = 1e100;
            for (int k = 0; k < j - 1; k++) {
                best = min(best, dp[k][j - 1] + dist(p[k], p[j]));
            }
            dp[j - 1][j] = best;
        }

        double ans = dp[n - 2][n - 1] + dist(p[n - 2], p[n - 1]);
        cout << fixed << setprecision(2) << ans << "\n";
    }

    return 0;
}
