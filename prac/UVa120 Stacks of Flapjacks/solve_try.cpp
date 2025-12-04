// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=98&page=show_problem&problem=56
// UVa120 Stacks of Flapjacks
#include <bits/stdc++.h>
using namespace std;

array<int, 31> pan;
int n = 1;
int flipped = 1;

void flip(int k) {
    // reverse all after index k;
    for (int i = k, j = n; i < j; i++, j--) {
        swap(pan[i], pan[j]);
    }
}

int check() {
    int flag = 0;
    for (int i = 1; i < n; i++) {
        if (pan[i] < pan[i + 1]) {
            flag = 1;
        }
    }
    return flag;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string line;
    while (getline(cin, line)) {
        n = 0;
        flipped = 1;

        int p;
        stringstream ss(line);
        while (ss >> p) {
            n++;
            pan[n] = p;
        }

        array<int, 31> _pan(pan);
        sort(_pan.begin() + 1, _pan.begin() + n);
        vector<int> res;

        for (int i = 1; i <= n; i++) {
            int target = _pan[i];
            if (check() == 0) {
                break;
            }
            if (pan[i] != target) {
                
                int idx = 0;
                for (int j = i; j <= n; j++) {
                    if (pan[j] == target) {
                        idx = j;
                        break;
                    }
                }

                if (idx != n) { // 如果不在顶部
                    flip(idx);
                    res.push_back(idx); // 转换为题目要求的位置编号
                }
                flip(i);
                res.push_back(i); // 转换为题目要求的位置编号
            }
        }

        cout << "----------------" << endl;
        for (int i = 1; i <= n; i++) {
            if (i > 1) {
                cout << " ";
            }
            cout << pan[i];
        }
        cout << endl;

        for (int i = 0; i < res.size(); i++) {
            if (i > 0)
                cout << " ";
            cout << res[i];
        }
        cout << " " << 0 << endl;
        cout << "----------------" << endl;
    }
}
