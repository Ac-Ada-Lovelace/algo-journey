#include <bits/stdc++.h>
using namespace std;

string formatFive(int value) {
    string s = to_string(value);
    if (s.size() < 5)
        s = string(5 - s.size(), '0') + s;
    return s;
}

bool usesAllDigits(const string& top, const string& bottom) {
    int mask = 0;
    for (char c : top) {
        int d = c - '0';
        if (mask & (1 << d))
            return false;
        mask |= 1 << d;
    }
    for (char c : bottom) {
        int d = c - '0';
        if (mask & (1 << d))
            return false;
        mask |= 1 << d;
    }
    return mask == (1 << 10) - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    bool firstCase = true;
    while (cin >> n && n) {
        if (!firstCase)
            cout << "\n";
        firstCase = false;

        vector<pair<int, int>> solutions;
        for (int denominator = 1234; denominator <= 98765; ++denominator) {
            int numerator = denominator * n;
            if (numerator > 98765)
                break;
            string sNum = formatFive(numerator);
            string sDen = formatFive(denominator);
            if (usesAllDigits(sNum, sDen))
                solutions.emplace_back(numerator, denominator);
        }

        if (solutions.empty()) {
            cout << "There are no solutions for " << n << ".\n";
        } else {
            for (auto [numerator, denominator] : solutions) {
                cout << formatFive(numerator) << " / "
                     << formatFive(denominator) << " = " << n << "\n";
            }
        }
    }
    return 0;
}
