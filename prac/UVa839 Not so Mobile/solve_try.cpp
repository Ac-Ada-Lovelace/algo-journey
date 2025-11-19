#include <bits/stdc++.h>
using namespace std;

array<int, 4> parse_line(const string& line) {
    array<int, 4> args;
    stringstream ss(line);
    string token;
    int index = 0;
    while (getline(ss, token, ' ')) {
        if (token.empty())
            continue;
        args[index++] = stoi(token);
    }
    return args;
}
int get_weight(array<int, 4> args) {
    int wl = args[0];
    int dl = args[1];
    int wr = args[2];
    int dr = args[3];
    if (wl == 0) {
        string line;
        getline(cin, line);
        args = parse_line(line);
        wl = get_weight(args);
    }
    if (wr == 0) {
        string line;
        getline(cin, line);

        args = parse_line(line);
        wr = get_weight(args);
    }

    if (wl == -1 || wr == -1) {
        return -1;
    }
    if (wl * dl == wr * dr) {
        return wl + wr;
    } else {
        return -1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    cin.ignore();
    int flag = 0;
    while (cases--) {
        if(flag)
        cout << endl;
        cin.ignore();
        string line;
        getline(cin, line); // consume newline
        auto args = parse_line(line);
        if (get_weight(args) != -1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        flag = 1;
    }
}
