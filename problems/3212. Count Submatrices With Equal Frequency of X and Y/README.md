# Day 55: Count Submatrices With Equal Frequency of X and Y

- **Difficulty:** Medium
- **Topics:** Array, Matrix, Prefix Sum, Bit Manipulation
- **LeetCode Link:** [Count Submatrices With Equal Frequency of X and Y](https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a 2D character matrix `grid`, where `grid[i][j]` is either `'X'`, `'Y'`, or `'.'`, return the number of submatrices that contain:
1. `grid[0][0]` (meaning they start at the top-left corner).
2. An **equal** frequency of `'X'` and `'Y'`.
3. At least **one** `'X'`.

**Example 1:**
Input: `grid = [["X","Y","."],["Y",".","."]]`
Output: `3`

---

## 🏗️ Deep-Dive Implementation Strategy

This problem demands a 2D Prefix Sum to dynamically query the frequency of both `'X'` and `'Y'` for any submatrix originating at `(0,0)`. While a standard approach uses an array of structures (like `std::pair<int, int>`), we can achieve superior memory locality and ALU performance via **Bit Packing**.

### 1. Register-Level Parallelism (Bit Packing)
Instead of processing the counts of `'X'` and `'Y'` separately, we pack them into a single 64-bit unsigned integer (`uint64_t`).
* We shift the `'X'` count to the upper 32 bits: `currentIntX << 32`.
* We place the `'Y'` count in the lower 32 bits.
* The combined state is `(X << 32) | Y`.

Since the maximum grid size is $1000 \times 1000$, the maximum possible frequency is $1,000,000$. A 32-bit integer can hold up to $\sim 2.14 \times 10^9$. Therefore, **mathematical overflow from the lower 32 bits (Y) into the upper 32 bits (X) is strictly impossible**. 
This allows us to perform 2D Prefix Sum arithmetic (`+=`, `-=`) on the 64-bit integer directly, calculating the prefix sums of both `'X'` and `'Y'` simultaneously in a single CPU clock cycle.

### 2. State Extraction and Validation
During the secondary linear scan to validate the constraints:
* **Extract X:** `transformed[i][j] >> 32`
* **Extract Y:** `(transformed[i][j] << 32) >> 32` (Shifting left erases the upper bits, shifting right restores the lower bits to their original magnitude).
* **Constraints:** We check if `X == Y` and `X > 0`. If true, we increment our valid submatrix counter.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $M \in \{X, Y, \cdot\}^{R \times C}$. We map this to a prefix sum matrix $P$ where each element $P_{i,j}$ encodes a vector $\vec{v} = (count_X, count_Y)$.
Using a scalar $P'_{i,j} \in \mathbb{N}^{64}$, the vector addition is modeled as:

$$
P'_{i,j} = M'_{i,j} + P'_{i-1,j} + P'_{i,j-1} - P'_{i-1,j-1}
$$

Because $\max(count_Y) \le 10^6 < 2^{32}$, the addition operates isomorphically to the vector space $\mathbb{N}^2$.
The algorithm evaluates the cardinality of the set $S$:

$$
|S| = \sum_{i=0}^{R-1} \sum_{j=0}^{C-1} \mathbb{I} \left( \lfloor \frac{P'_{i,j}}{2^{32}} \rfloor = (P'_{i,j} \bmod 2^{32}) \land \lfloor \frac{P'_{i,j}}{2^{32}} \rfloor > 0 \right)
$$

### 2. Time Complexity Analysis

The algorithm executes two distinct unnested double-loops over the matrix of dimensions $R \times C$. 
Memory accesses and packed bitwise arithmetic inside the loops execute in strict $\Theta(1)$ constant time.

$$
T(R, C) = \Theta(R \times C) + \Theta(R \times C) = \Theta(R \times C)
$$

### 3. Space Complexity Analysis

An auxiliary matrix of dimensions $R \times C$ of type `uint64_t` is allocated to store the transformed prefix sums.

$$
S_{aux}(R, C) = \Theta(R \times C)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Allocate a 64-bit matrix to pack both X and Y states
        vector<vector<uint64_t>> transformed(rows, vector<uint64_t>(cols, 0));
        
        // 1. Inclusion-Exclusion 2D Prefix Sum via ALU Bit Packing
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                uint64_t currentIntX = grid[i][j] == 'X' ? 1ULL : 0;
                uint64_t currentIntY = grid[i][j] == 'Y' ? 1ULL : 0;
                
                // Pack X into upper 32 bits, Y into lower 32 bits
                transformed[i][j] = (currentIntX << 32) | currentIntY;
                
                // Native 64-bit arithmetic computes both prefix sums simultaneously
                if (i > 0) transformed[i][j] += transformed[i-1][j];
                if (j > 0) transformed[i][j] += transformed[i][j-1];
                if (i > 0 && j > 0) transformed[i][j] -= transformed[i-1][j-1];
            }
        }
        
        int countSubMatrices = 0;
        
        // 2. State Decoding and Constraint Validation
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++) {
                // Extract X by shifting down. Extract Y by shifting out X, then shifting down.
                uint64_t countX = transformed[i][j] >> 32;
                uint64_t countY = (transformed[i][j] << 32) >> 32;
                
                if (countX == countY && countX > 0) {
                    countSubMatrices++;
                }
            }
        }
        
        return countSubMatrices;
    }
};
```

---
### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).