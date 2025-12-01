#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> solves;
vector<vector<int>> C;
int tot = 0;
int n;

void dfs(int cur) {
    if(cur == n){
        tot++;
        return;
    }

 for (int i = 0; i < n; i++) {
        C[cur][i] = 1;
        bool ok = true;
        for (int j = 0; j < cur; j++) {
        }
    }

}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    solves.assign(n, vector<int>(n, 0));
    C.assign(n, vector<int>(n, 0));

    dfs(0);
}
