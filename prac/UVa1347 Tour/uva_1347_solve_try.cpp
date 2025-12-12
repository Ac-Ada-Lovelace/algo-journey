// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=847&page=show_problem&problem=4093
// UVa1347 Tour
#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;

    point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator<(const point& other) const {
        return x < other.x;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        sort(points.begin(), points.end());
    }
}
