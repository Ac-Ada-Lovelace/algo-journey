#include "bits/stdc++.h"

using namespace std;

map<char, int> char_count;

void count_characters(const string& s) {
    for (char c : s) {
        char_count[c]++;
    }
}

void count_til_n(int n){
    for(int i = 1; i <= n; i++){
        count_characters(to_string(i));   
    }

}


int main() {
    int n;
    while (cin >> n, n != 0) {
        count_til_n(n);
        for (char c = '0'; c <= '9'; c++) {
            cout << c << " : " << char_count[c] << endl;
        }
    }
    return 0;
}