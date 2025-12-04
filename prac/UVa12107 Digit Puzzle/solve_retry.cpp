#include <bits/stdc++.h>
#include <stdexcept>
using namespace std;

char xyz[8];
int starts[3] = {0, 2, 4};
int len[3];

bool calc() {
    int x = stoi(string(xyz, 0, 2));
    int y = stoi(string(xyz, 2, 2));

    int count = 0;
    // +
    int _z = x + y;
    string sz = to_string(_z);
    int flag = false;
    if (sz.size() == len[2]) {
        for (int i = 0; i < len[2]; i++) {
            if (xyz[4 + i] != '*' && xyz[4 + i] != sz[i]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            count++;
        }
    }

    // -
    _z = x - y;
    sz = to_string(_z);

    if (sz.size() == len[2]) {
        for (int i = 0; i < len[2]; i++) {
            if (xyz[4 + i] != '*' && xyz[4 + i] != sz[i]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            count++;
        }
    }
    // *
    _z = x * y;
    sz = to_string(_z);

    if (sz.size() == len[2]) {
        for (int i = 0; i < len[2]; i++) {
            if (xyz[4 + i] != '*' && xyz[4 + i] != sz[i]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            count++;
        }
    }

    return count == 1;
}
bool is_good(int c, int pos) {
    if (pos == starts[c + 1]) {
        c++;
    }

    if (c == 3) {
        return calc();
    }
    int can_be_zero = true;
    if (pos == starts[c]) {
        can_be_zero = false;
    }
    if (isdigit(xyz[pos])) {
        return is_good(c, pos + 1);
    }
    for (int i = can_be_zero ? 0 : 1; i <= 9; i++) {
        xyz[pos] = '0' + i;
        if (is_good(c, pos + 1)) {
            return true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
