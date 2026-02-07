# Day 23: Search in Rotated Sorted Array

- **Difficulty:** Medium
- **Topics:** Array, Binary Search
- **LeetCode Link:** [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

There is an integer array `nums` sorted in ascending order (with distinct values).
Prior to being passed to your function, `nums` is **possibly rotated** at an unknown pivot index `k` ($1 \le k < nums.length$).
For example, `[0,1,2,4,5,6,7]` might be rotated at pivot index 3 and become `[4,5,6,7,0,1,2]`.

Given the array `nums` **after** the possible rotation and an integer `target`, return the index of `target` if it is in `nums`, or `-1` if it is not in `nums`.

You must write an algorithm with $O(\log n)$ runtime complexity.

**Example 1:**
Input: `nums = [4,5,6,7,0,1,2], target = 0`
Output: `4`

**Example 2:**
Input: `nums = [4,5,6,7,0,1,2], target = 3`
Output: `-1`

---

## 🏗️ Deep-Dive Implementation Strategy

We cannot use linear search because of the $O(\log n)$ constraint. We must modify **Binary Search**.
The core insight is that for any `mid` element in a rotated sorted array, **at least one half (left or right) remains sorted**.

### 1. Identifying the Sorted Half
We compare `nums[mid]` with the boundaries (`nums[l]` or `nums[r]`).

[Image of binary search decision tree for rotated array]

* **Case 1: Left Half is Sorted** (`nums[mid] > nums[r]`)
    * If the target lies strictly within this sorted range ($nums[l] \le target < nums[mid]$), we eliminate the right half (`r = mid - 1`).
    * Otherwise, the target must be in the complex right half (`l = mid + 1`).

* **Case 2: Right Half is Sorted** (`nums[mid] < nums[l]`)
    * If the target lies strictly within this sorted range ($nums[mid] < target \le nums[r]$), we eliminate the left half (`l = mid + 1`).
    * Otherwise, the target must be in the complex left half (`r = mid - 1`).

* **Case 3: Fully Sorted** (`nums[mid] >= nums[l] && nums[mid] <= nums[r]`)
    * Standard binary search logic applies.

### 2. Execution Visualization
Input: `nums = [4, 5, 6, 7, 0, 1, 2]`, `target = 0`

* **Iteration 1:** `l=0, r=6`. `mid=3` (Value **7**).
    * `nums[mid] > nums[r]` (7 > 2) -> **Left is Sorted**.
    * Is target (0) in range `[4, 7)`? **No**.
    * Move Right: `l = mid + 1 = 4`.

* **Iteration 2:** `l=4, r=6`. `mid=5` (Value **1**).
    * `nums[mid] < nums[l]` (1 < 0 is false, check boundaries). Here `nums[mid] < nums[r]` check or `nums[mid] < nums[l]` logic handles the split.
    * In your logic: `nums[mid] (1) < nums[l] (0)` is False.
    * Check `nums[mid] (1) <= nums[r] (2)` and `nums[mid] (1) >= nums[l] (0)`? Yes. **Fully Sorted**.
    * `1 < 0`? False. `r = mid - 1 = 4`.

* **Iteration 3:** `l=4, r=4`. `mid=4` (Value **0**).
    * `nums[mid] == target`. **Return 4**.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let the array be partitioned into two sorted sequences $S_1$ and $S_2$ where all elements in $S_1$ are greater than all elements in $S_2$.
Binary search works because the predicate "Is $X$ in the currently sorted range?" provides a deterministic way to discard half the search space, maintaining the logarithmic invariant.

### 2. Time Complexity
The algorithm is a standard binary search with constant-time additional checks at each step.
$$T(N) = O(\log N)$$

### 3. Space Complexity
The algorithm uses iterative binary search with $O(1)$ auxiliary variables.
$$S(N) = O(1)$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] > nums[r]) {
                // right half sorted
                // left half sorted
                //[4,5,6,7,0,1,2]]
                if (target < nums[mid] && target >= nums[l]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else if(nums[mid] < nums[l]) {
                // [4,5,0,1,2]
                if (target > nums[mid] && target <= nums[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            } else if (nums[mid] >= nums[l] && nums[mid] <= nums[r]) {
                //all array sorted
                if (nums[mid] < target) {
                    l = mid + 1;
                } else{
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).
