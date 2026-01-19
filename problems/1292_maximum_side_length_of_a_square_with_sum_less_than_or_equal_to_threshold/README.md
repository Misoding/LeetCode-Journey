# Day 4: Maximum Side Length of a Square with Sum Less than or Equal to Threshold

- **Difficulty:** Medium
- **Topics:** Array, Matrix, Binary Search, Prefix Sum
- **LeetCode Link:** [Maximum Side Length of a Square](https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/)
- **Author:** [Mihail Iazinschi](https://github.com/Misoding)

---

## 📝 Problem Statement

Given an $m \times n$ matrix `mat` and an integer `threshold`, return the maximum side-length of a square with a sum less than or equal to `threshold` or return 0 if no such square exists.

The side length $k$ must satisfy $1 \le k \le \min(m, n)$.

---

## 🔬 Formal Algorithmic Analysis

To solve this problem efficiently, we combine **2D Prefix Sums** for $O(1)$ subgrid sum queries with **Binary Search** on the answer (the side length).

### 1. Mathematical Abstraction (2D Prefix Sums)

Let $M$ be the input matrix. We transform $M$ in-place into a Prefix Sum Matrix $P$, where $P[i][j]$ represents the sum of the rectangle defined by the top-left corner $(0,0)$ and bottom-right corner $(i,j)$.

The recurrence relation for building the prefix sum matrix is:

$$
P[i][j] = M[i][j] + P[i-1][j] + P[i][j-1] - P[i-1][j-1]
$$


**Query Formulation:**
To calculate the sum of a square subgrid defined by its bottom-right corner $(r, c)$ and side length $k$, we use the Inclusion-Exclusion principle. The top-left corner corresponds to $(r-k+1, c-k+1)$.
Let $(r', c') = (r-k, c-k)$. The sum $S$ is given by:

$$
S = P[r][c] - P[r'][c] - P[r][c'] + P[r'][c']
$$

*(Note: Boundary checks for indices $< 0$ are required in implementation).*

### 2. Search Strategy (Binary Search)

The function $f(k) = \text{"Exists a square of size } k \text{ with sum } \le \text{Threshold"}$ is monotonic.
* If a valid square of size $k$ exists, it does not strictly imply $k+1$ is valid, but we are looking for the *maximum*.
* We define the search space for the side length $k$ as $[1, \min(m, n)]$.

Algorithm:
1.  **Midpoint Calculation:** Let $mid = \lfloor \frac{low + high}{2} \rfloor$.
2.  **Feasibility Check:** We iterate through all possible top-left corners $(i, j)$ such that a square of size $mid$ fits in the matrix. We verify if the sum of any such square is $\le$ `threshold`.
3.  **Space Reduction:**
    * If valid: Try larger squares ($low = mid + 1$, store result).
    * If invalid: Try smaller squares ($high = mid - 1$).

### 3. Complexity Calculation

**Time Complexity Analysis:**
Let $m$ and $n$ be the dimensions of the matrix.
1.  **Preprocessing:** Iterating through the matrix to compute prefix sums takes $\Theta(m \cdot n)$.
2.  **Binary Search:** The range is $L = \min(m, n)$. The loop runs $\log L$ times.
3.  **Feasibility Check:** Inside each binary search step, we iterate through roughly $m \cdot n$ possible positions.

Total Complexity:

$$
T(m, n) = \Theta(m \cdot n) + O(m \cdot n \cdot \log(\min(m, n)))
$$

$$
T(m, n) \in O(m \cdot n \cdot \log(\min(m, n)))
$$

**Space Complexity Analysis:**
The implementation performs the prefix sum calculation **in-place** (modifying the input `mat`), requiring no significant extra space beyond loop variables.

$$
S(m, n) \in O(1)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = mat.size();
        int m = mat[0].size();
        int squareEdgeMax = min(n,m), squareEdgeMin = 1;
        int sqSum, end_sq_i, end_sq_j;
        vector<vector<int>> row_prefix_sum(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == 0) {
                    continue;
                }
                mat[i][j]+=mat[i][j-1];
            }
        }
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0){
                    continue;
                }
                mat[i][j] += mat[i-1][j];
            }
        }
        int resEdge = 0;
        while (squareEdgeMin <= squareEdgeMax) {
            int midEdge = squareEdgeMin + (squareEdgeMax - squareEdgeMin) / 2;
            bool valid = false;
            for(int i = 0; i <= n - midEdge; i++) {
                for (int j = 0; j <= m - midEdge; j++) {
                    end_sq_i = i + midEdge - 1;
                    end_sq_j = j + midEdge - 1;
                    sqSum = mat[end_sq_i][end_sq_j];
                    if (i > 0) {
                        sqSum -= mat[i-1][end_sq_j];
                    }
                    if (j > 0) {
                        sqSum -= mat[end_sq_i][j-1];
                    }
                    if (i > 0 && j > 0) {
                        sqSum += mat[i-1][j-1];
                    }
                    if (sqSum <= threshold) {
                        valid = true;
                        break;
                    }
                }
                if (valid) break;
            }
            if(valid) {
                resEdge = midEdge;
                squareEdgeMin = midEdge + 1;
            } else {
                squareEdgeMax = midEdge - 1;
            }
        }
        return resEdge;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).