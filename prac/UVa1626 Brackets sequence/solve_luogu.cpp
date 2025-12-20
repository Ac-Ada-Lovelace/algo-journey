#include <bits/stdc++.h>
const int INF = 1e9;
using namespace std;
int f[105][105], t;
string s;
void write(int i, int j) {
    if (i == j)
        if (s[i] == '(' || s[i] == ')')
            cout << "()";
        else
            cout << "[]";
    else if (((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']')) &&
             f[i][j] == f[i + 1][j - 1]) {
        cout << s[i];
        write(i + 1, j - 1);
        cout << s[j];
    } else
        for (int p = i; p < j; p++)
            if (f[i][j] == f[i][p] + f[p + 1][j]) {
                write(i, p), write(p + 1, j);
                return;
            }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    getchar();
    while (t--) {
        getline(cin, s);
        getline(cin, s);
        int n = s.size();
        // cout<<n<<endl;
        for (int i = 0; i < n; i++)
            f[i][i] = 1, f[i + 1][i] = 0;
        for (int k = 1; k <= n; k++) {
            for (int i = 0; i <= n - k; i++) {
                int j = i + k - 1;
                f[i][j] = INF;
                // cout<<i<<" "<<j<<endl;
                if ((s[i] == '(' && s[j] == ')') ||
                    (s[i] == '[' && s[j] == ']'))
                    f[i][j] = min(f[i][j], f[i + 1][j - 1]);
                else if (s[i] == '(' || s[i] == '[')
                    f[i][j] = min(f[i][j], f[i + 1][j] + 1);
                else if (s[j] == ')' || s[j] == ']')
                    f[i][j] = min(f[i][j], f[i][j - 1] + 1);
                for (int p = i; p < j; p++)
                    f[i][j] = min(f[i][j], f[i][p] + f[p + 1][j]);
            }
        }
        // cout<<f[0][n-1]<<endl;
        write(0, n - 1);
        cout << endl;
        if (t)
            cout << endl;
    }
}
