# Day 54: Count Submatrices with Top-Left Element and Sum Less Than k

- **Difficulty:** Medium
- **Topics:** Array, Matrix, Prefix Sum
- **LeetCode Link:** [Count Submatrices with Top-Left Element and Sum Less Than k](https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given a **0-indexed** integer matrix `grid` and an integer `k`.

Return the number of submatrices that contain the top-left element of the grid, and have a sum less than or equal to `k`.

**Example 1:**
Input: `grid = [[7,6,3],[6,6,1]], k = 18`
Output: `4`
Explanation:
There are only 4 submatrices, starting from the top-left, that have a sum less than or equal to 18:
- `[[7]]` (sum = 7)
- `[[7, 6]]` (sum = 13)
- `[[7], [6]]` (sum = 13)
- `[[7, 6], [6, 6]]` (sum = 25 > 18) -> Invalid.

---

## 🏗️ Deep-Dive Implementation Strategy

This problem inherently queries the sum of elements spanning from the origin `(0,0)` to an arbitrary coordinate `(i, j)`. Recomputing these sums iteratively yields an unscalable $O(N^2 \times M^2)$ bottleneck. The optimal strategy utilizes a **2D Prefix Sum** transformation.

### 1. In-Place 2D Prefix Sum via Inclusion-Exclusion
We iterate through the matrix, transforming each cell `grid[i][j]` to hold the total sum of the submatrix bounded by `(0,0)` and `(i,j)`.
To calculate the new value of `grid[i][j]` using already updated adjacent cells, we apply the mathematical principle of inclusion-exclusion:
1.  **Include Upper Bound:** Add the accumulated sum from directly above: `grid[i-1][j]`.
2.  **Include Left Bound:** Add the accumulated sum from the immediate left: `grid[i][j-1]`.
3.  **Exclude Intersection:** Both the upper and left bounds inherently contain the accumulated sum of the top-left diagonal matrix ending at `(i-1, j-1)`. Because it was added twice, we subtract it once: `- grid[i-1][j-1]`.

By overwriting the input matrix dynamically, we entirely bypass the need for an auxiliary $N \times M$ memory allocation.

### 2. Constraint Evaluation
Since all elements in the given grid are non-negative, the 2D prefix sum is monotonically increasing along both axes. We perform a second linear scan over the modified grid. For every cell where `grid[i][j] <= k`, we increment our valid submatrices counter.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the original matrix be $M \in \mathbb{N}^{R \times C}$. We map $M$ to a prefix sum matrix $P$ such that $P_{i,j} = \sum_{r=0}^{i} \sum_{c=0}^{j} M_{r,c}$.
The recurrence relation utilized for the in-place mapping is:

$$
P_{i,j} = M_{i,j} + P_{i-1,j} + P_{i,j-1} - P_{i-1,j-1}
$$

Boundary conditions evaluate to $0$ for out-of-bounds indices ($i < 0 \lor j < 0$).
The algorithm subsequently evaluates the cardinality of the set $S$:

$$
|S| = \sum_{i=0}^{R-1} \sum_{j=0}^{C-1} \mathbb{I}(P_{i,j} \le k)
$$

Where $\mathbb{I}$ is the indicator function.

### 2. Time Complexity Analysis

The algorithm executes two distinct unnested double-loops over the matrix of dimensions $R \times C$. 
Memory accesses and arithmetic evaluations inside the loops execute in strict $\Theta(1)$ constant time.

$$
T(R, C) = \Theta(R \times C) + \Theta(R \times C) = \Theta(R \times C)
$$

### 3. Space Complexity Analysis

The $R \times C$ accumulation is evaluated directly onto the heap-allocated memory of the input `grid`. No auxiliary data structures are instanced.

$$
S_{aux}(R, C) = \Theta(1)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        for(int i = 0; i < grid.size();i++){
            for(int j = 0; j< grid[0].size(); j++) {
                if (i > 0) grid[i][j] += grid[i-1][j];
                if (j > 0) grid[i][j] +=grid[i][j-1];
                if(i > 0 && j> 0) grid[i][j] -=grid[i-1][j-1];
            }
        }
        int res = 0;
        for(int i = 0; i < grid.size();i++) {
            for(int j = 0; j < grid[0].size();j++){
                if (grid[i][j] <= k) res++;
            }
        }
        return res;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).