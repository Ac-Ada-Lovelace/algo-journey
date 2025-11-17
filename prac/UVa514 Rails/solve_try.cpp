#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        int n;
        cin >> n;
        if (n == 0) {
            break;
        }
        cin.ignore();
        while (true) {
            string line;
            getline(cin, line);
            if (line == "0")
                break;
            vector<int> out_seq;

            stringstream ss(line);
            int x;
            while (ss >> x) {
                out_seq.push_back(x);
            }

            int curr = 1;
            stack<int> station;
            station.push(curr);
            curr++;
            while (!out_seq.empty()) {
                if (station.empty() || station.top() != out_seq.front()) {
                    if (curr > n) {
                        break;
                    }
                    station.push(curr);
                    curr++;
                } else {
                    station.pop();
                    out_seq.erase(out_seq.begin());
                }
            }
            if (out_seq.empty()) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }

        cout << endl;
    }
}
