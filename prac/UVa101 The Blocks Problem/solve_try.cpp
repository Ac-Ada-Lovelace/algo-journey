#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int pile;
    int index;

} pos;
void put_back_above(vector<vector<int>>& blocks, vector<pos>& bpos, int a) {
    auto pos_a = bpos[a];
    // 原实现：
    // while (blocks[pos_a.pile].size() > pos_a.index + 1) {
    //     auto block = blocks[pos_a.pile].back();
    //     blocks[pos_a.pile].pop_back();
    //     blocks[block].push_back(block);
    //     bpos[block] = {block, 0};
    // }
    while (static_cast<int>(blocks[pos_a.pile].size()) > pos_a.index + 1) {
        auto block = blocks[pos_a.pile].back();
        blocks[pos_a.pile].pop_back();
        blocks[block].clear();
        blocks[block].push_back(block);
        bpos[block] = {block, 0};
    }
}
void move_onto(vector<vector<int>>& blocks, vector<pos>& bpos, int a, int b) {
    put_back_above(blocks, bpos, a);

    put_back_above(blocks, bpos, b);
    blocks[bpos[a].pile].pop_back();
    blocks[bpos[b].pile].push_back(a);
    bpos[a] = {bpos[b].pile, bpos[b].index + 1};
}
void move_over(vector<vector<int>>& blocks, vector<pos>& bpos, int a, int b) {
    put_back_above(blocks, bpos, a);

    blocks[bpos[a].pile].pop_back();
    blocks[bpos[b].pile].push_back(a);
    bpos[a] = {bpos[b].pile, (int)blocks[bpos[b].pile].size() - 1};
}
void pile_onto(vector<vector<int>>& blocks, vector<pos>& bpos, int a, int b) {
    put_back_above(blocks, bpos, b);

    // 原实现：
    // auto pos_a = bpos[a];
    // auto pos_b = bpos[b];
    // stack<int> pile_stack;
    // while (blocks[pos_a.pile].back() != a) {
    //     pile_stack.push(blocks[pos_b.pile].back());
    //     blocks[pos_b.pile].pop_back();
    // }
    // blocks[pos_a.pile].pop_back();
    // pile_stack.push(a);
    // while (!pile_stack.empty()) {
    //     auto block = pile_stack.top();
    //     pile_stack.pop();
    //     blocks[pos_b.pile].push_back(block);
    //     bpos[block] = {pos_b.pile, (int)blocks[pos_b.pile].size() - 1};
    // }

    auto pos_a = bpos[a];
    int from_pile = pos_a.pile;
    vector<int> moving(blocks[from_pile].begin() + pos_a.index, blocks[from_pile].end());
    blocks[from_pile].resize(pos_a.index);
    int target_pile = bpos[b].pile;
    for (int block : moving) {
        blocks[target_pile].push_back(block);
        bpos[block] = {target_pile, static_cast<int>(blocks[target_pile].size()) - 1};
    }
}
void pile_over(vector<vector<int>>& blocks, vector<pos>& bpos, int a, int b) {
    // 原实现：
    // auto pos_a = bpos[a];
    // auto pos_b = bpos[b];
    // stack<int> pile_stack;
    // while (blocks[pos_a.pile].size() > pos_a.index) {
    //     pile_stack.push(blocks[pos_a.pile].back());
    //     blocks[pos_a.pile].pop_back();
    // }
    // while (!pile_stack.empty()) {
    //     auto tmp_b = pile_stack.top();
    //     pile_stack.pop();
    //     bpos[tmp_b] = {pos_b.pile, (int)blocks[pos_b.pile].size()};
    //     blocks[pos_b.pile].push_back(tmp_b);
    // }

    auto pos_a = bpos[a];
    int from_pile = pos_a.pile;
    vector<int> moving(blocks[from_pile].begin() + pos_a.index, blocks[from_pile].end());
    blocks[from_pile].resize(pos_a.index);
    int target_pile = bpos[b].pile;
    for (int block : moving) {
        blocks[target_pile].push_back(block);
        bpos[block] = {target_pile, static_cast<int>(blocks[target_pile].size()) - 1};
    }
}
int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    string str;
    int blocks_num = 0;
    vector<vector<int>> blocks;
    while (str != "quit") {
        cin >> blocks_num;

        blocks = vector<vector<int>>(blocks_num);
        auto bpos = vector<pos>(blocks_num);
        for (int i = 0; i < blocks_num; i++) {
            blocks[i].push_back(i);
            bpos[i] = {i, 0};
        }
        while (true) {
            cin >> str;
            if (str == "quit")
                break;
            int a, b;
            cin >> a;

            if (str == "move") {
                cin >> str;
                if (str == "onto") {
                    cin >> b;
                    if (a == b || bpos[a].pile == bpos[b].pile)
                        continue;
                    move_onto(blocks, bpos, a, b);
                } else if (str == "over") {
                    cin >> b;
                    if (a == b || bpos[a].pile == bpos[b].pile)
                        continue;
                    move_over(blocks, bpos, a, b);
                }
            } else if (str == "pile") {
                cin >> str;
                if (str == "onto") {
                    cin >> b;
                    if (a == b || bpos[a].pile == bpos[b].pile)
                        continue;
                    pile_onto(blocks, bpos, a, b);
                } else if (str == "over") {
                    cin >> b;
                    if (a == b || bpos[a].pile == bpos[b].pile)
                        continue;
                    pile_over(blocks, bpos, a, b);
                }
            }
        }
    }
    for (int i = 0; i < blocks_num; i++) {
        cout << i << ":";
        for (int j = 0; j < (int)blocks[i].size(); j++) {
            cout << " " << blocks[i][j];
        }
        cout << endl;
    }
    return 0;
}
