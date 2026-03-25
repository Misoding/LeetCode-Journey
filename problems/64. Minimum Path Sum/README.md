# Day 58: Minimum Path Sum

- **Difficulty:** Medium
- **Topics:** Array, Dynamic Programming, Matrix
- **LeetCode Link:** [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a `m x n` grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

**Note:** You can only move either down or right at any point in time.

**Example 1:**
Input: `grid = [[1,3,1],[1,5,1],[4,2,1]]`
Output: `7`
Explanation: Because the path `1 -> 3 -> 1 -> 1 -> 1` minimizes the sum.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem guarantees movement in only two directions: down or right. In a reversed Top-Down execution (starting from the destination and moving backwards to the origin), this translates to moving strictly **up** or **left**.

### 1. Optimal Substructure
To find the minimum path sum to reach cell `(i, j)`, we must evaluate the minimum path sums of its immediate predecessors:
* The cell directly above it: `(i-1, j)`
* The cell directly to its left: `(i, j-1)`

The optimal sum at `(i, j)` is strictly the value of the current cell plus the minimum of these two preceding optimal paths.

### 2. Base Cases and Boundary Enforcement
* **Origin:** When the recursion reaches `(0, 0)`, the path terminates. The cost is simply `grid[0][0]`.
* **Out of Bounds:** If the recursion steps outside the matrix (`i < 0` or `j < 0`), it returns `INT_MAX`. This acts as an infinite penalty, mathematically ensuring the `min()` function in the recursive step will always select the valid inbound path.

### 3. State Memoization
A binary decision tree of depth $N+M$ leads to $O(2^{N+M})$ time complexity due to overlapping subproblems. A 2D `dp` matrix intercepts these redundant branches. Once a state `dp[i][j]` is calculated, subsequent recursive calls targeting `(i, j)` immediately return the cached scalar in $O(1)$ time.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the cost matrix be $M \in \mathbb{N}^{R \times C}$. We define $DP(i, j)$ as the minimal accumulated cost from $(0,0)$ to $(i, j)$.
The state transition mapping is:

$$
DP(i, j) = \begin{cases} 
\infty & \text{if } i < 0 \lor j < 0 \\
M_{0,0} & \text{if } i = 0 \land j = 0 \\
M_{i,j} + \min(DP(i-1, j), DP(i, j-1)) & \text{otherwise}
\end{cases}
$$

The target state is $DP(R-1, C-1)$.

### 2. Time Complexity Analysis

The DP parameters are bounded by the matrix dimensions $R$ and $C$.
The memoization table limits the recursive evaluations strictly to the number of cells. Each cell performs a $\Theta(1)$ addition and minimum comparison.

$$
T(R, C) = \Theta(R \times C)
$$

$$
T(R, C) \in O(R \times C)
$$

### 3. Space Complexity Analysis

The implementation utilizes auxiliary space for:
1.  **Memoization Matrix:** A 2D `vector` of dimensions $(R+1) \times (C+1)$, filled with `-1`.
2.  **Call Stack:** The maximum depth of the DFS recursion correlates to the longest path from `(R-1, C-1)` to `(0, 0)`, which is exactly $R + C - 1$ stack frames.

$$
S_{aux}(R, C) = \Theta(R \times C) + \Theta(R + C) = \Theta(R \times C)
$$

$$
S_{aux}(R, C) \in O(R \times C)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int solveDp(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp){
        if(i < 0 || j < 0) {
            return INT_MAX;
        }
        if (i == 0 && j == 0) {
            return grid[i][j];
        }
        if (dp[i][j] != -1) return dp[i][j];
        int topStep = solveDp(grid, i-1, j, dp);
        int leftStep = solveDp(grid, i, j-1, dp);
        dp[i][j] = grid[i][j] + min(topStep, leftStep);
        return dp[i][j];
    }
    int minPathSum(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid.size()+1, vector<int>(grid[0].size()+1, -1));
        return solveDp(grid, grid.size()-1, grid[0].size()-1, dp);
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).