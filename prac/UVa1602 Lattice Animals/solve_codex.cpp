#include <bits/stdc++.h>
using namespace std;

// Generate all free polyominoes up to size 10, then count how many of size n
// can fit inside a given w x h rectangle (rotations/reflections allowed).

struct Poly {
    vector<pair<int, int>> cells;            // canonical orientation
    vector<pair<int, int>> orientation_dims; // unique (width, height) pairs
};

// Normalize: shift to min x,y = 0 and sort.
string normalize(vector<pair<int, int>>& pts) {
    int minx = INT_MAX, miny = INT_MAX;
    for (auto [x, y] : pts) {
        minx = min(minx, x);
        miny = min(miny, y);
    }
    for (auto& p : pts) {
        p.first -= minx;
        p.second -= miny;
    }
    sort(pts.begin(), pts.end());
    string s;
    s.reserve(pts.size() * 8);
    for (auto [x, y] : pts) {
        s += to_string(x);
        s.push_back(',');
        s += to_string(y);
        s.push_back(';');
    }
    return s;
}

vector<pair<int, int>> transform(const vector<pair<int, int>>& pts, int t) {
    // t: 0..3 rotations, 4..7 rotations after reflection over y-axis.
    vector<pair<int, int>> res;
    res.reserve(pts.size());
    bool reflect = t >= 4;
    int rot = t % 4;
    for (auto [x, y] : pts) {
        if (reflect)
            x = -x;
        int rx, ry;
        if (rot == 0) {
            rx = x, ry = y;
        } else if (rot == 1) {
            rx = y, ry = -x;
        } else if (rot == 2) {
            rx = -x, ry = -y;
        } else {
            rx = -y, ry = x;
        }
        res.push_back({rx, ry});
    }
    return res;
}

string canonical(const vector<pair<int, int>>& pts) {
    string best;
    bool first = true;
    for (int t = 0; t < 8; ++t) {
        auto v = transform(pts, t);
        string s = normalize(v);
        if (first || s < best) {
            best = std::move(s);
            first = false;
        }
    }
    return best;
}

vector<Poly> polys[11];
int fitCount[11][11][11]; // fitCount[n][w][h]

void generatePolys() {
    vector<pair<int, int>> base{{0, 0}};
    polys[1].push_back({base, {{1, 1}}});
    for (int sz = 1; sz < 10; ++sz) {
        unordered_set<string> seen;
        vector<Poly> next;
        for (auto& p : polys[sz]) {
            unordered_set<long long> occupied;
            for (auto [x, y] : p.cells) {
                occupied.insert(((long long)x << 32) ^ (unsigned long long)(y));
            }
            const int dx[4] = {1, -1, 0, 0};
            const int dy[4] = {0, 0, 1, -1};
            for (auto [x, y] : p.cells) {
                for (int d = 0; d < 4; ++d) {
                    int nx = x + dx[d], ny = y + dy[d];
                    long long key =
                        ((long long)nx << 32) ^ (unsigned long long)(ny);
                    if (occupied.count(key))
                        continue;
                    vector<pair<int, int>> q = p.cells;
                    q.push_back({nx, ny});
                    string can = canonical(q);
                    if (seen.insert(can).second) {
                        // Compute unique orientation dimensions.
                        vector<pair<int, int>> dims;
                        unordered_set<long long> dimSeen;
                        for (int t = 0; t < 8; ++t) {
                            auto v = transform(q, t);
                            string tmp = normalize(v); // normalize modifies v
                            (void)tmp;
                            int maxx = 0, maxy = 0;
                            for (auto [ux, uy] : v) {
                                maxx = max(maxx, ux);
                                maxy = max(maxy, uy);
                            }
                            int w = maxx + 1, h = maxy + 1;
                            long long dh =
                                ((long long)w << 32) ^ (unsigned long long)h;
                            if (dimSeen.insert(dh).second)
                                dims.push_back({w, h});
                        }
                        next.push_back({q, dims});
                    }
                }
            }
        }
        polys[sz + 1] = std::move(next);
    }
}

void precomputeFits() {
    memset(fitCount, 0, sizeof fitCount);
    for (int n = 1; n <= 10; ++n) {
        for (auto& p : polys[n]) {
            bool ok[11][11] = {};
            for (auto [w, h] : p.orientation_dims) {
                for (int W = w; W <= 10; ++W) {
                    for (int H = h; H <= 10; ++H) {
                        ok[W][H] = true; // fits with this orientation
                    }
                }
            }
            for (int W = 1; W <= 10; ++W) {
                for (int H = 1; H <= 10; ++H) {
                    if (ok[W][H])
                        ++fitCount[n][W][H];
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    generatePolys();
    precomputeFits();

    int n, w, h;
    while (cin >> n >> w >> h) {
        cout << fitCount[n][w][h] << '\n';
    }
    return 0;
}
