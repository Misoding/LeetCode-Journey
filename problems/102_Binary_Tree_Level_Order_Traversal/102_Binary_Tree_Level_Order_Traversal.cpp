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
    vector<vector<int>> levelOrder(TreeNode* root) {
        std::queue<std::pair<int,TreeNode*>> node_queue;
        node_queue.push(std::make_pair(0, root));
        unordered_map<int, vector<int>> resultMap;
        vector<vector<int>> finalResult;
        while (!node_queue.empty()){
            std::pair<int, TreeNode*> currentPair = node_queue.front();
            node_queue.pop();
            if(currentPair.second != nullptr) {
                if (resultMap.find(currentPair.first) == resultMap.end()) {
                    vector<int> levelResult;
                    levelResult.push_back(currentPair.second->val);
                    resultMap[currentPair.first] = levelResult;
                } else {
                    resultMap[currentPair.first].push_back(currentPair.second->val);
                }

                node_queue.push(std::make_pair(currentPair.first + 1, currentPair.second->left));
                node_queue.push(std::make_pair(currentPair.first + 1, currentPair.second->right));
            }
        }
        int i = 0;
        while (resultMap.find(i) != resultMap.end()) {
            finalResult.push_back(resultMap[i++]);
        }
        return finalResult;
    }
};