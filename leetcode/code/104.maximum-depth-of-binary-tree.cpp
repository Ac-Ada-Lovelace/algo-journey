#include <bits/stdc++.h>
#include "defs.h"
using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    int _max_depth = 0;
    void dfs(TreeNode* node, int depth) {
        if (!node) {
            return;
        }
        depth++;
        if (depth > _max_depth) {
            _max_depth = depth;
        }
        dfs(node->left, depth);
        dfs(node->right, depth);
    }
    int maxDepth(TreeNode* root) {
        _max_depth = 0;
        dfs(root, 0);
        return _max_depth;
    }
};
