// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=842&page=show_problem&problem=3004
// UVa11882 Biggest Number
#include <bits/stdc++.h>
using namespace std;
#define MAX_N 16

// a<b : false  a>b : true
bool compare(const int* a, int lena, const int* b, int lenb) {
    if (lena != lenb) {
        return lena > lenb;
    }

    for (int i = 0; i < lena; i++) {
        if (a[i] != b[i]) {
            return a[i] > b[i];
        }
    }
}

int grid[MAX_N][MAX_N];
int c, r;
vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int* maxn = (int*)malloc(sizeof(int) * (MAX_N * MAX_N));
int len = 0;

int* nums = (int*)malloc(sizeof(int) * (MAX_N * MAX_N));
int* used = (int*)malloc(sizeof(int) * (MAX_N * MAX_N));
int num_count = 0;

int* ideal = (int*)malloc(sizeof(int) * (MAX_N * MAX_N));
int dfs(int x, int y, int* current, int current_len) {
    memset(ideal, 0, sizeof(int) * (MAX_N * MAX_N));
    memcpy(ideal, current, sizeof(int) * current_len);
    memcpy(ideal + current_len, nums, sizeof(int) * (num_count));
    if (compare(maxn, len, ideal, current_len + num_count)) {
        return 0;
    }

    int ps = 0;
    for (auto d : directions) {
        int dx = d.first;
        int dy = d.second;
        int nx = x + dx;
        int ny = y + dy;
        if (nx < 1 || nx > r || ny < 1 || ny > c)
            continue;
        if (grid[nx][ny] == -1)
            continue;

        ps++;
        current[current_len] = grid[nx][ny];
        current_len++;
        if (compare(current, current_len, maxn, len)) {
            memcpy(maxn, current, sizeof(int) * current_len);
            len = current_len;
        }
        dfs(nx, ny, current, current_len + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> r >> c;
        if (r == 0 && c == 0)
            break;

        memset(grid, -1, sizeof(grid));
        memset(maxn, 0, sizeof(int) * (MAX_N * MAX_N));
        memset(nums, 0, sizeof(int) * (MAX_N * MAX_N));
        num_count = 0;
        len = 0;

        for (int i = 1; i <= r; i++) {
            getline(cin, line);
            for (int j = 1; j <= c; j++) {
                if (isdigit(line[j - 1]) == 0) {
                    grid[i][j] = line[j - 1] - '0';
                    nums[num_count] = grid[i][j];
                    num_count++;
                }
            }
        }

        sort(nums, nums + num_count, greater<int>());

        int* initial = (int*)malloc(sizeof(int) * (MAX_N * MAX_N));
        dfs(1, 1, initial, 0);

        for (int i = 0; i < len; i++) {
            cout << maxn[i];
        }
        cout << endl;
    }
}
