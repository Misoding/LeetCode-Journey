# Day 11: Minimum Absolute Difference

- **Difficulty:** Easy
- **Topics:** Array, Sorting, Hash Table
- **LeetCode Link:** [Minimum Absolute Difference](https://leetcode.com/problems/minimum-absolute-difference/)
- **Author:** [Mihail Iazinschi (LinkedIn)](https://www.linkedin.com/in/misoding)

---

## 📝 Problem Statement

Given an array of **distinct** integers `arr`, find all pairs of elements with the minimum absolute difference of any two elements.

Return a list of pairs in ascending order (with respect to pairs), each pair `[a, b]` follows:
1.  $a, b$ are from `arr`.
2.  $a < b$.
3.  $b - a$ equals the minimum absolute difference of any two elements in `arr`.

**Example:**
Input: `arr = [4, 2, 1, 3]`
Sorted: `[1, 2, 3, 4]`
Minimum Difference: $1$ (between 1-2, 2-3, 3-4).
Output: `[[1, 2], [2, 3], [3, 4]]`

---

## 🏗️ Deep-Dive Implementation Strategy

The fundamental observation is that in a list of numbers, the minimum absolute difference can only occur between **adjacent elements** after the list has been sorted.

### 1. Sorting
We first sort the array `arr`. This ensures that for any two elements $a$ and $b$ (where index of $a <$ index of $b$), the difference $b - a$ is minimized when $b$ is immediately next to $a$.
$$\min_{i \ne j} |a_i - a_j| = \min_{k} (a_{k+1} - a_k) \quad \text{after sorting}$$

### 2. Hash Map for Index Tracking
Unlike the standard approach which rebuilds the result vector on the fly, this implementation utilizes an **Index Tracking Strategy** via a Hash Map (`unordered_map`).
* **Key:** The difference value (`sum`).
* **Value:** A list of starting indices (`i`) that produce this difference.

**The Algorithm Flow:**
1.  **Iterate** through the sorted array.
2.  Calculate `diff = arr[i+1] - arr[i]`.
3.  **Update State:**
    * If `diff < min_sum`: We found a new global minimum. We update `min_sum` and start a new entry in the map for this difference.
    * If `diff == min_sum`: We append the current index `i` to the existing list in the map.
4.  **Reconstruction:** After the loop, we access `sum_indexes[min_sum]` to retrieve all valid indices and construct the final result vector.

### 3. Execution Visualization
Consider `arr = [4, 2, 1, 3]`. Sorted: `[1, 2, 3, 4]`. `min_sum` starts at `INT_MAX`.

* **i = 0:** Pair `(1, 2)`. Diff = 1.
    * $1 < \text{INT\_MAX}$. `min_sum` becomes 1. Map: `{1: [0]}`.
* **i = 1:** Pair `(2, 3)`. Diff = 1.
    * $1 == \text{min\_sum}$. Map: `{1: [0, 1]}`.
* **i = 2:** Pair `(3, 4)`. Diff = 1.
    * $1 == \text{min\_sum}$. Map: `{1: [0, 1, 2]}`.

**Final Build:** Iterate indices `[0, 1, 2]` to create pairs `[1,2], [2,3], [3,4]`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the sorted sequence be $A = \{a_1, a_2, \dots, a_n\}$.
The objective is to find the set of pairs $P = \{ (a_i, a_{i+1}) \}$ such that:
$$a_{i+1} - a_i = \delta_{min}$$
where $\delta_{min} = \min_{1 \le k < n} (a_{k+1} - a_k)$.

### 2. Time Complexity

* **Sorting:** `std::sort` takes $O(N \log N)$.
* **Linear Scan:** We iterate through the array once ($N$ steps). Inside the loop, map operations (insertion/lookup) take amortized $O(1)$.
* **Reconstruction:** We iterate through the valid indices (at most $N$) to build the result.

$$T(N) = T_{sort} + T_{scan} + T_{build}$$
$$T(N) \approx O(N \log N) + O(N) + O(N)$$
$$T(N) \in O(N \log N)$$

### 3. Space Complexity

* **Auxiliary Map:** In the worst case (e.g., `[1, 2, 3, 4]`), all adjacent pairs have the minimal difference. The map stores $O(N)$ indices.
* **Output:** The result vector takes $O(N)$.

$$S(N) \in O(N)$$

---
```cpp
## 💻 Implementation (C++)
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        vector<vector<int>> result;
        unordered_map<int, vector<int>> sum_indexes;
        int min_sum = INT_MAX;
        for(int i = 0; i < arr.size()-1; i++) {
            int sum = arr[i+1] - arr[i];
            if (sum < min_sum) {
                vector<int> current_sum_indexes;
                current_sum_indexes.push_back(i);
                sum_indexes[sum] = current_sum_indexes;
                min_sum = sum;
            } else if (sum == min_sum){
                sum_indexes[min_sum].push_back(i);
            }
        }
        for(int index : sum_indexes[min_sum]) {
            result.push_back({arr[index], arr[index+1]});
        }
        return result;
    }
};
```

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).   