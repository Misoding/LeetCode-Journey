# Day 24: Balanced Binary Tree

- **Difficulty:** Easy
- **Topics:** Tree, Depth-First Search, Recursion
- **LeetCode Link:** [Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a binary tree, determine if it is **height-balanced**.

A **height-balanced** binary tree is defined as:
> A binary tree in which the left and right subtrees of **every** node differ in height by no more than 1.

**Example 1:**
Input: `root = [3,9,20,null,null,15,7]`
Output: `true`
Explanation: The height of the left subtree is 1. The height of the right subtree is 2. $|1 - 2| \le 1$.

**Example 2:**
Input: `root = [1,2,2,3,3,null,null,4,4]`
Output: `false`
Explanation: The root's left subtree has height 3, while the right subtree has height 1. $|3 - 1| > 1$.

---

## 🏗️ Deep-Dive Implementation Strategy

A naive approach might calculate the height of the left and right children from the top down for every node, leading to an $O(N^2)$ complexity due to redundant calculations.

We optimize this using a **Bottom-Up DFS** approach.



### 1. The Recursion Logic
We traverse the tree using **Post-Order Traversal** (Left $\to$ Right $\to$ Root). This ensures that when we process a node, we already know the heights of its children.
* **Base Case:** If the node is `nullptr`, its height is 0.
* **Recursive Step:**
    * Calculate height of left subtree (`leftSize`).
    * Calculate height of right subtree (`rightSize`).
* **Height Calculation:** The height of the current node is $1 + \max(\text{leftSize}, \text{rightSize})$.

### 2. The Validation Flag
Instead of returning complex error codes (like `-1` for invalid), your implementation uses a member variable `validTree` initialized to `true`.
* At every node, we check the balance condition: `abs(leftSize - rightSize) > 1`.
* If the condition is violated anywhere in the tree, we set `validTree = false`.
* The recursion continues (calculating heights), but the final answer is already determined.

### 3. Execution Visualization
Consider a skewed tree `1 -> 2 -> 3`.
1.  **Node 3:** Left=0, Right=0. Diff=0. Height=1.
2.  **Node 2:** Left=0, Right=Height(3)=1. Diff=1. Height=2.
3.  **Node 1:** Left=0, Right=Height(2)=2. Diff=2. **Flag set to False**. Height=3.
4.  **Result:** `validTree` is `false`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let $H(v)$ be the height of node $v$.
$$ H(v) = \begin{cases} 0 & \text{if } v \text{ is null} \\ 1 + \max(H(v_{left}), H(v_{right})) & \text{otherwise} \end{cases} $$
The tree is balanced if and only if:
$$ \forall v \in V, \ |H(v_{left}) - H(v_{right})| \le 1 $$

### 2. Time Complexity
The algorithm visits every node exactly once using DFS. At each node, we perform constant-time operations (addition, comparison, max).
$$ T(N) = O(N) $$

### 3. Space Complexity
The space complexity depends on the recursion stack depth.
* **Balanced Tree:** $O(\log N)$
* **Skewed Tree:** $O(N)$

$$ S(N) \in O(N) \text{ (Worst Case)} $$

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
    bool validTree;
    int balancedTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftSize = 1 + balancedTree(root->left);
        int rightSize = 1 + balancedTree(root->right);
        if (abs(leftSize - rightSize) > 1) {
            validTree = false;
        }
        return max(leftSize, rightSize);
    }
    bool isBalanced(TreeNode* root) {
        validTree = true;
        int n = balancedTree(root);
        return validTree;
    }
};
```

---
### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).
