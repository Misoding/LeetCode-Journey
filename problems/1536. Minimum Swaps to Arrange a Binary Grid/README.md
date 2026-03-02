# Day 40: Minimum Swaps to Arrange a Binary Grid

- **Difficulty:** Medium
- **Topics:** Array, Greedy, Matrix
- **LeetCode Link:** [Minimum Swaps to Arrange a Binary Grid](https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given an `n x n` binary grid, in one step you can choose two **adjacent rows** of the grid and swap them.

A grid is said to be **valid** if all the cells above the main diagonal are `0`s.

Return the minimum number of steps needed to make the grid valid, or `-1` if the grid cannot be valid.

**Example 1:**
Input: `grid = [[0,0,1],[1,1,0],[1,0,0]]`
Output: `3`

---

## 🏗️ Deep-Dive Implementation Strategy

The requirement "all cells above the main diagonal are zeros" means that for any row $i$ (0-indexed), all elements from column $i+1$ to $n-1$ must be `0`. 
This translates to a single unified constraint: **The rightmost `1` in row $i$ must be at an index $\le i$.**

### 1. Dimensionality Reduction (Preprocessing)
Instead of moving entire rows of arrays and checking the 2D matrix repeatedly, we can map each row to a single integer representing the position of its rightmost `1`.
* Iterate through each row from right to left.
* Record the index of the first `1` encountered. If a row contains all `0`s, we record `-1`.
* Store these values in a 1D array `maxRightIndexes`.

### 2. Greedy Adjacent Swapping
We need to sort the `maxRightIndexes` array such that for every index $i$, `maxRightIndexes[i] <= i`. We can only swap adjacent elements.
To minimize the number of swaps, we apply a **Greedy Choice**:
* For a target row index $i$, we look for the *first* available row $j \ge i$ that satisfies the condition `maxRightIndexes[j] <= i`.
* Why the first? Because picking a row further down would require more adjacent swaps to bubble it up to position $i$, which is strictly suboptimal.
* Once found, we bubble this row up from $j$ to $i$, incrementing our `steps` counter by 1 for each adjacent swap.
* If no such row $j$ exists for a given $i$, the grid cannot be made valid, and we return `-1`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the matrix be $M \in \{0, 1\}^{n \times n}$. We define a mapping vector $R$ of size $n$, where:

$$
R_k = \max(\{c \mid M_{k,c} = 1\} \cup \{-1\})
$$

The matrix $M$ is valid if and only if:

$$
\forall i \in \{0, \dots, n-1\}, \quad R_i \le i
$$

The allowed operation is the transposition of adjacent elements in $R$: $(R_k, R_{k+1}) \to (R_{k+1}, R_k)$. 
The problem reduces to finding the minimum number of adjacent transpositions to satisfy the condition constraint, identical to computing the inversion distance for a specific greedy permutation constraint.

### 2. Time Complexity Analysis

1. **Preprocessing:** We iterate through the $n \times n$ matrix once to compute $R$. This takes $\Theta(n^2)$.
2. **Greedy Swapping:** For each position $i$ from $0$ to $n-1$, we search forward for a valid row $j$. In the worst case, $j = n-1$. The inner `while` loop for bubbling up takes $j - i$ steps. 
The total number of swaps across all iterations is at most $\frac{n(n-1)}{2}$.

$$
T(n) = \Theta(n^2) + O(n^2) = \Theta(n^2)
$$

Given $n \le 200$, $n^2 \le 40,000$, well within standard competitive programming limits.

### 3. Space Complexity Analysis

We allocate a 1D vector `maxRightIndexes` of size $n$ to store the condensed row states.

$$
S(n) = \Theta(n)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> maxRightIndexes;
        for(int i = 0; i<n; i++) {
            int rightPos = -1;
            for(int r = n-1; r>=0;r--){
                if(grid[i][r]) {
                    rightPos = r;
                    break;
                }
            }
            maxRightIndexes.push_back(rightPos);
        }
        int steps = 0;
        for (int i = 0; i < n; i++) {
            int j = i;
            while (j < n && maxRightIndexes[j] > i) {
                j++;
            }
            if (j >= n) return -1;
            while(j>i) {
                swap(maxRightIndexes[j], maxRightIndexes[j-1]);
                swap(grid[j], grid[j-1]);
                steps++;
                j--;
            }
        }       
        return steps;


    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).