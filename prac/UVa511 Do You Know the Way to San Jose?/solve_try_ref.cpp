// trick 1 按段解析输入
// trick 2 EPS 比较浮点数


#include <bits/stdc++.h>
using namespace std;

struct Pos {
    long double x{};
    long double y{};
};

struct MapInfo {
    string name;
    long double minx{};
    long double maxx{};
    long double miny{};
    long double maxy{};
    long double area{};
    long double centerx{};
    long double centery{};
    long double aspect{};
    long double lowerRightX{};
    long double lowerRightY{};
    long double minCornerX{};
};

struct Request {
    string name;
    int detail{};
};

constexpr long double WINDOW_RATIO = 0.75L;
constexpr long double EPS = 1e-9L;

long double square(long double v) { return v * v; }

bool contains(const MapInfo& m, const Pos& p) {
    return p.x >= m.minx - EPS && p.x <= m.maxx + EPS && p.y >= m.miny - EPS && p.y <= m.maxy + EPS;
}

int compareMaps(const MapInfo& a, const MapInfo& b, const Pos& loc) {
    long double distCenterA = square(loc.x - a.centerx) + square(loc.y - a.centery);
    long double distCenterB = square(loc.x - b.centerx) + square(loc.y - b.centery);
    if (fabsl(distCenterA - distCenterB) > EPS) return distCenterA < distCenterB ? -1 : 1;

    long double aspectDiffA = fabsl(a.aspect - WINDOW_RATIO);
    long double aspectDiffB = fabsl(b.aspect - WINDOW_RATIO);
    if (fabsl(aspectDiffA - aspectDiffB) > EPS) return aspectDiffA < aspectDiffB ? -1 : 1;

    long double distLowerRightA =
        square(loc.x - a.lowerRightX) + square(loc.y - a.lowerRightY);
    long double distLowerRightB =
        square(loc.x - b.lowerRightX) + square(loc.y - b.lowerRightY);
    if (fabsl(distLowerRightA - distLowerRightB) > EPS) return distLowerRightA > distLowerRightB ? -1 : 1;

    if (fabsl(a.minCornerX - b.minCornerX) > EPS) return a.minCornerX < b.minCornerX ? -1 : 1;

    if (a.name == b.name) return 0;
    return a.name < b.name ? -1 : 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<MapInfo> maps;
    unordered_map<string, Pos> locations;
    vector<Request> requests;

    string line;
    string section;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (line == "MAPS" || line == "LOCATIONS" || line == "REQUESTS" || line == "END") {
            section = line;
            if (section == "END") break;
            continue;
        }
        istringstream iss(line);
        if (section == "MAPS") {
            string name;
            long double x1, y1, x2, y2;
            iss >> name >> x1 >> y1 >> x2 >> y2;
            long double minx = min(x1, x2);
            long double maxx = max(x1, x2);
            long double miny = min(y1, y2);
            long double maxy = max(y1, y2);
            long double width = maxx - minx;
            long double height = maxy - miny;
            MapInfo info;
            info.name = name;
            info.minx = minx;
            info.maxx = maxx;
            info.miny = miny;
            info.maxy = maxy;
            info.area = fabsl(width * height);
            info.centerx = (minx + maxx) / 2.0L;
            info.centery = (miny + maxy) / 2.0L;
            info.aspect = (fabsl(width) < EPS) ? numeric_limits<long double>::infinity()
                                               : fabsl(height) / fabsl(width);
            info.lowerRightX = maxx;
            info.lowerRightY = miny;
            info.minCornerX = minx;
            maps.push_back(info);
        } else if (section == "LOCATIONS") {
            string name;
            long double x, y;
            iss >> name >> x >> y;
            locations[name] = {x, y};
        } else if (section == "REQUESTS") {
            string name;
            int detail;
            iss >> name >> detail;
            requests.push_back({name, detail});
        }
    }

    struct AreaGroup {
        long double area;
        const MapInfo* bestMap;
    };

    for (const auto& req : requests) {
        cout << req.name << " at detail level " << req.detail << ' ';
        auto locIt = locations.find(req.name);
        if (locIt == locations.end()) {
            cout << "unknown location\n";
            continue;
        }
        const Pos& loc = locIt->second;

        vector<AreaGroup> groups;
        for (const auto& m : maps) {
            if (!contains(m, loc)) continue;
            bool matched = false;
            for (auto& g : groups) {
                if (fabsl(g.area - m.area) <= EPS) {
                    if (compareMaps(m, *g.bestMap, loc) < 0) g.bestMap = &m;
                    matched = true;
                    break;
                }
            }
            if (!matched) groups.push_back({m.area, &m});
        }

        if (groups.empty()) {
            cout << "no map contains that location\n";
            continue;
        }

        sort(groups.begin(), groups.end(), [](const AreaGroup& a, const AreaGroup& b) {
            if (fabsl(a.area - b.area) > EPS) return a.area > b.area;
            return a.bestMap->name < b.bestMap->name;
        });

        if (req.detail <= static_cast<int>(groups.size())) {
            cout << "using " << groups[req.detail - 1].bestMap->name << "\n";
        } else {
            cout << "no map at that detail level; using " << groups.back().bestMap->name << "\n";
        }
    }
}
