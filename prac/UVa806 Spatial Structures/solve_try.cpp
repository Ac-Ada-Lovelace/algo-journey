// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=839&page=show_problem&problem=747
// UVa806 Spatial Structures
#include <bits/stdc++.h>
#include <sys/types.h>
using namespace std;

struct quad_tree {
    int val; // -1 means need to be split, 0 means whith, 1 means black
    quad_tree* qts[4]; // enable when val == -1, order by left upper, right
                       // upper, left lower, right lower
};

bool is_pure(const vector<string>& image, int x_start, int y_start, int size) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (image[y_start + i][x_start + j] == '1') {
                count++;
            }
        }
    }

    return count == 0 || count == size * size;
}

quad_tree* build(const vector<string>& image, int x_start, int y_start,
                 int size) {
    if (size == 1) {
        return new quad_tree{image[y_start][x_start] == '1' ? 1 : 0,
                             {nullptr, nullptr, nullptr, nullptr}};
    }
    if (is_pure(image, x_start, y_start, size)) {
        int val = image[y_start][x_start] == '1' ? 1 : 0;
        return new quad_tree{val, {nullptr, nullptr, nullptr, nullptr}};
    }

    int x_center = x_start + (size / 2);
    int y_center = y_start + (size / 2);
    array<array<int, 2>, 4> quadrants = {{
        {x_start, y_start},  // left upper
        {x_center, y_start}, // right upper
        {x_start, y_center}, // left lower
        {x_center, y_center} // right lower
    }};

    quad_tree* node = new quad_tree{-1, {nullptr, nullptr, nullptr, nullptr}};
    for (int i = 0; i < 4; i++) {
        auto xy = quadrants[i];
        if (is_pure(image, xy[0], xy[1], size / 2)) {
            int val = image[xy[1]][xy[0]] == '1' ? 1 : 0;
            node->qts[i] =
                new quad_tree{val, {nullptr, nullptr, nullptr, nullptr}};
        } else {
            quad_tree* qt = build(image, xy[0], xy[1], size / 2);
            node->qts[i] = qt;
        }
    }
    return node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
