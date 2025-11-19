#include <bits/stdc++.h>
using namespace std;

// NOTE: build binary tree from inorder and postorder;

typedef struct tree_node {
    int val;
    tree_node* left;
    tree_node* right;
    tree_node(int x) : val(x), left(nullptr), right(nullptr) {}
} tree_node;

tree_node* build(const vector<int>& inorder, int in_start, int in_end, const vector<int>& postorder,
                 int post_start, int post_end, unordered_map<int, int>& ino_index_map) {
    if (in_start > in_end || post_start > post_end) {
        return nullptr;
    }

    int root_val = postorder[post_end];
    tree_node* root = new tree_node(root_val);

    int ino_root_index = ino_index_map[root_val];
    int left_tree_size = ino_root_index - in_start;

    root->left = build(inorder, in_start, ino_root_index - 1, postorder, post_start,
                       post_start + left_tree_size - 1, ino_index_map);
    root->right = build(inorder, ino_root_index + 1, in_end, postorder, post_start + left_tree_size,
                        post_end - 1, ino_index_map);

    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    string ino_str, post_str;
    while (getline(cin, line)) {
        if (ino_str.empty()) {
            ino_str = line;
        } else {
            post_str = line;

            vector<int> inorder, postorder;
            unordered_map<int, int> ino_index_map;

            stringstream ino_ss(ino_str);
            string token;
            int index = 0;
            while (getline(ino_ss, token, ' ')) {
                int val = stoi(token);
                inorder.push_back(val);
                ino_index_map[val] = index++;
            }

            stringstream post_ss(post_str);
            while (getline(post_ss, token, ' ')) {
                int val = stoi(token);
                postorder.push_back(val);
            }

            tree_node* root = build(inorder, 0, inorder.size() - 1, postorder, 0,
                                    postorder.size() - 1, ino_index_map);

            ino_str.clear();
            post_str.clear();
        }
    }
}
