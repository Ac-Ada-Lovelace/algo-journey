#include <bits/stdc++.h>
using namespace std;

#define MAXM 200000
#define MAXN 100000

int gates[MAXM + 1]; // positive means use gates, negative means use input
int input[MAXN + 1]; //

int output[MAXN + 1][2];
int critical[MAXN + 1];

bool get_output(int gate, int x) {
    if (output[gate][x] != -1)
        return output[gate][x];

    int l = 2 * gate - 1;
    int r = 2 * gate;
    int li, ri;
    if (gates[l] > 0) {
        li = get_output(gates[l], 0);
    } else {
        li = input[-gates[l]];
    }
    if (gates[r] > 0) {
        ri = get_output(gates[r], 0);
    } else {
        ri = input[-gates[r]];
    }

    output[gate][x] = !(li && ri);
    return output[gate][x];
}

int find_critical(int lg, int rg){

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
