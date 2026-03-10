# Day 47: Edit Distance

- **Difficulty:** Medium
- **Topics:** String, Dynamic Programming
- **LeetCode Link:** [Edit Distance](https://leetcode.com/problems/edit-distance/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given two strings `word1` and `word2`, return the minimum number of operations required to convert `word1` to `word2`.

You have the following three operations permitted on a word:
1. Insert a character
2. Delete a character
3. Replace a character

**Example 1:**
Input: `word1 = "horse", word2 = "ros"`
Output: `3`
Explanation: 
* horse -> rorse (replace 'h' with 'r')
* rorse -> rose (delete 'r')
* rose -> ros (delete 'e')

---

## 🏗️ Deep-Dive Implementation Strategy

The problem seeks the shortest path between two string states, which is mathematically known as the **Levenshtein Distance**. Since computing this requires making discrete choices that lead to overlapping subproblems, **Dynamic Programming** is the optimal strategy.

### 1. Top-Down Memoization (DFS)
The algorithm evaluates the strings from left to right using two pointers, `idx1` and `idx2`.
* **Match:** If `word1[idx1] == word2[idx2]`, no operation is needed. We simply advance both pointers without adding to the cost.
* **Mismatch:** If the characters differ, we branch into three parallel universes, each representing an allowed operation, and add `1` to the cost:
  1.  **Replace:** Advance both pointers `(idx1 + 1, idx2 + 1)`.
  2.  **Insert:** Conceptually insert `word2[idx2]` into `word1`. This matches the character in `word2`, so we advance `idx2`, but `idx1` remains at its current position `(idx1, idx2 + 1)`.
  3.  **Delete:** Conceptually delete `word1[idx1]`. We advance `idx1` to skip the character, but `idx2` remains `(idx1 + 1, idx2)`.
* **Memoization:** To prevent the exponential $O(3^N)$ blowup of the recursion tree, we cache the result of every unique `(idx1, idx2)` state in a 2D `dp` matrix.

### 2. Base Cases
* If `idx1` reaches the end of `word1`, the only way to match `word2` is to **insert** all its remaining characters: return `word2.length() - idx2`.
* If `idx2` reaches the end of `word2`, the only way to match `word2` is to **delete** all remaining characters in `word1`: return `word1.length() - idx1`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $DP(i, j)$ be the minimum edit distance between the suffixes $w_1[i \dots M]$ and $w_2[j \dots N]$.
The state transition equation is:

$$
DP(i, j) = \begin{cases} 
N - j & \text{if } i = M \\
M - i & \text{if } j = N \\
DP(i+1, j+1) & \text{if } w_1[i] = w_2[j] \\
1 + \min \begin{cases} 
DP(i+1, j+1) \quad (\text{Replace}) \\
DP(i, j+1) \quad (\text{Insert}) \\
DP(i+1, j) \quad (\text{Delete})
\end{cases} & \text{if } w_1[i] \neq w_2[j]
\end{cases}
$$

### 2. Time Complexity Analysis

The state space is defined by the parameters `idx1` and `idx2`. `idx1` ranges from $0$ to $M$ (length of `word1`), and `idx2` ranges from $0$ to $N$ (length of `word2`).
Because of the memoization table `dp`, each unique state $(i, j)$ is computed exactly once. The operations within each state calculation take $\Theta(1)$ constant time.

$$
T(M, N) = \Theta(M \times N)
$$

### 3. Space Complexity Analysis

The algorithm requires auxiliary memory for:
1.  **The DP Table:** A 2D matrix of dimensions $(M+1) \times (N+1)$ initialized to `-1`.
2.  **The Recursion Stack:** In the worst case (e.g., all inserts or all deletes), the maximum depth of the DFS tree is $M + N$.

$$
S(M, N) = \Theta(M \times N) + O(M + N) = \Theta(M \times N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int minDist_Helper(string w1, string w2, int idx1, int idx2, vector<vector<int>> &dp) {
        // Base Cases: Reached the end of one string
        if (idx1 == w1.length()) return w2.length() - idx2; // Insert remaining
        if (idx2 == w2.length()) return w1.length() - idx1; // Delete remaining
        
        // Return memoized state if already computed
        if (dp[idx1][idx2] != -1) return dp[idx1][idx2];
        
        // Characters match: cost is 0, advance both pointers
        if (w1[idx1] == w2[idx2]) {
            dp[idx1][idx2] = minDist_Helper(w1, w2, idx1 + 1, idx2 + 1, dp);
            return dp[idx1][idx2];
        }
        
        // Characters mismatch: calculate min cost of 3 possible operations
        dp[idx1][idx2] = 1 + min(
            minDist_Helper(w1, w2, idx1 + 1, idx2 + 1, dp), // Replace
            min(
                minDist_Helper(w1, w2, idx1, idx2 + 1, dp), // Insert
                minDist_Helper(w1, w2, idx1 + 1, idx2, dp)  // Delete
            )
        );
        
        return dp[idx1][idx2];
    }
    
    int minDistance(string word1, string word2) {
        // Initialize DP memoization table with -1
        vector<vector<int>> dp(word1.length() + 1, vector<int>(word2.length() + 1, -1));
        return minDist_Helper(word1, word2, 0, 0, dp);
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).