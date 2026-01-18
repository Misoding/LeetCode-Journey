# Day 3: Largest Magic Square in Grid via 2D Prefix Sums

- **Difficulty:** Medium
- **Topics:** Matrix, Prefix Sum, Dynamic Programming, Greedy
- **LeetCode Link:** [Largest Magic Square](https://leetcode.com/problems/largest-magic-square/)
- **Author:** [Mihail Iazinschi](https://github.com/Misoding)

---

## 📝 Problem Statement

Given an $m \times n$ integer `grid`, a **magic square** is defined as a $k \times k$ subgrid (where $1 \le k \le \min(m, n)$) such that:
1.  The sum of elements in each row is equal.
2.  The sum of elements in each column is equal.
3.  The sum of elements in both the principal diagonal and the secondary diagonal is equal.
4.  All these sums share the same value.

The objective is to find the **largest possible value of $k$** (the side length) of such a subgrid.

---

## 🔬 Formal Algorithmic Analysis

To solve this problem efficiently, we employ the **Prefix Sum** technique extended to multiple dimensions. This reduces the cost of range sum queries from linear time to constant time.

### 1. Mathematical Abstraction & Preprocessing

Let $G$ be the input matrix of size $m \times n$. We define four auxiliary matrices to store cumulative sums, allowing for $O(1)$ retrieval of subarray sums.

**A. Row Prefix Sum ($P_{row}$):**

$$
P_{row}[i][j] = \sum_{c=0}^{j} G[i][c]
$$

Recurrence relation:

$$
P_{row}[i][j] = \begin{cases} G[i][0] & \text{if } j=0 \\ P_{row}[i][j-1] + G[i][j] & \text{if } j > 0 \end{cases}
$$

Query: The sum of a row segment in row $i$ from column $c_1$ to $c_2$ is:

$$
\text{Sum} = P_{row}[i][c_2] - P_{row}[i][c_1-1]
$$

**B. Column Prefix Sum ($P_{col}$):**

$$
P_{col}[i][j] = \sum_{r=0}^{i} G[r][j]
$$

Recurrence relation:

$$
P_{col}[i][j] = P_{col}[i-1][j] + G[i][j]
$$

**C. Principal Diagonal Prefix Sum ($P_{diag}$):**

$$
P_{diag}[i][j] = \sum_{k=0}^{\min(i,j)} G[i-k][j-k]
$$

Recurrence relation:

$$
P_{diag}[i][j] = P_{diag}[i-1][j-1] + G[i][j]
$$

**D. Secondary Diagonal Prefix Sum ($P_{anti}$):**

$$
P_{anti}[i][j] = \sum_{k=0}^{\min(i, n-1-j)} G[i-k][j+k]
$$

Recurrence relation:

$$
P_{anti}[i][j] = P_{anti}[i-1][j+1] + G[i][j]
$$

### 2. Search Strategy

We adopt a **Greedy** approach regarding the size $k$. We iterate $k$ from the maximum possible dimension ($\min(m, n)$) down to 1. The first $k$ for which we find a valid magic square is guaranteed to be the maximum.

For a fixed size $k$, we iterate through all possible top-left corners $(i, j)$ where $0 \le i \le m-k$ and $0 \le j \le n-k$.

### 3. Validity Verification

For a candidate subgrid of size $k$ at $(i, j)$, let the target sum $S$ be the sum of the first row. We then verify:

1.  **Rows:** $\forall r \in [0, k-1]$, $\text{Sum}(Row_{i+r}) = S$. (Cost: $k$ comparisons)
2.  **Columns:** $\forall c \in [0, k-1]$, $\text{Sum}(Col_{j+c}) = S$. (Cost: $k$ comparisons)
3.  **Diagonals:**
    * Principal: $P_{diag}[i+k-1][j+k-1] - P_{diag}[i-1][j-1] = S$
    * Secondary: $P_{anti}[i+k-1][j] - P_{anti}[i-1][j+k] = S$
    * Cost: $O(1)$

### 4. Complexity Calculation

**Time Complexity Analysis:**

Let $K = \min(m, n)$.
1.  **Preprocessing:** $\Theta(m \cdot n)$
2.  **Search Phase:** The nested loops iterate roughly $m \cdot n$ times for each size $k$. The verification takes $O(k)$.

$$
T_{search} \approx \sum_{k=1}^{K} (m-k)(n-k) \cdot 2k
$$

Approximating via integration, the worst-case time complexity is:

$$
T(m, n) \in O(m \cdot n \cdot \min(m, n)^2)
$$

**Space Complexity Analysis:**

We use 4 auxiliary matrices of size $m \times n$.

$$
S(m, n) \in \Theta(m \cdot n)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:

    void calcRowPrefixSum(vector<vector<int>>& originalGrid,
                          vector<vector<int>>& row_grid,
                          int& m,
                          int& n) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0) {
                    row_grid[i][j] = originalGrid[i][j];
                    continue;
                }
                row_grid[i][j] = row_grid[i][j-1] + originalGrid[i][j];
            }
        }
    }

    void calcColumnPrefixSum(vector<vector<int>>& originalGrid,
                             vector<vector<int>>& column_grid,
                             int& m,
                             int& n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == 0) {
                    column_grid[j][i] = originalGrid[j][i];
                    continue;
                }
                column_grid[j][i] = column_grid[j-1][i] + originalGrid[j][i];
            }
        }
    }

    void calcPrincipalDiagonalSum(vector<vector<int>>& originalGrid,
                                  vector<vector<int>>& principalDiagonal,
                                  int& m,
                                  int& n) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 || j == 0) {
                    principalDiagonal[i][j] = originalGrid[i][j];
                    continue;
                }
                principalDiagonal[i][j] = principalDiagonal[i-1][j-1] + originalGrid[i][j];
            }
        }
    }

    void calcSecondaryDiagonalSum(vector<vector<int>>& originalGrid,
                                  vector<vector<int>>& secondaryDiagonal,
                                  int& m,
                                  int& n) {
        for (int i = 0; i < m; i++) {
           for (int j = n-1; j >= 0; j--) {
                if (j == n-1 || i == 0) {
                    secondaryDiagonal[i][j] = originalGrid[i][j];
                    continue;
                }
                secondaryDiagonal[i][j] = secondaryDiagonal[i-1][j+1] + originalGrid[i][j];
           }
        }
    }

    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int squareDimension = min(m,n);
        int oneSum, prevRowSum, prevColSum;
        bool validSquare;
        
        vector<vector<int>> rowPrefixSum(m, vector<int>(n));
        vector<vector<int>> columnPrefixSum(m, vector<int>(n));
        vector<vector<int>> principalDiagonalSum(m, vector<int>(n));
        vector<vector<int>> secondaryDiagonal(m, vector<int>(n));

        calcRowPrefixSum(grid, rowPrefixSum, m, n);
        calcColumnPrefixSum(grid, columnPrefixSum, m, n);
        calcPrincipalDiagonalSum(grid, principalDiagonalSum, m, n);
        calcSecondaryDiagonalSum(grid, secondaryDiagonal, m, n);

        for (int edge = squareDimension; edge > 0; edge--) {
            for (int i = 0; i <= m - edge; i++) {
                for (int j = 0; j <= n - edge; j++) {
                    validSquare = true;
                    prevRowSum = 0;
                    if (j > 0) {
                        prevRowSum = rowPrefixSum[i][j-1]; 
                    }
                    oneSum = rowPrefixSum[i][j + edge-1] - prevRowSum;
                    for (int sqRow = 0; sqRow < edge; sqRow++) {
                        prevRowSum = 0;
                        if (j > 0) {
                            prevRowSum = rowPrefixSum[i + sqRow][j-1];
                        }
                        if (rowPrefixSum[i + sqRow][j + edge - 1] - prevRowSum != oneSum) {
                            validSquare = false;
                            break;
                        }
                    }
                    if (!validSquare) continue;
                    for (int sqCol = 0; sqCol < edge; sqCol++) {
                        prevColSum = 0;
                        if (i > 0) {
                            prevColSum = columnPrefixSum[i-1][j + sqCol];
                        }
                        if (columnPrefixSum[i + edge - 1][j + sqCol] - prevColSum != oneSum) {
                            validSquare = false;
                            break;
                        }
                    }
                    if (!validSquare) continue;
                    int prevPrincipalSum = 0, prevSecondarySum = 0;
                    if (i != 0 && j != 0) {
                      prevPrincipalSum = principalDiagonalSum[i-1][j-1];
                    }
                    if (i != 0 && (j + edge) < n) {
                        prevSecondarySum = secondaryDiagonal[i-1][j+edge];
                    }
                    
                    if (principalDiagonalSum[i + edge-1][j + edge-1] - prevPrincipalSum != oneSum ||
                        secondaryDiagonal[i + edge-1][j] - prevSecondarySum != oneSum ){
                            continue;
                        }
                    
                    return edge;
                }
            }
        }
        return 1;
    }
};
```

### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).
