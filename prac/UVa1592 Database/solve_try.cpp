#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int col;
    int row;
} pos;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<string>> matrix(n, vector<string>(m));
        map<string, vector<pos>> string_set;
        vector<map<string, vector<pos>>> repeated_string_by_col(m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                string s;
                cin >> s;
                if(string_set.count(s)){
                       
                }

            }
        }
    }

}
