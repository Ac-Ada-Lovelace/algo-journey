// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=847&page=show_problem&problem=4500
// UVa1625 Color Length
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s1, s2;
        cin >> s1 >> s2;

        array<int, 26> cnt1{}, cnt2{};

        vector<array<int, 26>> rem1(s1.size() + 1), rem2(s2.size() + 1);

        for (int i = (int)s1.size() - 1; i >= 0; --i) {
            cnt1[s1[i] - 'a']++;
            rem1[i] = cnt1;
        }
        for (int i = (int)s2.size() - 1; i >= 0; --i) {
            cnt2[s2[i] - 'a']++;
            rem2[i] = cnt2;
        }

    }
}
