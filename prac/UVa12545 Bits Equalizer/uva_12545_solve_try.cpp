// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=3990
// UVa12545 Bits Equalizer
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string s1, s2;
        cin >> s1 >> s2;

        int A = 0, B = 0, C = 0, D = 0;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] == '0' && s2[i] == '0') {
                continue;
            } else if (s1[i] == '1' && s2[i] == '0') {
                A++;
            } else if (s1[i] == '0' && s2[i] == '1') {
                B++;
            } else if (s1[i] == '?' && s2[i] == '1') {
                C++;
            } else if (s1[i] == '?' && s2[i] == '0') {
                D++;
            }
        }
        int ans = 0;
        int imp = 0;
        if (B > A) {
            ans += A;
            B = B - A;
            A = 0;
            if (B > D) {
                ans += D;
                B = B - D;
                D = 0;
            } else {
                ans += B;
                D = D - B;
                B = 0;
            }
            ans += B + C + D;
        } else {
            ans += B;
            A = A - B;
            B = 0;
            if (A > C) {
                imp = 1;

            } else {
                ans += C + D;
            }
        }


        if (imp) {
            cout << "Solve " << t << ": " << -1 << '\n';
        } else {
            cout << "Solve " << t << ": " << ans << '\n';
        }
    }
}
