// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=841&page=show_problem&problem=4089
// UVa1343 The Rotation Game
#include <bits/stdc++.h>
using namespace std;

array<array<int, 7>, 7> convert(array<int, 24> source) {
    array<array<int, 7>, 7> target;

    target[0] = {0, 0, source[0], 0, source[1], 0, 0};
    target[1] = {0, 0, source[2], 0, source[3], 0, 0};

    target[2] = {source[4], source[5], source[6], source[7],
                 source[8], source[9], source[10]};

    target[3] = {0, 0, source[11], 0, source[12], 0, 0};
    target[4] = {source[13], source[14], source[15], source[16],
                 source[17], source[18], source[19]};
    target[5] = {0, 0, source[20], 0, source[21], 0, 0};
    target[6] = {0, 0, source[22], 0, source[23], 0, 0};
}

 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
