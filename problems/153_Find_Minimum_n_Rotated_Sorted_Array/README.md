# Day 21: Find Minimum in Rotated Sorted Array

- **Difficulty:** Medium
- **Topics:** Array, Binary Search
- **LeetCode Link:** [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Suppose an array of length `n` sorted in ascending order is **rotated** between `1` and `n` times. For example, `[0,1,2,4,5,6,7]` might become `[4,5,6,7,0,1,2]`.

Given the sorted rotated array `nums` of **unique** elements, return the **minimum element** of this array.

You must write an algorithm that runs in $O(\log n)$ time.

**Example 1:**
Input: `nums = [3, 4, 5, 1, 2]`
Output: `1`

**Example 2:**
Input: `nums = [4, 5, 6, 7, 0, 1, 2]`
Output: `0`

---

## 🏗️ Deep-Dive Implementation Strategy

Since the requirement is $O(\log n)$, we must use **Binary Search**. However, the array is not fully sorted. It consists of two sorted subarrays (e.g., `[4, 5, 6, 7]` and `[0, 1, 2]`). The minimum element is the **pivot point** where the first sorted sequence ends and the second begins.

### 1. The Comparison Logic
In a standard Binary Search, we compare `nums[mid]` with a target. Here, we compare `nums[mid]` with the boundaries to determine which side is sorted and which side contains the "inflection" (the minimum).

**Key Observation:** Compare `nums[mid]` with `nums[r]` (the rightmost element of the current search space).

* **Case A:** `nums[mid] < nums[r]`
    * This implies the right half `[mid...r]` is sorted.
    * The minimum values cannot be in the range `(mid, r]`.
    * However, `nums[mid]` *itself* could be the minimum.
    * **Action:** Move `r` to `mid` (preserve `mid` as a candidate).

* **Case B:** `nums[mid] > nums[r]`
    * This implies the left half `[l...mid]` is sorted but contains large values (shifted from the end).
    * The pivot (minimum) *must* be in the right unsorted half.
    * `nums[mid]` is definitely not the minimum (since it's larger than `nums[r]`).
    * **Action:** Move `l` to `mid + 1`.

### 2. Execution Visualization
Input: `[4, 5, 6, 7, 0, 1, 2]`

* **Iteration 1:** `l=0, r=6`
    * `mid = 3` (Val: 7).
    * Compare `7` vs `2` (`nums[r]`).
    * `7 > 2`: The drop is to the right.
    * `l = 4`. Range: `[0, 1, 2]` (indices 4-6).

* **Iteration 2:** `l=4, r=6`
    * `mid = 5` (Val: 1).
    * Compare `1` vs `2` (`nums[r]`).
    * `1 < 2`: The right side is sorted. Min is at `mid` or left.
    * `r = 5`. Range: `[0, 1]` (indices 4-5).

* **Iteration 3:** `l=4, r=5`
    * `mid = 4` (Val: 0).
    * Compare `0` vs `1` (`nums[r]`).
    * `0 < 1`: Right side sorted.
    * `r = 4`.

* **End:** `l == r == 4`. Return `nums[4]` which is `0`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let the array $A$ be a cyclic shift of a sorted array $S$.
We are looking for index $k$ such that $A[k] < A[k-1]$ (with wrap-around).
The condition `nums[mid] < nums[r]` effectively acts as a predicate $P(x)$ that is monotonic over the rotation property, allowing the search space to be halved.

### 2. Time Complexity
Binary Search reduces the search space by half at each step.
$$ T(N) = O(\log N) $$

### 3. Space Complexity
The algorithm uses iterative binary search with a few variables.
$$ S(N) = O(1) $$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1, mid;
        while(l < r) {
            mid = l + (r-l)/2;
            if (nums[mid] < nums[r]){
                r = mid;
            } else if (nums[mid] > nums[r]) {
                l = mid + 1;
            }
        }
        return nums[l];
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).