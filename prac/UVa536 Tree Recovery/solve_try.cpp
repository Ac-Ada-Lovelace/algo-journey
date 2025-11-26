// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=839&page=show_problem&problem=477
// UVa536 Tree Recovery
#include <bits/stdc++.h>
using namespace std;

typedef struct tree_node {
    char val;
    tree_node* left;
    tree_node* right;
    tree_node(char x) : val(x), left(nullptr), right(nullptr) {}
} tree_node;

tree_node* build_by_pre_in(const vector<char>& pre, int pre_start, int pre_end,
                           vector<char> in, int in_start, int in_end) {
    if (pre_start > pre_end || in_start > in_end) {
        return nullptr;
    }

    char root_val = pre[pre_start];

    tree_node* root = new tree_node(root_val);

    auto root_pos_at_in =
        find(in.begin() + in_start, in.begin() + in_end + 1, root_val) -
        in.begin();

    root->left = build_by_pre_in(pre, pre_start + 1,
                                 pre_start + (root_pos_at_in - in_start), in,
                                 in_start, root_pos_at_in - 1);
    root->right =
        build_by_pre_in(pre, pre_start + (root_pos_at_in - in_start) + 1,
                        pre_end, in, root_pos_at_in + 1, in_end);
    return root;
}

vector<char> visit_postorder(tree_node* root) {
    vector<char> res;
    if (!root) {
        return res;
    }
    vector<char> left = visit_postorder(root->left);
    vector<char> right = visit_postorder(root->right);
    res.insert(res.end(), left.begin(), left.end());
    res.insert(res.end(), right.begin(), right.end());
    res.push_back(root->val);
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

}
