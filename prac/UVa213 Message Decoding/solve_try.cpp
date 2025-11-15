#include <bits/stdc++.h>
using namespace std;

char get_char(const string& s, int code, int L) {
    if (L == 1) {
        return s[0];
    }
    return s[(1 << L) - 1 - L + code];
}

int get_bin(int num) {
    int dec = 0;
    int count = 0;
    while (count < num) {
        char bit;
        cin.get(bit);
        if (bit == '\n') {
            continue;
        }
        dec += ((bit - '0') << (num - 1 - count));
        count++;
    }
    return dec;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string symbols;
    while (getline(cin, symbols)) {
        if (symbols.empty()) {
            continue;
        }
        while (true) {
            int head_3 = get_bin(3);
            if (head_3 == 0) {
                cout << endl;
                break;
            }
            int L = head_3;
            int code;
            while (true) {
                code = get_bin(L);
                if (code == (1 << L) - 1) {
                    break;
                }

                cout << get_char(symbols, code, L);
            }
        }
    }
}
