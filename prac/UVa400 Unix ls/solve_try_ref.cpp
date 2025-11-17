#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<string> files(n);
        int maxLen = 0;
        for (int i = 0; i < n; ++i) {
            cin >> files[i];
            maxLen = max(maxLen, (int)files[i].size());
        }
        sort(files.begin(), files.end());

        int cols = max(1, (60 - maxLen) / (maxLen + 2) + 1);
        int rows = (n + cols - 1) / cols;

        cout << string(60, '-') << "\n";
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int idx = c * rows + r;
                if (idx >= n)
                    continue;
                cout << left << setw(c == cols - 1 ? maxLen : maxLen + 2) << files[idx];
            }
            cout << "\n";
        }
    }
    return 0;
}
