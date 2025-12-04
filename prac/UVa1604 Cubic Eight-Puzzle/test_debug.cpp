#include <bits/stdc++.h>
using namespace std;

struct cubic {
    char vertical;
    char horizontal;

    static const char BLUE = 0b00;
    static const char WHITE = 0b01;
    static const char RED = 0b10;

    cubic() {
        // Initial: Top=White, Bottom=White, Front=Red, Back=Red, Left=Blue, Right=Blue
        vertical = (WHITE << 6) | (RED << 4) | (WHITE << 2) | RED;
        horizontal = (WHITE << 6) | (BLUE << 4) | (WHITE << 2) | BLUE;
    }

    char get_face(char data, int pos) const {
        return (data >> (pos * 2)) & 0b11;
    }

    char color_to_char(char color) const {
        if (color == BLUE) return 'B';
        if (color == WHITE) return 'W';
        if (color == RED) return 'R';
        return '?';
    }

    void print_all() {
        cout << "Vertical: [bottom=" << color_to_char(get_face(vertical, 3))
             << "][back=" << color_to_char(get_face(vertical, 2))
             << "][top=" << color_to_char(get_face(vertical, 1))
             << "][front=" << color_to_char(get_face(vertical, 0)) << "]" << endl;
        cout << "Horizontal: [bottom=" << color_to_char(get_face(horizontal, 3))
             << "][left=" << color_to_char(get_face(horizontal, 2))
             << "][top=" << color_to_char(get_face(horizontal, 1))
             << "][right=" << color_to_char(get_face(horizontal, 0)) << "]" << endl;
    }
};

int main() {
    cubic c;
    cout << "Initial state:" << endl;
    c.print_all();

    cout << "\n=== Thinking about horizontal roll ===" << endl;
    cout << "When rolling RIGHT (dy=1):" << endl;
    cout << "- Left face becomes new Top" << endl;
    cout << "- Top becomes new Right" << endl;
    cout << "- Right becomes new Bottom" << endl;
    cout << "- Bottom becomes new Left" << endl;
    cout << "- Front and Back stay the same" << endl;

    cout << "\nSo for horizontal roll:" << endl;
    cout << "horizontal rotates: [bottom][left][top][right]" << endl;
    cout << "vertical's front/back stay, but top/bottom sync with horizontal" << endl;
}
