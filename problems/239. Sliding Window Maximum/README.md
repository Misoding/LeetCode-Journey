# Day 27: Sliding Window Maximum

- **Difficulty:** Hard
- **Topics:** Array, Sliding Window, Heap (Priority Queue), Monotonic Queue, Multiset
- **LeetCode Link:** [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an array of integers `nums`, there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return *the max sliding window*.

**Example 1:**
Input: `nums = [1,3,-1,-3,5,3,6,7], k = 3`
Output: `[3,3,5,5,6,7]`
Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

---

## 🏗️ Deep-Dive Implementation Strategy

The naive approach involves iterating through all windows and finding the max in $O(k)$, leading to a total of $O(N \cdot k)$. This is too slow for large inputs ($N=10^5, k=10^4$).

We need a data structure that allows us to:
1.  Add an element efficiently.
2.  Remove an element efficiently.
3.  Query the **maximum** value efficiently.

### 1. The Multiset (Balanced BST) Approach
Your solution uses a `std::multiset`. A multiset maintains its elements in sorted order.
* **Insert:** When the window expands right, we insert `nums[r]`. Cost: $O(\log k)$.
* **Query Max:** The maximum element is always at the end of the set (`*window.rbegin()`). Cost: $O(1)$.
* **Remove:** When the window shrinks from the left, we remove `nums[l]`. We must use `window.find(nums[l])` to erase only **one instance** of the value (in case of duplicates). Cost: $O(\log k)$.

### 2. Execution Visualization
Input: `[1, 3, -1, -3]`, `k = 3`

* **Step 1 (Expand):** Insert `1`. Set: `{1}`.
* **Step 2 (Expand):** Insert `3`. Set: `{1, 3}`.
* **Step 3 (Expand):** Insert `-1`. Set: `{-1, 1, 3}`. Window size is 3.
    * **Max:** `3`. Result: `[3]`.
    * **Shrink:** Remove `1` (nums[l]). Set: `{-1, 3}`.
* **Step 4 (Slide):** Insert `-3`. Set: `{-3, -1, 3}`.
    * **Max:** `3`. Result: `[3, 3]`.
    * **Shrink:** Remove `3`. Set: `{-3, -1}`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let $W_i$ be the set of elements in the sliding window at index $i$.
We maintain $W_i$ using a Red-Black Tree (underlying structure of `multiset`).
The operation is to find $\max(W_i)$ while updating $W_i \to W_{i+1}$ by adding $x_{new}$ and removing $x_{old}$.

### 2. Time Complexity
* We iterate through the array of size $N$.
* For each element, we perform one insertion and (eventually) one deletion in the multiset.
* The size of the multiset is at most $k$.
* Operations take logarithmic time relative to the container size.

$$T(N) = O(N \log k)$$

### 3. Space Complexity
The multiset stores at most $k$ elements.
$$S(N) = O(k)$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> maxArr;
        int l = 0, r = 0;
        multiset<int> window;
        for(int i = 0; i < nums.size(); i++) {
            if (r - l < k) {
                if (r < nums.size()) {
                    window.insert(nums[r]);
                }
                r++;
            }
            if (r-l == k) {
                maxArr.push_back(*(window.rbegin()));
                window.erase((window.find(nums[l])));
                l++;
            }
        }
        return maxArr;
    }
};
```
---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).