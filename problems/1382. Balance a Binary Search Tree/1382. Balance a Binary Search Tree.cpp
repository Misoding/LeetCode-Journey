/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void traverseInOrder(TreeNode* root, vector<int>& nodes) {
        if (root == nullptr) return;
        traverseInOrder(root->left, nodes);
        nodes.push_back(root->val);
        traverseInOrder(root->right, nodes);
    }
    TreeNode* reformTree(vector<int>& nodes, int begin, int end) {
        if (begin > end) return nullptr;
        int mid = (begin + end) / 2;
        TreeNode* root = new TreeNode(nodes[mid]);
        root->left = reformTree(nodes, begin, mid - 1);
        root->right = reformTree(nodes, mid+1, end);
        return root;
    }
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> nodes;
        traverseInOrder(root, nodes);
        return reformTree(nodes, 0, nodes.size()-1);
    }
};