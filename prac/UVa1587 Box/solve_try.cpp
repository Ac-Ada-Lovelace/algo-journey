#include <bits/stdc++.h>
using namespace std;

int sort_2(int* arr, int i1, int i2) {
    if (arr[i1] > arr[i2]) {
        int temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
    }
}

int main() {
    int faces[6];
    int num = 0;
    int turn = 0;
    while (cin >> num) {
        faces[turn] = num;
        turn = (turn + 1) % 6;
        if (turn == 0) {}
    }
}
