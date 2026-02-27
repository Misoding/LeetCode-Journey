# Day 37: Subsets

- **Difficulty:** Medium
- **Topics:** Array, Backtracking, Depth-First Search
- **LeetCode Link:** [Subsets](https://leetcode.com/problems/subsets/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given an integer array `nums` of **unique** elements, return all possible subsets (the power set).

The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

**Example 1:**
Input: `nums = [1,2,3]`
Output: `[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]`

**Example 2:**
Input: `nums = [0]`
Output: `[[],[0]]`

---

## 🏗️ Deep-Dive Implementation Strategy

Generating a power set requires exploring all combinations of elements. Since we either include or exclude each element independently, the total number of states is $2^N$. We can model this as a binary decision tree and traverse it using **Backtracking (DFS)**.

### 1. The Decision Tree (Include / Exclude)
At each index `id` in the array `nums`, we branch into two parallel universes:
1.  **Include the element:** We push `nums[id]` into our tracking vector `curSubset` and recurse to `id + 1`.
2.  **Exclude the element:** We backtrack by popping `nums[id]` out of `curSubset` (restoring the state to what it was before the inclusion) and recurse to `id + 1`.

### 2. Execution Visualization
Input: `nums = [1, 2]`

* **Start:** `id = 0`, `curSubset = []`
    * **Include 1:** `curSubset = [1]`. Recurse `id = 1`.
        * **Include 2:** `curSubset = [1, 2]`. Recurse `id = 2`.
            * *Base Case `id == 2`: Add `[1, 2]` to result. Return.*
        * **Exclude 2:** Pop `2`. `curSubset = [1]`. Recurse `id = 2`.
            * *Base Case `id == 2`: Add `[1]` to result. Return.*
    * **Exclude 1:** Pop `1`. `curSubset = []`. Recurse `id = 1`.
        * **Include 2:** `curSubset = [2]`. Recurse `id = 2`.
            * *Base Case `id == 2`: Add `[2]` to result. Return.*
        * **Exclude 2:** Pop `2`. `curSubset = []`. Recurse `id = 2`.
            * *Base Case `id == 2`: Add `[]` to result. Return.*

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $S$ be a set of $N$ distinct elements. The power set $\mathcal{P}(S)$ is the set of all subsets of $S$.
The cardinality of the power set is mathematically proven to be:

$$
|\mathcal{P}(S)| = 2^N
$$

The backtracking algorithm defines a recurrence relation for the decision space where at each step $k \in \{0, \dots, N-1\}$, we multiply the branching factor by 2.

### 2. Time Complexity Analysis

The recursion tree has a depth of $N$ and a branching factor of $2$, resulting in $2^N$ leaf nodes (representing all subsets).
At each leaf node, when `id == initialArr.size()`, the algorithm performs a deep copy of the `curSubset` vector into the `res` vector. The maximum length of `curSubset` is $N$.

$$
T(N) = \sum_{i=1}^{2^N} O(k_i) \quad \text{where } k_i \le N
$$

$$
T(N) = O(N \cdot 2^N)
$$

### 3. Space Complexity Analysis

The space complexity is defined by the auxiliary memory used during the DFS traversal, excluding the space required for the output array `res` (which takes $O(N \cdot 2^N)$ space).
1.  **Recursion Stack:** The maximum depth of the call stack is exactly $N$.
2.  **Tracking Vector:** The `curSubset` vector grows to a maximum size of $N$.

$$
S_{aux}(N) = O(N) + O(N) = O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    void formSubsets(vector<int>& initialArr, vector<int>& curSubset, vector<vector<int>>& res, int id) {
        if (id == initialArr.size()) {
            res.push_back(curSubset);
            return;
        }
        // include current element at index id
        curSubset.push_back(initialArr[id]);
        formSubsets(initialArr, curSubset, res, id+1);
        
        //don't include current element
        curSubset.pop_back();
        formSubsets(initialArr,curSubset,res,id+1);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> curSubset;
        formSubsets(nums, curSubset, res, 0);
        return res;
    }

};
```

---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).