#include <bits/stdc++.h>
using namespace std;

int is_generator_of_whom(int num) {
    int k = num;
    int target = num;
    while (k != 0) {
        target += k % 10;
        k /= 10;
    }

    return target;
}

int ANS[100001];

int main() {
    memset(ANS, -1, sizeof(ANS));
    for (int i = 0; i <= 100000; i++) {
        int target = is_generator_of_whom(i);
        if (ANS[target] == -1 && target <= 100000) {
            ANS[target] = i;
        }
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int turn = 0;
    cin >> turn;
    while (turn--) {
        int n;
        cin >> n;
        if (ANS[n] != -1) {
            cout << ANS[n] << "\n";
        } else {
            cout << "0" << "\n";
        }
    }
}
