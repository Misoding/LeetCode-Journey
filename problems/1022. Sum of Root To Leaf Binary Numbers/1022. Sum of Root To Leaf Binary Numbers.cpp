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
    void helperFunc(TreeNode* root, unsigned long long comulatedNum, int& totalSum) {
        if(root == nullptr) {
            return;
        }
        comulatedNum = comulatedNum << 1;
        comulatedNum |= root->val;
        if (root->left == nullptr && root->right == nullptr) {
            totalSum+=comulatedNum;
            return;
        }
        helperFunc(root->left, comulatedNum, totalSum);
        helperFunc(root->right, comulatedNum, totalSum);
    }
    int sumRootToLeaf(TreeNode* root){
        int totalSum = 0;
        helperFunc(root, 0, totalSum);
        return totalSum;
    }
};