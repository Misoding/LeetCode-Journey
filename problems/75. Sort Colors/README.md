# Day 60: Sort Colors

- **Difficulty:** Medium
- **Topics:** Array, Sorting, Divide and Conquer
- **LeetCode Link:** [Sort Colors](https://leetcode.com/problems/sort-colors/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given an array `nums` with `n` objects colored red, white, or blue, sort them **in-place** so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers `0`, `1`, and `2` to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

**Example 1:**
Input: `nums = [2,0,2,1,1,0]`
Output: `[0,0,1,1,2,2]`

---

## 🏗️ Deep-Dive Implementation Strategy

The implementation utilizes a general-purpose, highly efficient **Randomized QuickSort** algorithm. It relies on the Divide and Conquer paradigm to sort the array in-place.

### 1. Lomuto Partition Scheme
The core of the algorithm is the `partition` function. It selects a pivot (in this case, the element placed at the extreme right, `r`) and maintains an `index` pointer that tracks the boundary of elements strictly smaller than or equal to the pivot.
As the array is iterated from `l` to `r-1`, any element smaller than or equal to the pivot is swapped into the boundary, effectively isolating the elements into two distinct halves. Finally, the pivot is swapped into its correct, sorted position `index + 1`.

### 2. Randomized Pivot Selection
Standard QuickSort degrades to an unacceptable $O(N^2)$ time complexity if the input array is already sorted or reverse-sorted. To mitigate this adversarial edge case, the `partition_helper` function generates a random index within the current bounds `[l, r]`, swaps the random element to the end of the segment, and then applies the Lomuto partition. This probabilistic safeguard guarantees an expected time complexity of $O(N \log N)$.

### 3. Execution Context
The `quickSort` function recursively applies this logic to the left and right subarrays, bounded by the newly established pivot, until the base case (`l >= r`) is reached, resulting in a fully sorted array.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the array be $A$ of size $N$. The algorithm selects a random index $p \in [l, r]$. 
The partition function rearranges the subarray such that:
1. $A[k] \le A[p]$ for all $l \le k < \text{pivot\_index}$
2. $A[k] > A[p]$ for all $\text{pivot\_index} < k \le r$

The expected recurrence relation for the randomized execution is:

$$
T(N) = 2T\left(\frac{N}{2}\right) + \Theta(N)
$$

### 2. Time Complexity Analysis

Due to the randomized pivot, the partition splits the array relatively evenly in the average case. The recursion tree reaches a depth of $\log_2 N$, and at each level, the partition performs $\Theta(N)$ work.
* **Expected Time Complexity:** $\Theta(N \log N)$
* **Worst-Case Time Complexity:** $O(N^2)$ (Mathematically possible if the random number generator consistently picks the global maximum or minimum of the subarray, but probabilistically negligible).

### 3. Space Complexity Analysis

The algorithm operates strictly in-place, swapping array elements without auxiliary data structures. However, the depth of the recursive call stack dictates the spatial footprint.
* **Expected Space Complexity:** $\Theta(\log N)$ stack frames.
* **Worst-Case Space Complexity:** $O(N)$ stack frames (if the tree is completely unbalanced).

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int partition(vector<int>& nums, int l, int r) {
        int selectedNum = nums[r];
        int index = l-1;
        for (int j = l; j <= r-1; j++) {
            if (nums[j] <= selectedNum) {
                index++;
                swap(nums[index], nums[j]);
            }
        }
        swap(nums[index+1], nums[r]);
        return (index+1);
    }
    int partition_helper(vector<int>& nums, int l, int r){
        srand(time(NULL));
        int random = l + rand() % (r - l);
        swap(nums[random], nums[r]);
        return partition(nums, l, r);
    }
    void quickSort(vector<int>& nums, int l, int r) {
        if (l < r) {
            int idx = partition_helper(nums, l, r);
            quickSort(nums, l, idx-1);
            quickSort(nums, idx+1, r);
        }
    }
    void sortColors(vector<int>& nums) {
        quickSort(nums, 0, nums.size()-1);
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).