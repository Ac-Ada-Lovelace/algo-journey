#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
    bool deleted;
    Node* row_prev;
    Node* row_next;
    Node* col_prev;
    Node* col_next;
} Node;

int main() {
    // test timer
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::cout << ms << std::endl;

    array<array<Node*, 51>, 51> raw_pos;
    array<Node*, 51> row_head, col_head;

    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 50; j++) {
            raw_pos[i][j] = new Node{false, nullptr, nullptr, nullptr, nullptr};
        }
    }

    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 50; j++) {
            if (j == 1) {
                row_head[i] = raw_pos[i][j];
            } else {
                raw_pos[i][j]->col_prev = raw_pos[i][j - 1];
                raw_pos[i][j - 1]->col_next = raw_pos[i][j];
            }

            if (i == 1) {
                col_head[j] = raw_pos[i][j];
            } else {
                raw_pos[i][j]->row_prev = raw_pos[i - 1][j];
                raw_pos[i - 1][j]->row_next = raw_pos[i][j];
            }
        }
    }

    ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::cout << ms << std::endl;
}
