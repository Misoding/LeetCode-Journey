# Day 34: Sum of Root To Leaf Binary Numbers

- **Difficulty:** Easy
- **Topics:** Tree, Depth-First Search, Binary Tree, Bit Manipulation
- **LeetCode Link:** [Sum of Root To Leaf Binary Numbers](https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given the `root` of a binary tree where each node has a value `0` or `1`. Each root-to-leaf path represents a binary number starting with the most significant bit.

For example, if the path is `0 -> 1 -> 1 -> 0 -> 1`, then this could represent `01101` in binary, which is `13`.

For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return the **sum of these numbers**. The test cases are generated so that the answer fits in a 32-bits integer.

**Example:**
Input: `root = [1,0,1,0,1,0,1]`
Output: `22`
Explanation: 
* Path 1: `1->0->0` = `100` (4)
* Path 2: `1->0->1` = `101` (5)
* Path 3: `1->1->0` = `110` (6)
* Path 4: `1->1->1` = `111` (7)
Sum: 4 + 5 + 6 + 7 = 22

---

## 🏗️ Deep-Dive Implementation Strategy

The problem requires us to traverse every path from the root to the leaves and accumulate a running value. This is a classic **Depth-First Search (DFS)** scenario.



### 1. Bitwise Accumulation
As we traverse down a path, appending a bit to the right of a binary number is mathematically equivalent to multiplying the current number by 2 and adding the new bit. In bitwise operations, this is highly efficient:
* **Shift Left (`<< 1`):** Multiplies the number by 2, creating a `0` at the Least Significant Bit (LSB).
* **Bitwise OR (`| val`):** Sets the LSB to the current node's value (`0` or `1`).

### 2. The DFS Traversal Logic
1.  **State Management:** We pass the current accumulated value (`comulatedNum`) *by value* to the recursive calls. This ensures that going down the left subtree does not affect the state passed to the right subtree.
2.  **Base Case:** If a node is `nullptr`, we simply return.
3.  **Leaf Detection:** If a node has no left and no right child, we have reached the end of a valid path. We add the `comulatedNum` to the global `totalSum` (passed by reference) and return.
4.  **Recursion:** We recursively call the helper function on the left and right children.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $P(v)$ be the integer value represented by the path from the root to node $v$.
The recursive definition of the path value is:

$$
P(root) = root \rightarrow val
$$

For any non-root node $v$ with parent $u$:

$$
P(v) = P(u) \cdot 2 + v \rightarrow val
$$

Using bitwise arithmetic, this recurrence is precisely:

$$
P(v) = (P(u) \ll 1) \lor v \rightarrow val
$$

The final objective is to sum $P(l)$ for all $l \in L$, where $L$ is the set of all leaf nodes.

### 2. Time Complexity Analysis

The DFS visits every node in the binary tree exactly once. The operations performed at each node (bitwise shift, bitwise OR, addition, comparisons) execute in $\Theta(1)$ constant time. Let $N$ be the number of nodes.

$$
T(N) = \sum_{v \in V} \Theta(1) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The space complexity is bounded by the maximum depth of the recursion stack, which corresponds to the height of the tree $H$.
In the worst case (a completely skewed tree), $H = N$.
In the best case (a perfectly balanced tree), $H = \log_2 N$.

$$
S(N) = \Theta(H)
$$

$$
S(N) \in O(N) \quad \text{(Worst Case)}
$$

---

## 💻 Implementation (C++)

```cpp
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
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).