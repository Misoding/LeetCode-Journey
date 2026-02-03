# Day 19: Trionic Array I

- **Difficulty:** Easy
- **Topics:** Array, Simulation, Two Pointers
- **LeetCode Link:** [Trionic Array I](https://leetcode.com/problems/trionic-array-i/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an integer array `nums` of length `n`. An array is **Trionic** if it follows a specific "Up-Down-Up" pattern. Specifically, there must exist indices $0 < p < q < n-1$ such that:

1.  `nums[0...p]` is **strictly increasing**.
2.  `nums[p...q]` is **strictly decreasing**.
3.  `nums[q...n-1]` is **strictly increasing**.

Return `true` if `nums` is trionic, otherwise return `false`.

**Example 1:**
Input: `nums = [1, 3, 5, 4, 2, 6]`
* **Up:** `[1, 3, 5]` (Peak at index 2, val 5)
* **Down:** `[5, 4, 2]` (Valley at index 4, val 2)
* **Up:** `[2, 6]` (End of array)
Output: `true`

---

## 🏗️ Deep-Dive Implementation Strategy

The problem asks us to validate a specific shape of the data curve. We can visualize this as verifying three sequential slopes: **Ascending $\nearrow$, Descending $\searrow$, Ascending $\nearrow$**.



### 1. The Three-Phase Linear Scan
We can solve this with a single pass through the array using a state-machine approach or simply three sequential `while` loops.

**Phase 1: The First Ascent**
* Start at `i = 0`.
* Move forward as long as `nums[i+1] > nums[i]`.
* **Validation:** We must climb at least one step (`p > 0`), otherwise the first segment is empty.

**Phase 2: The Descent**
* From the peak `p`, move forward as long as `nums[i+1] < nums[i]`.
* **Validation:** We must descend at least one step ($q > p$).

**Phase 3: The Second Ascent**
* From the valley `q`, move forward as long as `nums[i+1] > nums[i]`.
* **Validation:** We must climb at least one step ($n-1 > q$) and reach the **end of the array**.

### 2. Execution Visualization
Input: `[1, 3, 5, 4, 2, 6]`

1.  **Climb 1:** `1 < 3`, `3 < 5`. Next is `4` (smaller). Stop at `5` (index 2).
    * Valid? Yes, index 2 > 0.
2.  **Descend:** `5 > 4`, `4 > 2`. Next is `6` (larger). Stop at `2` (index 4).
    * Valid? Yes, we moved.
3.  **Climb 2:** `2 < 6`. End of array.
    * Valid? Yes, reached index `n-1`.

Result: `true`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
We are looking for a partition of the array indices $I = \{0, \dots, n-1\}$ into three intervals $I_1 = [0, p]$, $I_2 = [p, q]$, $I_3 = [q, n-1]$.
The conditions are:
$$ \forall k \in [0, p-1], nums[k] < nums[k+1] $$
$$ \forall k \in [p, q-1], nums[k] > nums[k+1] $$
$$ \forall k \in [q, n-2], nums[k] < nums[k+1] $$

### 2. Time Complexity
The algorithm involves a single pointer `i` that increments from `0` to `n-1`. Each element is visited at most once by the checks.
$$ T(N) = O(N) $$

### 3. Space Complexity
We use only a few integer variables for state tracking.
$$ S(N) = O(1) $$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int i = 0; int n = nums.size();
        if (n <= 3) return false;
        bool validArray = true;
        int s = -2000, q = -2000, p = -2000;
        while (i < n-1){
            if (!(nums[i+1] > nums[i])) {
                break;
            }
            i++;
        }
        if (i == 0) return 0;
        p = nums[i];
        while (i < n-1){
            if (!(nums[i+1] < nums[i])) {
                break;
            }
            i++;
        }
        q = nums[i];
        while (i < n-1){
            if (!(nums[i+1] > nums[i])) {
                break;
            }
            i++;
        }
        if (i == n-1 && nums[n-1] > q  && q < p && p > s) {
            return validArray;
        }
        return false;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).