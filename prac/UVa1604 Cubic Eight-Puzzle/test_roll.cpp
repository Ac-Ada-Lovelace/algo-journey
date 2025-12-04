#include <bits/stdc++.h>
using namespace std;

struct cubic {
    char vertical;
    char horizontal;

    static const char BLUE = 0b00;
    static const char WHITE = 0b01;
    static const char RED = 0b10;

    cubic() {
        vertical = (WHITE << 6) | (RED << 4) | (WHITE << 2) | RED;
        horizontal = (WHITE << 6) | (BLUE << 4) | (WHITE << 2) | BLUE;
    }

    char get_top() const {
        return (vertical >> 2) & 0b11;
    }

    char color_to_char(char color) const {
        if (color == BLUE) return 'B';
        if (color == WHITE) return 'W';
        if (color == RED) return 'R';
        return '?';
    }

    void roll(int dx, int dy) {
        if (dx != 0) {
            // Vertical roll
            if (dx == 1) {
                char front = vertical & 0b11;
                vertical >>= 2;
                vertical |= (front << 6);
            } else {
                char bottom = (vertical >> 6) & 0b11;
                vertical = ((vertical << 2) & 0b11111111) | bottom;
            }
            // Update horizontal's top and bottom to match vertical
            char v_top = (vertical >> 2) & 0b11;
            char v_bottom = (vertical >> 6) & 0b11;
            horizontal = (horizontal & 0b00110011) | (v_bottom << 6) | (v_top << 2);
        } else {
            // Horizontal roll
            if (dy == 1) {
                char right = horizontal & 0b11;
                horizontal >>= 2;
                horizontal |= (right << 6);
            } else {
                char bottom = (horizontal >> 6) & 0b11;
                horizontal = ((horizontal << 2) & 0b11111111) | bottom;
            }
            // Update vertical's top and bottom to match horizontal
            char h_top = (horizontal >> 2) & 0b11;
            char h_bottom = (horizontal >> 6) & 0b11;
            vertical = (vertical & 0b00110011) | (h_bottom << 6) | (h_top << 2);
        }
    }

    void print() {
        cout << "Top: " << color_to_char(get_top()) << endl;
    }
};

int main() {
    cubic c;
    cout << "Initial state: ";
    c.print();

    cout << "\nAfter roll down (dx=1, dy=0): ";
    c.roll(1, 0);
    c.print();

    cout << "After roll up (dx=-1, dy=0): ";
    c.roll(-1, 0);
    c.print();

    cout << "Should be back to White\n";

    cubic c2;
    cout << "\nInitial state: ";
    c2.print();

    cout << "After roll right (dx=0, dy=1): ";
    c2.roll(0, 1);
    c2.print();

    cout << "After roll left (dx=0, dy=-1): ";
    c2.roll(0, -1);
    c2.print();

    cout << "Should be back to White\n";
}
