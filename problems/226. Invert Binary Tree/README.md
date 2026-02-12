# Day 28: Invert Binary Tree

- **Difficulty:** Easy
- **Topics:** Tree, Depth-First Search, Breadth-First Search, Recursion
- **LeetCode Link:** [Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, invert the tree, and return its root.

An inverted form of a binary tree is another binary tree where the left and right children of all non-leaf nodes are swapped. This is effectively a mirror image of the original tree.

**Example 1:**
Input: `root = [4,2,7,1,3,6,9]`
Output: `[4,7,2,9,6,3,1]`

Visualization:
```text
     4                 4
   /   \             /   \
  2     7    ==>    7     2
 / \   / \         / \   / \
1   3 6   9       9   6 3   1
```

---

## 🏗️ Deep-Dive Implementation Strategy

The problem requires visiting every node in the tree and swapping its left and right child pointers. Since we must process every node, the approach is a standard Tree Traversal (DFS or BFS).

### 1. Recursive Approach (Pre-Order DFS)
Your implementation follows a **Pre-Order Traversal** pattern:
1.  **Process Root:** Swap the `left` and `right` pointers of the current node.
2.  **Recurse Left:** Call the function on the *new* left child (which was originally the right child).
3.  **Recurse Right:** Call the function on the *new* right child (which was originally the left child).

*Note: The order of steps 2 and 3 relative to step 1 doesn't strictly matter (Post-Order works too), as long as every node is visited.*

### 2. Execution Visualization
Input: `root = [2, 1, 3]`

1.  **Call `invertTree(2)`:**
    * `root` is not null.
    * Swap children: `2->left` becomes `3`, `2->right` becomes `1`.
    * Tree state: `2 -> {Left: 3, Right: 1}`.
    * **Recurse Left:** `invertTree(3)`.
        * `3` is a leaf (children are null). Swap nulls (no change).
        * Recurse on null children (base cases return immediately).
        * Return `3`.
    * **Recurse Right:** `invertTree(1)`.
        * `1` is a leaf. Swap nulls.
        * Return `1`.
    * Return `2`.

Final Tree: `[2, 3, 1]`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let $T$ be a binary tree. The inversion function $Inv(T)$ is defined recursively:
$$Inv(T) = \begin{cases} \emptyset & \text{if } T \text{ is empty} \\ Node(root, Inv(right), Inv(left)) & \text{otherwise} \end{cases}$$

### 2. Time Complexity
We must visit every node exactly once to perform the swap.
$$T(N) = O(N)$$
Where $N$ is the number of nodes in the tree.

### 3. Space Complexity
The space complexity is determined by the recursion stack height, which corresponds to the height of the tree $H$.
* **Worst Case (Skewed Tree):** $O(N)$.
* **Best Case (Balanced Tree):** $O(\log N)$.

$$S(N) = O(H)$$

---

## 💻 Implementation (C++)

```cpp
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
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
```

---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).