# Day 53: House Robber

- **Difficulty:** Medium
- **Topics:** Array, Dynamic Programming
- **LeetCode Link:** [House Robber](https://leetcode.com/problems/house-robber/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and **it will automatically contact the police if two adjacent houses were broken into on the same night**.

Given an integer array `nums` representing the amount of money of each house, return the maximum amount of money you can rob tonight **without alerting the police**.

**Example 1:**
Input: `nums = [1,2,3,1]`
Output: `4`
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3). Total amount you can rob = $1 + 3 = 4$.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem exhibits optimal substructure and overlapping subproblems, making it a canonical candidate for **Dynamic Programming**. The current implementation utilizes a Top-Down approach (Depth-First Search with Memoization) to explore the state space.

### 1. State Definition and Transitions
Let the state function `robHouse(idx)` represent the maximum loot obtainable starting from the house at index `idx` to the end of the array.
At any valid index `idx`, the decision matrix presents two mutually exclusive branches:
1.  **Rob the current house:** The robber gains `nums[idx]` but is mathematically forced to skip `idx + 1` due to the adjacency constraint. The next available state is `idx + 2`.
2.  **Skip the current house:** The robber gains $0$ from the current house but preserves the eligibility to rob `idx + 1`. The next available state is `idx + 1`.

The optimal choice is the maximum of these two discrete paths.

### 2. Memoization Array
A recursion tree for this decision matrix expands at $O(2^N)$, leading to severe redundancy (e.g., `robHouse(idx + 2)` is called by both the `rob(idx)` and `skip(idx + 1)` branches). By caching the evaluated results of `idx` in a $1D$ vector `dp` initialized to `-1`, the execution flow intercepts and returns precomputed states, effectively pruning the exponential branches.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $N$ be the cardinality of the `nums` array. Let $DP(i)$ map to the maximum value extractable from the suffix subset $\{nums_i, \dots, nums_{N-1}\}$.
The recurrence relation establishes:

$$
DP(i) = \begin{cases} 
0 & \text{if } i \ge N \\
\max(nums[i] + DP(i+2), DP(i+1)) & \text{if } 0 \le i < N
\end{cases}
$$

The target value is the root state $DP(0)$.

### 2. Time Complexity Analysis

The state space is strictly defined by the parameter `idx`, which ranges from $0$ to $N$.
Due to the `dp` memoization matrix, each unique state $DP(i)$ is computed exactly once. The discrete arithmetic operations (addition, `max()`) within each state frame execute in $\Theta(1)$ constant time bounds.

$$
T(N) = \sum_{i=0}^{N-1} \Theta(1) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The auxiliary spatial allocations consist of:
1.  **Memoization Matrix:** A vector `dp` of size $N$ initialized on the heap.
2.  **Call Stack:** The DFS recursion depth is bounded by the longest path, which occurs if the algorithm skips every house, reaching a maximum stack depth of $N$.

$$
S(N) = \Theta(N) + \Theta(N) = \Theta(N)
$$

$$
S(N) \in O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int robHouse(vector<int>& nums, int idx, vector<int> &dp) {
        if (idx >= nums.size()) return 0;
        if (dp[idx] != -1) return dp[idx];
        int num = nums[idx];
        int robCurrent =  num + robHouse(nums, idx + 2, dp);
        int noRobCurrent = robHouse(nums, idx+1, dp);
        dp[idx] = max(robCurrent, noRobCurrent);
        return dp[idx];
    }
    int rob(vector<int>& nums) {
        vector<int> dp(nums.size(), -1);
        dp[nums.size()-1] =  robHouse(nums, 0, dp);
        return dp[nums.size() - 1];
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).