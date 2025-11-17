#include <bits/stdc++.h>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n;
    while (cin >> n) {
        if (n == 0) {
            break;
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            q.push(i);
        }
        cout << "Discarded cards:";
        int flag = 0;
        while (q.size() > 1) {
            if (flag) {
                cout << ",";
            }
            auto c = q.front();
            q.pop();
            cout << " " << c;
            auto nc = q.front();
            q.pop();
            q.push(nc);
            flag = 1;
        }
        cout << endl;
        cout << "Remaining card: " << q.front() << "\n";
    }
}
