// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=841&page=show_problem&problem=465
// UVa524 Prime Ring Problem
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> ring;
vector<int> used;
bool is_prime[33];

void print_ring() {
    for (int i = 0; i < n; i++) {
        if (i)
            cout << ' ';
        cout << ring[i];
    }
    cout << '\n';
}

void dfs(int idx) {
    if (idx == n) {
        if (is_prime[ring[n - 1] + ring[0]]) {
            print_ring();
        }
        return;
    }
    for (int v = 2; v <= n; v++) {
        if (used[v])
            continue;
        if (!is_prime[ring[idx - 1] + v])
            continue;
        ring[idx] = v;
        used[v] = 1;
        dfs(idx + 1);
        used[v] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int case_no = 1;
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    for (int p : primes)
        is_prime[p] = true;

    while (cin >> n) {
        if (case_no > 1)
            cout << '\n';
        cout << "Case " << case_no++ << ":\n";

        ring.assign(n, 0);
        used.assign(n + 1, 0);
        ring[0] = 1;
        used[1] = 1;
        dfs(1);
    }
}
