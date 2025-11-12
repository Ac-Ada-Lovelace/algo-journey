#include <bits/stdc++.h>
using namespace std;

struct Expansion {
    string non_repeating;
    string repeating;
    int repeat_len;
};

Expansion expand_fraction(int numerator, int denominator) {
    int integer_part = numerator / denominator;
    int remainder = numerator % denominator;
    vector<int> digits;
    unordered_map<int, int> remainder_pos;

    while (remainder != 0 && !remainder_pos.count(remainder)) {
        remainder_pos[remainder] = digits.size();
        remainder *= 10;
        digits.push_back(remainder / denominator);
        remainder %= denominator;
    }

    string decimal;
    decimal.reserve(digits.size());
    for (int d : digits) {
        decimal.push_back(char('0' + d));
    }

    if (remainder == 0) {
        return {decimal, "0", 1};
    }

    int repeat_start = remainder_pos[remainder];
    string non_rep = decimal.substr(0, repeat_start);
    string rep = decimal.substr(repeat_start);
    return {non_rep, rep, int(rep.size())};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numerator, denominator;
    bool first_case = true;
    while (cin >> numerator >> denominator) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;

        int integer_part = numerator / denominator;
        Expansion exp = expand_fraction(numerator, denominator);

        cout << numerator << "/" << denominator << " = " << integer_part << ".";
        cout << exp.non_repeating;

        string repeat_display = exp.repeating;
        if (exp.repeating != "0" && exp.repeating.size() > 50) {
            repeat_display = exp.repeating.substr(0, 50) + "...";
        }

        cout << "(" << repeat_display << ")\n";
        cout << "   " << exp.repeat_len << " = number of repeating digits.\n";
    }
    return 0;
}
