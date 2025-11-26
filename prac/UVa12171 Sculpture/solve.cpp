#include <bits/stdc++.h>
using namespace std;

struct Box {
  int x0, y0, z0, x, y, z;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  if (!(cin >> T)) return 0;
  while (T--) {
    int n;
    cin >> n;
    vector<Box> boxes;
    boxes.reserve(n);

    vector<int> xs = {0, 1001};
    vector<int> ys = {0, 1001};
    vector<int> zs = {0, 1001};

    for (int i = 0; i < n; ++i) {
      Box b;
      cin >> b.x0 >> b.y0 >> b.z0 >> b.x >> b.y >> b.z;
      boxes.push_back(b);
      xs.push_back(b.x0);
      xs.push_back(b.x0 + b.x);
      ys.push_back(b.y0);
      ys.push_back(b.y0 + b.y);
      zs.push_back(b.z0);
      zs.push_back(b.z0 + b.z);
    }

    auto prepare = [](vector<int>& coord) {
      sort(coord.begin(), coord.end());
      coord.erase(unique(coord.begin(), coord.end()), coord.end());
    };

    prepare(xs);
    prepare(ys);
    prepare(zs);

    const int nx = xs.size() - 1;
    const int ny = ys.size() - 1;
    const int nz = zs.size() - 1;
    const int total_cells = nx * ny * nz;

    auto idx = [ny, nz](int i, int j, int k) {
      return (i * ny + j) * nz + k;
    };

    vector<char> solid(total_cells, 0);
    vector<long long> dx(nx), dy(ny), dz(nz);
    for (int i = 0; i < nx; ++i) dx[i] = xs[i + 1] - xs[i];
    for (int j = 0; j < ny; ++j) dy[j] = ys[j + 1] - ys[j];
    for (int k = 0; k < nz; ++k) dz[k] = zs[k + 1] - zs[k];

    auto locate = [](const vector<int>& coord, int v) {
      return int(lower_bound(coord.begin(), coord.end(), v) - coord.begin());
    };

    for (const auto& b : boxes) {
      int xi = locate(xs, b.x0);
      int xj = locate(xs, b.x0 + b.x);
      int yi = locate(ys, b.y0);
      int yj = locate(ys, b.y0 + b.y);
      int zi = locate(zs, b.z0);
      int zj = locate(zs, b.z0 + b.z);
      for (int i = xi; i < xj; ++i) {
        for (int j = yi; j < yj; ++j) {
          for (int k = zi; k < zj; ++k) {
            solid[idx(i, j, k)] = 1;
          }
        }
      }
    }

    vector<char> visited(total_cells, 0);
    queue<tuple<int, int, int>> q;

    auto push_if_outside = [&](int i, int j, int k) {
      int id = idx(i, j, k);
      if (!solid[id] && !visited[id]) {
        visited[id] = 1;
        q.emplace(i, j, k);
      }
    };

    for (int i = 0; i < nx; ++i) {
      for (int j = 0; j < ny; ++j) {
        push_if_outside(i, j, 0);
        push_if_outside(i, j, nz - 1);
      }
    }
    for (int i = 0; i < nx; ++i) {
      for (int k = 0; k < nz; ++k) {
        push_if_outside(i, 0, k);
        push_if_outside(i, ny - 1, k);
      }
    }
    for (int j = 0; j < ny; ++j) {
      for (int k = 0; k < nz; ++k) {
        push_if_outside(0, j, k);
        push_if_outside(nx - 1, j, k);
      }
    }

    const int di[6] = {1, -1, 0, 0, 0, 0};
    const int dj[6] = {0, 0, 1, -1, 0, 0};
    const int dk[6] = {0, 0, 0, 0, 1, -1};

    long long area = 0;
    while (!q.empty()) {
      auto [i, j, k] = q.front();
      q.pop();
      for (int dir = 0; dir < 6; ++dir) {
        int ni = i + di[dir];
        int nj = j + dj[dir];
        int nk = k + dk[dir];
        if (ni < 0 || nj < 0 || nk < 0 || ni >= nx || nj >= ny || nk >= nz) continue;
        int nid = idx(ni, nj, nk);
        if (solid[nid]) {
          if (dir < 2) {
            area += dy[j] * dz[k];
          } else if (dir < 4) {
            area += dx[i] * dz[k];
          } else {
            area += dx[i] * dy[j];
          }
        } else if (!visited[nid]) {
          visited[nid] = 1;
          q.emplace(ni, nj, nk);
        }
      }
    }

    long long volume = 0;
    for (int i = 0; i < nx; ++i) {
      for (int j = 0; j < ny; ++j) {
        for (int k = 0; k < nz; ++k) {
          long long cell_volume = dx[i] * 1LL * dy[j] * dz[k];
          int id = idx(i, j, k);
          if (solid[id] || !visited[id]) {
            volume += cell_volume;
          }
        }
      }
    }

    cout << area << ' ' << volume << "\n";
  }
  return 0;
}
