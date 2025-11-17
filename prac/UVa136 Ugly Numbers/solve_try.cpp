#include <bits/stdc++.h>
using namespace std;
#define min3(x1, x2, x3) min(x1, min(x2, x3))

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    array<long long, 1500> ugly;

    ugly[0] = 1;
    long long i2 = 0, i3 = 0, i5 = 0;

    int count = 1;
    while (count < 1500) {
        long long n2 = ugly[i2] * 2;
        long long n3 = ugly[i3] * 3;
        long long n5 = ugly[i5] * 5;
        long long next = min3(n2, n3, n5);
        if (next == n2)
            i2++;
        if (next == n3)
            i3++;
        if (next == n5)
            i5++;

        ugly[count] = next;
        count++;
    }
    cout << "The 1500'th ugly number is " << ugly[1499] << ".\n";
}
