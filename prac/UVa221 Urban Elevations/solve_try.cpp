// https://onlinejudge.org/external/2/221.pdf
#include <bits/stdc++.h>
using namespace std;

struct Building {
    int id;
    double x, y, w, d, h;
};

constexpr double EPS = 1e-8;

bool covers(double mid, const Building& b) {
    return mid > b.x - EPS && mid < b.x + b.w + EPS;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int map_id = 1;
    while (cin >> n) {
        if (n == 0) break;

        vector<Building> buildings;
        buildings.reserve(n);
        vector<double> xs;
        xs.reserve(2 * n);

        for (int i = 0; i < n; i++) {
            double x, y, w, d, h;
            cin >> x >> y >> w >> d >> h;
            buildings.push_back(Building{i + 1, x, y, w, d, h});
            xs.push_back(x);
            xs.push_back(x + w);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end(), [](double a, double b) {
                     return fabs(a - b) < EPS;
                 }),
                 xs.end());

        vector<int> visible;
        visible.reserve(n);
        for (const auto& b : buildings) {
            bool vis = false;
            for (size_t i = 0; i + 1 < xs.size() && !vis; i++) {
                double left = xs[i];
                double right = xs[i + 1];
                if (right - left < EPS) continue;
                double mid = (left + right) / 2.0;
                if (!covers(mid, b)) continue;

                bool blocked = false;
                for (const auto& other : buildings) {
                    if (other.id == b.id) continue;
                    if (!covers(mid, other)) continue;
                    if (other.y + EPS < b.y && other.h >= b.h - EPS) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) vis = true;
            }
            if (vis) visible.push_back(b.id);
        }

        sort(visible.begin(), visible.end(), [&](int lhs, int rhs) {
            const Building& a = buildings[lhs - 1];
            const Building& b = buildings[rhs - 1];
            if (fabs(a.x - b.x) > EPS) return a.x < b.x;
            if (fabs(a.y - b.y) > EPS) return a.y < b.y;
            return lhs < rhs;
        });

        if (map_id > 1) cout << "\n";
        cout << "For map #" << map_id << ", the visible buildings are numbered as follows:\n";
        for (size_t i = 0; i < visible.size(); i++) {
            if (i) cout << ' ';
            cout << visible[i];
        }
        cout << "\n";
        map_id++;
    }
    return 0;
}
