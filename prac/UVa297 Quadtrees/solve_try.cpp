#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

void draw_quad(int x, int y, int size, queue<char>& tokens, array<array<int, 33>, 33>& canvas) {
    if (tokens.empty())
        return;
    int token = tokens.front();
    tokens.pop();

    if (token == 'p') {
        draw_quad(x, y, size / 2, tokens, canvas);                       // upper-left
        draw_quad(x + size / 2, y, size / 2, tokens, canvas);            // upper-right
        draw_quad(x, y + size / 2, size / 2, tokens, canvas);            // lower-left
        draw_quad(x + size / 2, y + size / 2, size / 2, tokens, canvas); // lower-right
    } else if (token == 'f') {
        for (int i = x; i < x + size; ++i) {
            for (int j = y; j < y + size; ++j) {
                canvas[i][j] = 1;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases = 0;
    cin >> cases;
    cin.ignore();
    while (cases--) {
        queue<char> tokens;
        char ch;
        while (cin.peek() != '\n') {
            ch = (char)getchar();
            tokens.push(ch);
        }
        getchar(); // consume newline
        array<array<int, 33>, 33> canvas = {};
        draw_quad(1, 1, 32, tokens, canvas);
        queue<char> tokens1;
        char ch1;
        while (cin.peek() != '\n') {
            ch1 = (char)getchar();
            tokens1.push(ch1);
        }
        getchar(); // consume newline
        array<array<int, 33>, 33> canvas1 = {};
        draw_quad(1, 1, 32, tokens1, canvas1);

        int count = 0;
        for (int i = 1; i <= 32; ++i) {
            for (int j = 1; j <= 32; ++j) {
                canvas[i][j] = canvas[i][j] | canvas1[i][j];
                count += canvas[i][j];
            }
        }

        cout << "There are " << count << " black pixels.\n";
    }
}
