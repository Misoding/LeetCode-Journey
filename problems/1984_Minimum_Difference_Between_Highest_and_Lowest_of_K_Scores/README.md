# Day 10: Minimum Difference Between Highest and Lowest of K Scores

- **Difficulty:** Easy
- **Topics:** Array, Sliding Window, Sorting
- **LeetCode Link:** [Minimum Difference Between Highest and Lowest of K Scores](https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/)
- **Author:** [Mihail Iazinschi (LinkedIn)](https://www.linkedin.com/in/misoding)

---

## 📝 Problem Statement

You are given a **0-indexed** integer array `nums`, where `nums[i]` represents the score of the $i^{th}$ student. You are also given an integer `k`.

Pick the scores of any `k` students from the array so that the **difference** between the **highest** and the **lowest** of the `k` scores is **minimized**.

Return the minimum possible difference.

**Example:**
Input: `nums = [9, 4, 1, 7], k = 2`
Sorted (Descending): `[9, 7, 4, 1]`
Possible subsets of size 2:
* `[9, 7]` $\rightarrow$ Difference $9 - 7 = 2$
* `[7, 4]` $\rightarrow$ Difference $7 - 4 = 3$
* `[4, 1]` $\rightarrow$ Difference $4 - 1 = 3$
Result: `2`

---

## 🏗️ Deep-Dive Implementation Strategy

The core requirement is to find $k$ numbers that are "clustered" as closely together as possible.

### 1. Intuition: Why Sorting?
In an unsorted array, the values close to each other might be scattered at random indices.
* If we select a subset of $k$ elements, the difference is defined by $\max(subset) - \min(subset)$.
* To minimize this range, the chosen elements must be contiguous in value.
* **Sorting** the array brings values that are close in magnitude next to each other.

### 2. The Sliding Window Technique
Once the array is sorted, any valid selection of $k$ optimal scores forms a **contiguous subarray** (window) of length $k$.
* If we sort in **Descending Order** (as in your implementation): `nums[i] \ge nums[i+1]`.
* For a window starting at index `l` and ending at `r = l + k - 1`:
    * **Maximum:** `nums[l]` (First element of the window).
    * **Minimum:** `nums[r]` (Last element of the window).
    * **Difference:** `nums[l] - nums[r]`.

We simply slide this window of size $k$ across the array and track the global minimum difference.

### 3. Execution Visualization

Consider `nums = [9, 4, 1, 7]`, `k = 2`.

**Step A: Sort Descending**
`nums` becomes `[9, 7, 4, 1]`.

**Step B: Sliding Window**

```text
Iteration 1:
Window: [9, 7], 4, 1
Indices: l=0, r=1
Diff:    9 - 7 = 2
MinDiff: 2

Iteration 2:
Window: 9, [7, 4], 1
Indices: l=1, r=2
Diff:    7 - 4 = 3
MinDiff: min(2, 3) = 2

Iteration 3:
Window: 9, 7, [4, 1]
Indices: l=2, r=3
Diff:    4 - 1 = 3
MinDiff: min(2, 3) = 2
```

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the sorted (descending) sequence be $A = \{a_1, a_2, \dots, a_n\}$ such that $a_1 \ge a_2 \ge \dots \ge a_n$.
We seek to minimize the range function $R(S) = \max(S) - \min(S)$ for subsets $S \subset A$ with $|S|=k$.

**Lemma:** The optimal subset $S^*$ consists of contiguous elements in the sorted sequence.
**Proof Intuition:** If an optimal subset contained gaps (e.g., $a_i$ and $a_{i+2}$ but not $a_{i+1}$), adding $a_{i+1}$ would not increase the range (since $a_i \ge a_{i+1} \ge a_{i+2}$) but is necessary to fill the count $k$. Replacing an extremal element with a closer intermediate element strictly reduces the range.

Thus, we only evaluate sets $\{a_i, a_{i+1}, \dots, a_{i+k-1}\}$.
The objective function becomes:
$$
\min_{0 \le i \le n-k} (a_i - a_{i+k-1})
$$

### 2. Time Complexity

* **Sorting:** The `std::sort` function typically implements Introsort.
    $$T_{sort}(N) \in O(N \log N)$$
* **Linear Scan:** We iterate through the sorted array once with a window of size $k$.
    $$T_{scan}(N) \approx (N - k) \cdot O(1) \in O(N)$$

**Total Time Complexity:**
$$T(N) = O(N \log N) + O(N) \implies T(N) \in O(N \log N)$$

### 3. Space Complexity

* **Auxiliary Space:** The sorting algorithm requires stack space for recursion.
    $$S(N) \in O(\log N)$$
* **Variables:** We use constant extra space (`l`, `r`, `min_diff`).

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        if (nums.size() < k) {
            return 0;
        }
        sort(nums.begin(), nums.end(), greater<int>());
        int l = 0, r = l + k - 1;
        int min_diff = INT_MAX;
        while (r < nums.size()){
            min_diff = min(nums[l++] - nums[r++], min_diff);
        }
        return min_diff;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).   