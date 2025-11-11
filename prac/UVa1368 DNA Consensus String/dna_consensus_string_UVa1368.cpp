#include <csignal>
#include "bits/stdc++.h"
using namespace std;

// fit for where s1.length() == s2.length()
int calc_hamming(string s1, string s2) {
    int l = s1.length();
    int sum = 0;

    for (int i = 0; i < l; i++) {
        if (s1[i] != s2[i]) {
            sum++;
        }
    }

    return sum;
}

char highest_freq_char(vector<char> str) {
    map<char, int> freq;
    freq['A'] = 0;
    freq['C'] = 0;
    freq['G'] = 0;
    freq['T'] = 0;
    for (char c : str) {
        freq[c]++;
        cout << c << freq[c] << endl;
    }
    char max_char = 'A';
    int max_count = freq['A'];
    for (auto& pair : freq) {
        if (pair.second > max_count) {
            max_char = pair.first;
            max_count = pair.second;
        }
    }
    return max_char;
}

int main() {
    int m = 5, n = 8;
    // cin >> m >> n;
    vector<string> dna_strings(m);
    dna_strings.clear();
    dna_strings.push_back("TATGATAC");
    dna_strings.push_back("TAAGCTAC");
    dna_strings.push_back("AAAGATCC");
    dna_strings.push_back("TGAGATAC");
    dna_strings.push_back("TAAGATGT");

    cout << "hello\n";
    // for (int i = 0; i < m; i++) {
    //     cin >> dna_strings[i];
    // }
    //
    string s = "";
    for (int i = 0; i < n; i++) {
        vector<char> column_chars;
        for (int j = 0; j < m; j++) {
            column_chars.push_back(dna_strings[j][i]);
        }
        for (auto c : column_chars) {
            cout << c << " ";
        }
        char c = highest_freq_char(column_chars);
        s += c;
        cout << c << endl;
    }
    cout << "OUTPUT" << endl;
    cout << s;
}
