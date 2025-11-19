#include <bits/stdc++.h>
using namespace std;

namespace {
const int DR[4] = {1, -1, 0, 0};
const int DC[4] = {0, 0, 1, -1};

void fillWhite(int sr, int sc, vector<vector<int>>& visited, const vector<vector<int>>& img) {
    int h = img.size();
    int w = img[0].size();
    queue<pair<int, int>> q;
    q.push({sr, sc});
    visited[sr][sc] = 1;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d];
            int nc = c + DC[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w)
                continue;
            if (img[nr][nc] == 0 && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }
}

int exploreBlack(int sr, int sc, vector<vector<int>>& blackVisited,
                 vector<vector<int>>& whiteVisited, const vector<vector<int>>& img) {
    int h = img.size();
    int w = img[0].size();
    queue<pair<int, int>> q;
    q.push({sr, sc});
    blackVisited[sr][sc] = 1;
    int holes = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d];
            int nc = c + DC[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w)
                continue;
            if (img[nr][nc] == 1 && !blackVisited[nr][nc]) {
                blackVisited[nr][nc] = 1;
                q.push({nr, nc});
            } else if (img[nr][nc] == 0 && !whiteVisited[nr][nc]) {
                ++holes;
                fillWhite(nr, nc, whiteVisited, img);
            }
        }
    }
    return holes;
}

char classifyGlyph(int holes) {
    switch (holes) {
        case 0:
            return 'W';
        case 1:
            return 'A';
        case 2:
            return 'K';
        case 3:
            return 'J';
        case 4:
            return 'S';
        case 5:
            return 'D';
        default:
            return '?';
    }
}

int hexValue(char ch) {
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    return 10 + (ch - 'a');
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    int caseNo = 1;
    while (cin >> H >> W) {
        if (H == 0 && W == 0)
            break;
        int width = W * 4;
        vector<vector<int>> img(H + 2, vector<int>(width + 2, 0));
        for (int r = 0; r < H; ++r) {
            string line;
            cin >> line;
            for (int c = 0; c < W; ++c) {
                int val = hexValue(line[c]);
                for (int k = 0; k < 4; ++k) {
                    int bit = (val >> (3 - k)) & 1;
                    img[r + 1][c * 4 + k + 1] = bit;
                }
            }
        }

        vector<vector<int>> whiteVisited(img.size(), vector<int>(img[0].size(), 0));
        vector<vector<int>> blackVisited(img.size(), vector<int>(img[0].size(), 0));

        fillWhite(0, 0, whiteVisited, img);

        vector<char> glyphs;
        for (int r = 0; r < static_cast<int>(img.size()); ++r) {
            for (int c = 0; c < static_cast<int>(img[0].size()); ++c) {
                if (img[r][c] == 1 && !blackVisited[r][c]) {
                    int holes = exploreBlack(r, c, blackVisited, whiteVisited, img);
                    glyphs.push_back(classifyGlyph(holes));
                }
            }
        }

        sort(glyphs.begin(), glyphs.end());
        cout << "Case " << caseNo++ << ": ";
        for (char ch : glyphs)
            cout << ch;
        cout << "\n";
    }
    return 0;
}
