# Day 21: Transformed Array

- **Difficulty:** Easy
- **Topics:** Array, Simulation, Modular Arithmetic
- **LeetCode Link:** [Transformed Array](https://leetcode.com/problems/transformed-array/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an integer array `nums` representing a **circular array**. You must create a new array `result` of the same size following these rules for each index `i`:
* If `nums[i] > 0`: Move `nums[i]` steps to the **right**.
* If `nums[i] < 0`: Move `|nums[i]|` steps to the **left**.
* If `nums[i] == 0`: Stay at index `i`.

Assign `result[i]` to the value found at the destination index.

**Example 1:**
Input: `nums = [3, -2, 1, 1]`
Output: `[1, 1, 1, 3]`
* `i=0`, val `3`: Move 3 right $\to$ index 3. `res[0] = nums[3] = 1`.
* `i=1`, val `-2`: Move 2 left $\to$ index 3 (wraps around). `res[1] = nums[3] = 1`.

---

## 🏗️ Deep-Dive Implementation Strategy

The core challenge is calculating the target index in a circular manner, especially when moving backwards (negative direction) past index 0.

### 1. The Modular Arithmetic Approach

For an array of length $N$, moving $k$ steps from index $i$ lands on index $(i + k) \pmod N$.



* **Positive Steps:** Simple `(i + k) % n`.
* **Negative Steps:** In C++, the `%` operator can return negative values (e.g., `-2 % 5 = -2`).
    * Your implementation handles this by adding the negative remainder to the current index.
    * If the result is still negative, adding `n` brings it back into the valid range `[0, n-1]`.

### 2. Logic Breakdown

We iterate through each element `nums[i]` and determine its destination:

1.  **Case 1 (Negative):** `toCommit < 0`.
    * Compute offset: `offset = toCommit % n`.
    * Tentative Index: `idx = i + offset`.
    * Wrap-around check: If `idx < 0`, the correct circular index is `n + idx`.
2.  **Case 2 (Positive):** `toCommit > 0`.
    * Tentative Index: `i + toCommit`.
    * Wrap-around: `idx % n`.

This logic effectively maps the linear array onto a circle.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $N$ be the size of the array. For each index $i$, the target index $T_i$ is defined as:

$$
T_i = (i + \text{nums}[i]) \pmod N
$$

To ensure the result is always in $[0, N-1]$ (handling C++ negative modulo behavior):

$$
T_i = ((i + \text{nums}[i]) \% N + N) \% N
$$

### 2. Time Complexity

We iterate through the array exactly once, performing constant-time arithmetic operations for each element.

$$
T(N) = O(N)
$$

### 3. Space Complexity

We allocate a result vector of size $N$.

$$
S(N) = O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        vector<int> res(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            int finalIdx;
            int toCommit = nums[i];
            if (toCommit < 0) {
                finalIdx = i + (toCommit % n);
                if (finalIdx < 0) {
                    res[i] = nums[n+finalIdx];
                } else {
                    res[i] = nums[finalIdx];
                }
            } else {
                finalIdx = i + toCommit;
                    res[i] = nums[finalIdx %(n)];
            }
        }
        return res;
    }
};
```
### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).