# Day 48: Count Square Submatrices with All Ones

- **Difficulty:** Medium
- **Topics:** Array, Dynamic Programming, Matrix
- **LeetCode Link:** [Count Square Submatrices with All Ones](https://leetcode.com/problems/count-square-submatrices-with-all-ones/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a `m * n` matrix of ones and zeros, return how many **square** submatrices have all ones.

**Example 1:**
Input: 
```text
matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
```
Output: `15`
Explanation: 
* There are 10 squares of side 1.
* There are 4 squares of side 2.
* There is 1 square of side 3.
* Total number of squares = 10 + 4 + 1 = 15.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem asks for the total number of square submatrices. A naive approach would check every possible square at every coordinate, leading to an unacceptable $O(N \times M \times \min(N,M))$ time complexity. We optimize this using **Dynamic Programming**.

### 1. DP State Definition
Let the value at `matrix[i][j]` represent the **size of the largest square** whose bottom-right corner is positioned at $(i, j)$. 
Mathematically, if the largest square ending at $(i, j)$ has size $K$, it implies there are exactly $K$ squares ending at $(i, j)$ (one of size $1 \times 1$, one of size $2 \times 2$, $\dots$, one of size $K \times K$). Thus, the size of the maximum square is identical to the number of squares terminating at that specific cell.

### 2. State Transition (The Recurrence Relation)
For any cell where the original value is `1` (and it is not in the 0-th row or 0-th column):
A square of size $K$ ending at $(i, j)$ requires three overlapping squares of size $K-1$ to exist at:
1. Top: $(i-1, j)$
2. Left: $(i, j-1)$
3. Top-Left diagonal: $(i-1, j-1)$

By taking the minimum of these three adjacent DP states and adding 1, we determine the maximum square size for the current cell. We then add this value to a global accumulator `squares`.

### 3. In-Place Memory Optimization
Instead of allocating a separate $N \times M$ DP table, we overwrite the input matrix directly. This architectural decision drops the auxiliary space complexity to pure constant time.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the matrix be $M \in \{0, 1\}^{N \times M}$. We mutate $M$ into a DP state matrix where $M_{i,j}$ evaluates the side length of the maximal square.
The state transition is defined as:

$$
M_{i,j} = \begin{cases} 
M_{i,j} & \text{if } i = 0 \lor j = 0 \\
\min(M_{i-1, j}, M_{i, j-1}, M_{i-1, j-1}) + 1 & \text{if } i > 0 \land j > 0 \land M_{i,j} \ge 1 \\
0 & \text{if } M_{i,j} = 0
\end{cases}
$$

The total number of valid square submatrices is the sum of all elements in the fully evaluated matrix:

$$
\text{Total Squares} = \sum_{i=0}^{N-1} \sum_{j=0}^{M-1} M_{i,j}
$$

### 2. Time Complexity Analysis

The algorithm traverses the 2D matrix exactly once using nested loops. For each cell, the minimum operation is computed in $\Theta(1)$ using immediate array indexing.

$$
T(N, M) = \sum_{i=0}^{N-1} \sum_{j=0}^{M-1} \Theta(1) = \Theta(N \times M)
$$

$$
T(N, M) \in O(N \times M)
$$

### 3. Space Complexity Analysis

Because the input matrix `matrix` is modified in-place to store the dynamic programming states, no additional data structures scaling with the input size are allocated. The algorithm operates strictly with discrete scalar variables (`n`, `m`, `squares`).

$$
S_{aux}(N, M) = \Theta(1)
$$

$$
S_{aux}(N, M) \in O(1)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int squares = 0;
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if (matrix[i][j] == 1) {
                    if (i > 0 && j > 0) {
                        matrix[i][j] = min({matrix[i-1][j-1], matrix[i-1][j], matrix[i][j-1]}) + 1;
                    }
                    squares += matrix[i][j];
                }
            }
        }
        return squares;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).