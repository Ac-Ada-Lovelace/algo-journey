// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=4494
//
// UVa1619 Feel Good
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int num;
    while (cin >> num) {
        vector<long long> arr(num);

        for (int i = 0; i < num; i++) {
            cin >> arr[i];
        }

        int l = 0, r = 0;
        long long _max = 0;
        ;

        for (int i = 0; i < num; i++) {
            long long sum = arr[i];
            for (int j = i - 1; j >= 0; j--) {
                if (arr[j] < arr[i]) {
                    l = j + 2;
                    break;
                }
                sum += arr[j];
            }
            for (int j = i + 1; j < num; j++) {
                if (arr[j] < arr[i]) {
                    r = j;
                    break;
                }

                sum += arr[j];
            }

            _max = max(_max, sum * arr[i]);
        }

        cout << _max << '\n';
        cout << l << ' ' << r << '\n';
    }
}
