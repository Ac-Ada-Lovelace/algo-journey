#include <bits/stdc++.h>
using namespace std;

int min_start(const char str[], int start_a, int start_b, int len) {
    for (int i = 0; i < len; i++) {
        if (str[(start_a + i) % len] != str[(start_b + i) % len]) {
            return str[(start_a + i) % len] < str[(start_b + i) % len] ? start_a : start_b;
        }
    }
    return -1;
}

int disp(const char str[], int start, int len) {
    for (int i = 0; i < len; i++) {
        cout << str[(start + i) % len];
    }
    cout << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    if (!(cin >> cases))
        return 0;
    string seq;
    while (cases--) {
        cin >> seq;
        int min_index = 0;
        for (int i = 1; i < seq.size(); i++) {
            int res = min_start(seq.data(), min_index, i, seq.size());
            if (res != -1) {
                min_index = res;
            }
        }
        disp(seq.data(), min_index, seq.size());
    }
}
