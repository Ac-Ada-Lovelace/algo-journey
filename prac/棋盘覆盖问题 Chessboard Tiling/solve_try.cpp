#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 64

int board[MAX_SIZE][MAX_SIZE];
int tile = 1;
int n;

int chess_board(int tr, int tc, int dr, int dc, int size) {
    if (size == 1)
        return 0;
    int t = tile++;
    int s = size / 2;

    // Top-left
    if (dr < tr + s && dc < tc + s)
        chess_board(tr, tc, dr, dc, s);
    else {
        board[tr + s - 1][tc + s - 1] = t;
        chess_board(tr, tc, tr + s - 1, tc + s - 1, s);
    }

    // Top-right
    if (dr < tr + s && dc >= tc + s)
        chess_board(tr, tc + s, dr, dc, s);
    else {
        board[tr + s - 1][tc + s] = t;
        chess_board(tr, tc + s, tr + s - 1, tc + s, s);
    }

    // Bottom-left
    if (dr >= tr + s && dc < tc + s)
        chess_board(tr + s, tc, dr, dc, s);
    else {
        board[tr + s][tc + s - 1] = t;
        chess_board(tr + s, tc, tr + s, tc + s - 1, s);
    }

    // Bottom-right
    if (dr >= tr + s && dc >= tc + s)
        chess_board(tr + s, tc + s, dr, dc, s);
    else {
        board[tr + s][tc + s] = t;
        chess_board(tr + s, tc + s, tr + s, tc + s, s);
    }
    return 0;
}

void print_board() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    n = 8;
    chess_board(0, 0, 5, 7, n);
    print_board();
}
