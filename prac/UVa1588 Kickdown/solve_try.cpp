#include <bits/stdc++.h>
using namespace std;

bool _xor(int* a, int len_a, int* b, int len_b, int offset) {
    bool flag = false;
    for (int i = 0; i < len_a; i++) {
        if (!a[i] || !b[offset + i])
            continue;
        flag = true;
    }

    return flag;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        string s1, s2;
        cin >> s1;
        cin >> s2;
        if (s1.size() == 0) {
            break;
        }

        int *shoter, *longer;
        if (s1.size() > s2.size()) {
            swap(s1, s2);
        }
        shoter = new int[s1.size()];
        longer = new int[s2.size()];
        for (int i = 0; i < s1.size(); i++) {
            shoter[i] = (s1[i] - '1');
        }
        for (int i = 0; i < s2.size(); i++) {
            longer[i] = (s2[i] - '1');
        }
        for (int i = 0; i < s2.size(); i++) {
            if (!_xor(shoter, s1.size(), longer, s2.size(), i)) {
                cout << max(i + (int)s1.size(), (int)s2.size()) << endl;
                break;
            }
        }
    }
}
