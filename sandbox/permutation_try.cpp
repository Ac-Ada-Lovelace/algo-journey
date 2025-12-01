#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

int main() {
    freopen("output.txt", "w", stdout);
    vector<int> is = {1, 2, 3, 4, 5};
    sort(is.begin(), is.end());
    do {
        for (auto i : is) {
            cout << i << " ";
        }
        cout << endl;
    } while (next_permutation(is.begin(), is.end()));
}
