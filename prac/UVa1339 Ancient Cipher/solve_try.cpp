#include <bits/stdc++.h>
using namespace std;

int freq_a[26];
int freq_b[26];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2;
    while (cin >> s1 >> s2) {
        for (int i = 0; i < s1.size(); i++) {
            freq_a[s1[i] - 'A']++;
            freq_b[s2[i] - 'A']++;
        }

        sort(freq_a, freq_a + 26);
        sort(freq_b, freq_b + 26);
        int flag = 0;
        for (int i = 0; i < 26; i++) {
            if (freq_a[i] != freq_b[i]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        memset(freq_a, 0, sizeof(freq_a));
        memset(freq_b, 0, sizeof(freq_b));
    }
    return 0;
}
