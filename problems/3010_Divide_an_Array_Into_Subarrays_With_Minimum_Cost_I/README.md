# Day 17: Divide an Array Into Subarrays With Minimum Cost I

- **Difficulty:** Easy
- **Topics:** Array, Greedy, Sorting
- **LeetCode Link:** [Divide an Array Into Subarrays With Minimum Cost I](https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-i/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an array of integers `nums` of length `n`.
The **cost** of an array is the value of its **first element**.
You need to divide `nums` into **3 disjoint contiguous subarrays**.

Return the **minimum possible sum** of the cost of these subarrays.

**Example 1:**
Input: `nums = [1, 2, 3, 12]`
Output: `6`
Explanation:
* Subarray 1: `[1]` (Starts with 1) -> Cost 1.
* Subarray 2: `[2]` (Starts with 2) -> Cost 2.
* Subarray 3: `[3, 12]` (Starts with 3) -> Cost 3.
Total: $1 + 2 + 3 = 6$.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem asks us to split the array into three parts: $[0 \dots i-1]$, $[i \dots j-1]$, and $[j \dots n-1]$.
The total cost is the sum of the first elements of these parts:
$$ Cost = nums[0] + nums[i] + nums[j] $$
where $1 \le i < j < n$.

### 1. The Greedy Observation
* The first subarray **must** start at index `0`. So, `nums[0]` is always included in the total cost.
* We need to choose two other starting positions ($i$ and $j$) from the remaining elements (`nums[1]` to `nums[n-1]`) to be the heads of the 2nd and 3rd subarrays.
* To minimize the sum $nums[0] + nums[i] + nums[j]$, we simply need to find the **two smallest values** in the range `nums[1...n-1]`.

The problem reduces to: **Find the two minimum elements in the suffix `nums[1:]` and add them to `nums[0]`.**

### 2. Execution Visualization
Input: `nums = [10, 3, 1, 1]`

1.  **Fixed Cost:** `nums[0] = 10`.
2.  **Search Range:** `[3, 1, 1]`.
3.  **Find Minimums:**
    * Iterate `3`: Min1 = 3.
    * Iterate `1`: Min1 = 1, Min2 = 3.
    * Iterate `1`: Min1 = 1, Min2 = 1.
4.  **Result:** `10 + 1 + 1 = 12`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let the array be $A = [a_0, a_1, \dots, a_{n-1}]$.
We want to minimize:
$$ C = a_0 + a_i + a_j \quad \text{subject to } 1 \le i < j \le n-1 $$
Since addition is commutative and associative, finding indices $i, j$ that minimize $a_i + a_j$ is equivalent to finding the two smallest values in $\{a_1, \dots, a_{n-1}\}$.

### 2. Time Complexity
We perform a single pass through the array (starting from index 1) to find the two smallest numbers.
$$ T(N) = O(N) $$

### 3. Space Complexity
We only store two variables (`minL`, `minR`) to track the minimums.
$$ S(N) = O(1) $$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int n = nums.size();
        int minL = INT_MAX, minR = INT_MAX;
        for(int i = 1; i < n; i++) {
            if (nums[i] < minL) {
                minR = minL;
                minL = nums[i];
            } else if (nums[i] < minR) {
                minR = nums[i];
            }
        }
        return nums[0] + minL + minR;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).