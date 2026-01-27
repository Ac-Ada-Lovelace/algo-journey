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
    void visit(TreeNode* node, int level, vector<vector<int>>& res) {
        if (!node)
            return;
        if (level == res.size()) {
            res.push_back({});
        }
        res[level].push_back(node->val);
        visit(node->left, level + 1, res);
        visit(node->right, level + 1, res);
        return;
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        visit(root, 0, res);
        return res;
    }

    vector<vector<int>> visitBFS(TreeNode* root) {
        vector<vector<TreeNode*>> res;
        res.push_back({root});

        int flag = 0;
        int dpth = 0;
        while (true) {
            for (int i = 0; i < res[dpth].size(), i++) {
                if (res.size() == dpth + 1) {
                    res.push_back({});
                }
                if (res[dpth][i]->left) {
                    res[dpth + 1].push_back(res[dpth][i]->left);
                }
                if (res[dpth][i]->right) {
                    res[dpth + 1].push_back(res[dpth][i]->right);
                }
            }
        }
    }
};
