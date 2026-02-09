# Day 25: Balance a Binary Search Tree

- **Difficulty:** Medium
- **Topics:** Binary Search Tree, Recursion, Divide and Conquer, Greedy
- **LeetCode Link:** [Balance a Binary Search Tree](https://leetcode.com/problems/balance-a-binary-search-tree/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given the `root` of a binary search tree (BST), return a **balanced** binary search tree with the same node values. If there is more than one answer, return **any** of them.

A binary search tree is **balanced** if the depth of the two subtrees of every node never differs by more than 1.

**Example:**
Input: `root = [1,null,2,null,3,null,4,null,null]` (A skewed line)
Output: `[2,1,3,null,null,null,4]` (A balanced tree)

---

## 🏗️ Deep-Dive Implementation Strategy

A BST can become degenerate (like a linked list) after many insertions or deletions. To rebalance it completely, we can't just rotate nodes locally; we need a global restructuring.

### 1. The Two-Phase Algorithm
The standard approach involves two distinct steps:

1.  **Flatten (In-Order Traversal):**
    * Perform an **In-Order Traversal** (Left $\to$ Root $\to$ Right) on the input BST.
    * Since it's a BST, this traversal yields the node values in strictly **ascending sorted order**.
    * Store these values in a `vector<int>`.

2.  **Rebuild (Divide and Conquer):**
    * To get a balanced height, the root of any subtree must be the **median** element of the available values.
    * Pick the middle element of the array: `mid = (L + R) / 2`.
    * Create a new node with this value.
    * Recursively build the left subtree using the left half of the array `[L, mid - 1]`.
    * Recursively build the right subtree using the right half of the array `[mid + 1, R]`.

### 2. Execution Visualization
Input Tree: `1 -> 2 -> 3 -> 4`

**Phase 1: Flatten**
* Traverse In-Order: `[1, 2, 3, 4]`.

**Phase 2: Rebuild**
* **Call 1:** Range `[0, 3]`. Mid index `1` (Value **2**). Root is `2`.
    * Left Child: Range `[0, 0]`. Mid index `0` (Value **1**). Node `1`.
    * Right Child: Range `[2, 3]`. Mid index `2` (Value **3**). Node `3`.
        * Right of 3: Range `[3, 3]`. Mid index `3` (Value **4**). Node `4`.

Resulting Structure:
```text
    2
   / \
  1   3
       \
        4
```
(Note: This is balanced. Max depth diff is 1).

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let $A$ be the sorted array of size $N$.
The recursion defines a tree where the root is $A[\lfloor N/2 \rfloor]$.
The height of the resulting tree satisfies the recurrence $H(N) = 1 + H(N/2)$, which implies $H(N) \approx \log_2 N$. This guarantees the balanced property.

### 2. Time Complexity
1.  **In-Order Traversal:** We visit every node once. $O(N)$.
2.  **Reconstruction:** We create a new node for every element in the array exactly once. $O(N)$.

Total Time Complexity:
$$ T(N) = O(N) $$

### 3. Space Complexity
1.  **Vector Storage:** Stores $N$ integers. $O(N)$.
2.  **Recursion Stack:** The reconstruction creates a balanced tree, so stack depth is $O(\log N)$.

Total Space Complexity:
$$ S(N) = O(N) $$

---

## 💻 Implementation (C++)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * TreeNode *left;
 * TreeNode *right;
 * TreeNode() : val(0), left(nullptr), right(nullptr) {}
 * TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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
        root->right = reformTree(nodes, mid + 1, end);
        return root;
    }

    TreeNode* balanceBST(TreeNode* root) {
        vector<int> nodes;
        traverseInOrder(root, nodes);
        return reformTree(nodes, 0, nodes.size() - 1);
    }
};
```

---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).