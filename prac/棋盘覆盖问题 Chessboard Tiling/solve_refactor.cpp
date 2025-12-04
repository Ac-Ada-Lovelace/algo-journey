#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 64

int board[MAX_SIZE][MAX_SIZE];
int tile = 1;
int n;

void chess_board(int tr, int tc, int dr, int dc, int size) {
    if (size == 1)
        return;

    int half = size / 2;
    int t = tile++;  // 当前L型骨牌的编号

    // 【核心】判断特殊方格在哪个子棋盘，并在中心位置放置L型骨牌
    // 四个子棋盘的中心交汇点坐标：
    // 左上角: (tr+half-1, tc+half-1)  右上角: (tr+half-1, tc+half)
    // 左下角: (tr+half,   tc+half-1)  右下角: (tr+half,   tc+half)

    // 判断特殊方格在哪个象限
    bool in_top_left = (dr < tr + half && dc < tc + half);
    bool in_top_right = (dr < tr + half && dc >= tc + half);
    bool in_bottom_left = (dr >= tr + half && dc < tc + half);
    bool in_bottom_right = (dr >= tr + half && dc >= tc + half);

    // 在中心位置放置L型骨牌（覆盖不包含特殊方格的3个子棋盘的角落）
    if (!in_top_left)     board[tr + half - 1][tc + half - 1] = t;  // 左上角
    if (!in_top_right)    board[tr + half - 1][tc + half] = t;      // 右上角
    if (!in_bottom_left)  board[tr + half][tc + half - 1] = t;      // 左下角
    if (!in_bottom_right) board[tr + half][tc + half] = t;          // 右下角

    // 递归处理4个子棋盘（每个子棋盘都有"特殊方格"了）
    // 左上子棋盘
    if (in_top_left) {
        chess_board(tr, tc, dr, dc, half);  // 特殊方格是原来的
    } else {
        chess_board(tr, tc, tr + half - 1, tc + half - 1, half);  // 特殊方格是刚放的骨牌
    }

    // 右上子棋盘
    if (in_top_right) {
        chess_board(tr, tc + half, dr, dc, half);
    } else {
        chess_board(tr, tc + half, tr + half - 1, tc + half, half);
    }

    // 左下子棋盘
    if (in_bottom_left) {
        chess_board(tr + half, tc, dr, dc, half);
    } else {
        chess_board(tr + half, tc, tr + half, tc + half - 1, half);
    }

    // 右下子棋盘
    if (in_bottom_right) {
        chess_board(tr + half, tc + half, dr, dc, half);
    } else {
        chess_board(tr + half, tc + half, tr + half, tc + half, half);
    }
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
    int sr = 5, sc = 7;
    board[sr][sc] = 0;  // 标记特殊方格

    chess_board(0, 0, sr, sc, n);
    print_board();
}
