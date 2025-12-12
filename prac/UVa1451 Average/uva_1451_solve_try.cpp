// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=4197
// UVa1451 Average
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000

int S[MAXN + 1];
double B[MAXN + 1];
int n;
int l;
int cases;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> cases;

    while (cases--) {
        cin >> n >> l;

        cin.ignore();
        char ch;
        int i = 1;
        int sum = 0;
        while (ch = getchar(), ch != '\n') {
            if (ch == ' ')
                continue;
            if (ch == '0') {
                S[i] = sum;
            } else {
                sum++;
                S[i] = sum;
            }
            i++;
        }
        
    }
}
