# Day 8: Binary Tree Level Order Traversal

- **Difficulty:** Medium
- **Topics:** Tree, Breadth-First Search (BFS), Queue, Hash Table
- **LeetCode Link:** [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
- **Author:** [Mihail Iazinschi (LinkedIn)](https://www.linkedin.com/in/misoding)
---

## 📝 Problem Statement

Given the `root` of a binary tree, return the **level order traversal** of its nodes' values. (i.e., from left to right, level by level).

**Example:**
Input: `root = [3, 9, 20, null, null, 15, 7]`
```text
    3
   / \
  9  20
    /  \
   15   7
```
Output: `[[3], [9, 20], [15, 7]]`

---

## Deep-Dive Implementation Strategy

The problem requires visiting nodes layer by layer. While Depth-First Search (DFS) processes branches deeply, **Breadth-First Search (BFS)** is the natural choice for level-wise processing.

### 1. Data Structures & State Management
To implement BFS and group nodes by their depth, we utilize:
1.  **Queue of Pairs:** `std::queue<pair<int, TreeNode*>>`
    * Stores `{depth_level, node_pointer}`.
    * Ensures First-In-First-Out (FIFO) processing, crucial for maintaining horizontal order.
2.  **Hash Map:** `unordered_map<int, vector<int>>`
    * Keys represent the `depth_level`.
    * Values are vectors collecting nodes at that specific depth.
    * *Note:* This specific implementation decouples the traversal logic from the result construction, allowing nodes to be processed in a stream and grouped lazily.

### 2. Execution Visualization

Let's trace the execution for the tree `[3, 9, 20]`.

**Step 1: Initialization**
* Push Root: `queue = [(0, Node(3))]`

**Step 2: Processing Node 3 (Level 0)**
* Pop `(0, 3)`.
* **Map Update:** `map[0].push_back(3)` $\rightarrow$ `{0: [3]}`.
* **Children Push:**
    * Left: Push `(1, 9)`
    * Right: Push `(1, 20)`
* **Queue State:** `[(1, 9), (1, 20)]`

**Step 3: Processing Node 9 (Level 1)**
* Pop `(1, 9)`.
* **Map Update:** `map[1].push_back(9)` $\rightarrow$ `{0: [3], 1: [9]}`.
* **Children Push:** None (Leaf).
* **Queue State:** `[(1, 20)]`

**Step 4: Processing Node 20 (Level 1)**
* Pop `(1, 20)`.
* **Map Update:** `map[1].push_back(20)` $\rightarrow$ `{0: [3], 1: [9, 20]}`.
* **Children Push:** (If any).

### 3. Reconstruction
After the queue is empty, we iterate linearly (`i = 0, 1, 2...`) to extract vectors from the map and build the final `vector<vector<int>>`.

---

## 🔬 Formal Algorithmic Analysis

We model the binary tree as a directed acyclic graph $G = (V, E)$, where $V$ is the set of nodes and $|V| = N$.

### 1. Mathematical Model of BFS

The algorithm traverses the graph starting from $root$. Let $L_k$ be the set of nodes at depth $k$.
The queue invariant guarantees that if node $u \in L_k$ enters the queue before $v \in L_k$, then $u$ is processed before $v$. Furthermore, all nodes in $L_k$ are processed before any node in $L_{k+1}$.

The operation performed on each node $v$ is:

$$
\Phi(v) = \text{Extract}(v) + \text{MapInsert}(v.val) + \sum_{u \in children(v)} \text{Insert}(u)
$$

### 2. Time Complexity Derivation

We calculate the total work by summing the cost of operations over all nodes.

**A. Traversal Cost:**
Each node $v \in V$ is:
1.  Pushed into the queue exactly once.
2.  Popped from the queue exactly once.
3.  Inserted into the `unordered_map` exactly once.

$$
T_{traversal} = \sum_{v \in V} (C_{push} + C_{pop} + C_{map\_insert})
$$

Assuming the hash map provides amortized $O(1)$ insertion:

$$
T_{traversal} = \sum_{v \in V} O(1) = O(N)
$$

**B. Reconstruction Cost:**
We iterate from level $0$ to $H$ (height of tree). Retrieving elements from the map and moving them to the final vector visits each element once more.

$$
T_{reconstruct} = \sum_{k=0}^{H} |L_k| = |V| = N
$$

**Total Time Complexity:**

$$
T(N) = T_{traversal} + T_{reconstruct} \approx 2N
$$

$$
T(N) \in \Theta(N)
$$

### 3. Space Complexity Analysis

We analyze the auxiliary memory usage:

1.  **Queue Storage:** In the worst case (a complete binary tree), the queue holds the leaf level, which contains approx $N/2$ nodes.
    $$S_{queue} \approx \frac{N}{2}$$
2.  **Map Storage:** The map stores every node value exactly once.
    $$S_{map} = N$$
3.  **Output Structure:** The result vector stores $N$ integers.

$$
S(N) = S_{queue} + S_{map} \approx 1.5N
$$

$$
S(N) \in \Theta(N)
$$

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
```

---

### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).
