// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=4490
// UVa1615 Highway
#include <bits/stdc++.h>
using namespace std;

struct Interval {
    double l, r;
};

struct ByRight {
    bool operator()(const Interval& a, const Interval& b) const {
        if (a.r != b.r)
            return a.r < b.r; // 先按右端点
        return a.l < b.l;     // 右端点相同，再按左端点
    }
};

int L;
long long D;
int n;

set<Interval, ByRight> intervals;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> L) {
        intervals.clear();
        cin >> D;
        cin >> n;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;

            double lx = x - sqrt(D * D - y * y);
            double rx = x + sqrt(D * D - y * y);
            if (lx < 1e-8) {
                lx = 0;
            }
            if (rx - L > -1e-8) {
                rx = L;
            }
            auto itvl = Interval{lx, rx};
            for (auto& i : intervals) {
                if (lx - i.r > 1e-8) {
                    intervals.insert(itvl);
                    break;
                }
                if(rx -i.l < -1e-8) {
                    intervals.insert(itvl);
                    break;
                }else if( i.r - rx > -1e-8 && i.l - lx < 1e-8) {
                    // 包含
                    itvl.l = i.l;
                } else if( i.r - rx < -1e-8 && i.l - lx > 1e-8) {
                    // 被包含
                    itvl.r = i.r;
                } else if( i.r - rx < -1e-8 && i.l - lx < 1e-8 && i.r - lx > -1e-8) {
                    // 左交
                    itvl.l = i.l;
                } else if( i.r - rx > -1e-8 && i.l - lx > 1e-8 && i.l - rx < 1e-8) {
                    // 右交
                    itvl.r = i.r;
                    
                }
            }
        }
    }
}
