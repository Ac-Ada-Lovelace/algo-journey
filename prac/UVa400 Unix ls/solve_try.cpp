#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int file_num;
    while (cin >> file_num) {
        vector<string> files;
        int max_len = 0;
        int N = file_num;
        while (file_num--) {
            string file_name;
            cin >> file_name;
            files.push_back(file_name);
            if (file_name.length() > max_len) {
                max_len = file_name.length();
            }
        }

        int C = floor((60 + 2) / (max_len + 2));
        int R = ceil(N / C);
        vector<vector<string>> files_by_line(C);
        for (auto &v : files_by_line) {
            v.resize(R);
        }
        for (int i = 0; i < N; i++) {
            int col = i / R;
            int row = i % R;
            files_by_line[col][row] = files[i];
        }

        cout << "------------------------------------------------------------" << endl;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (files_by_line[c][r] == "") {
                    continue;
                }
                cout << files_by_line[c][r];
                if (c != C - 1) {
                    cout << string(max_len - files_by_line[c][r].length() + 2, ' ');
                }
            }
            cout << endl;
        }
    }
}
