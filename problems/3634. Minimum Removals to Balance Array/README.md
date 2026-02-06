# Day 22: Minimum Removals to Balance Array

- **Difficulty:** Medium
- **Topics:** Array, Sorting, Binary Search, Sliding Window
- **LeetCode Link:** [Minimum Removals to Balance Array](https://leetcode.com/problems/minimum-removals-to-balance-array/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an integer array `nums` and an integer `k`. An array is considered **balanced** if the maximum element is at most `k` times the minimum element:
$$\max(arr) \le \min(arr) \times k$$

You can remove any number of elements from the array. Return the **minimum number of elements** to remove so that the remaining array is balanced.

**Example 1:**
Input: `nums = [1, 6, 2, 9], k = 3`
Output: `2`
Explanation:
* If we keep `[1, 2]`: $\max(2) \le 1 \times 3$. Valid. Removals: 2.
* If we keep `[6, 9]`: $\max(9) \le 6 \times 3$. Valid. Removals: 2.
* If we keep `[2, 6]`: $\max(6) \le 2 \times 3$. Valid. Removals: 2.
* Valid balanced subarrays can be formed by removing 2 elements.

---

## 🏗️ Deep-Dive Implementation Strategy

The brute force approach of checking every subsequence is inefficient. The key insight is that the "balanced" condition depends only on the values, not their original positions. Therefore, **sorting** the array transforms the problem into finding the longest **contiguous subarray** that satisfies the condition.

### 1. Sorting and Fixing the Minimum
Once `nums` is sorted, any valid subset will be a subarray `nums[i...j]`.
* We iterate through the array, treating `nums[i]` as the **minimum** of our potential balanced subarray.
* The maximum allowed value in this subarray becomes `limit = nums[i] * k`.



### 2. Binary Search for the Upper Bound
For a fixed minimum `nums[i]`, we need to find the largest index `j` such that `nums[j] <= limit`.
* We use `std::upper_bound` to find the first element strictly greater than `limit`. Let this iterator be `found`.
* The elements we **keep** are those in the range `[i, found - 1]`.
* The elements we **remove** are:
    1.  **Left side:** All elements before `i` ($i$ count).
    2.  **Right side:** All elements from `found` to the end.

### 3. Execution Visualization
Input: `nums = [1, 6, 2, 9], k = 3` -> Sorted: `[1, 2, 6, 9]`

* **i = 0 (Val 1):** Limit = $1 \times 3 = 3$.
    * `upper_bound` for 3 points to `6` (index 2).
    * Keep range `[0, 1]` (Values 1, 2). Length 2.
    * Removals: $4 - 2 = 2$.
* **i = 1 (Val 2):** Limit = $2 \times 3 = 6$.
    * `upper_bound` for 6 points to `9` (index 3).
    * Keep range `[1, 2]` (Values 2, 6). Length 2.
    * Removals: $4 - 2 = 2$.
* **i = 2 (Val 6):** Limit = $6 \times 3 = 18$.
    * `upper_bound` points to `end` (index 4).
    * Keep range `[2, 3]` (Values 6, 9). Length 2.
    * Removals: $4 - 2 = 2$.

Min Removals: 2.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let the sorted array be $A$ of size $N$. We want to maximize the window size $j - i + 1$ subject to:
$$A[j] \le A[i] \times k$$
The number of removals is $N - (j - i + 1)$.
The algorithm fixes $i$ and uses binary search to find the maximal $j$.

### 2. Time Complexity
1.  **Sorting:** $O(N \log N)$.
2.  **Iteration:** The loop runs $N$ times.
3.  **Binary Search:** Inside the loop, `upper_bound` takes $O(\log N)$.

Total Time Complexity:
$$T(N) = O(N \log N) + N \cdot O(\log N) = O(N \log N)$$

### 3. Space Complexity
We sort the array in-place.
$$S(N) = O(\log N) \text{ (Stack space for sort)}$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    // long long multiply;
    // vector<vector<int>> dp;
    // vector<int> numVect;
    // int removal(int l, int r) {
    //     if(l >= r) {
    //         return 0;
    //     }
    //     if (dp[l][r] != -1) {
    //         return dp[l][r];
    //     }
    //     if ((long long) numVect[l] * multiply >= (long long) numVect[r]) {
    //         return 0;
    //     }
    //     int currentMin = 1e9;
    //     currentMin = min(currentMin, 1 +  removal(l+1, r));
    //     currentMin = min(currentMin, 1 + removal(l, r-1));
    //     dp[l][r] = currentMin;
    //     return currentMin;
    // }
    int minRemoval(vector<int>& nums, int k) {
        // max element <= k * min_el
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int minRemoves = INT_MAX;
        for(int i = 0; i < n; i++) {
            long long searchFor = (long long) nums[i] * k;
            auto found = upper_bound(nums.begin() + i, nums.end(), searchFor);
            int rightElements = distance(found, nums.end());
            minRemoves = min(minRemoves, rightElements + i);
        }
        return minRemoves;
    }
};
```

---

### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).