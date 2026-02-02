# Day 18: Longest Consecutive Sequence

- **Difficulty:** Medium
- **Topics:** Array, Hash Table, Union Find
- **LeetCode Link:** [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
You must write an algorithm that runs in **$O(n)$** time.

**Example 1:**
Input: `nums = [100, 4, 200, 1, 3, 2]`
Output: `4`
Explanation: The longest consecutive elements sequence is `[1, 2, 3, 4]`. Its length is 4.

**Example 2:**
Input: `nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]`
Output: `9`
Explanation: The sequence is `[0, 1, 2, 3, 4, 5, 6, 7, 8]`.

---

## 🏗️ Deep-Dive Implementation Strategy

The constraint of $O(N)$ time complexity immediately rules out sorting, which would take $O(N \log N)$. We must rely on a **Hash Set** (`unordered_set`) to perform existence checks in $O(1)$ average time.

### 1. Data Structures Visualization

We treat the numbers as nodes in a graph where an edge exists between $x$ and $x+1$. The problem is equivalent to finding the largest connected component.

**State Definition:**
* `allNums`: A hash set containing all unique numbers from the input.
* `visited`: Implicitly managed by **removing** elements from `allNums` once processed.

### 2. The "Expand and Erase" Logic

Your solution uses a clever "consumptive" approach:
1.  **Populate:** Load all numbers into `allNums`.
2.  **Iterate:** Scan the input array. For a number `x`:
    * **Check:** Is `x` in the set?
    * **Expand Left:** While `x-1`, `x-2`... exist in the set, count them and **remove** them.
    * **Expand Right:** While `x+1`, `x+2`... exist in the set, count them and **remove** them.
    * **Update Max:** Record the total length of this consecutive cluster.

**Visual Trace:** `nums = [100, 4, 200, 1, 3, 2]`
Set: `{100, 4, 200, 1, 3, 2}`

* **Step 1:** Encounter `100`. Found in set? Yes.
    * Remove `100`.
    * Expand Left (99): Not found.
    * Expand Right (101): Not found.
    * Sequence Length: 1.
    * Set is now: `{4, 200, 1, 3, 2}`.

* **Step 2:** Encounter `4`. Found in set? Yes.
    * Remove `4`.
    * Expand Left:
        * Find `3` -> Remove.
        * Find `2` -> Remove.
        * Find `1` -> Remove.
        * Find `0` -> Not found. Stop.
    * Expand Right:
        * Find `5` -> Not found. Stop.
    * Sequence Length: 4 (`[1, 2, 3, 4]`).
    * Set is now: `{200}`.

* **Step 3:** Encounter `200`. Found? Yes. Remove. Len 1.
* **Step 4:** Encounter `1`. Found? No (Already removed in Step 2). Skip.
* **Step 5:** Encounter `3`. Found? No. Skip.
* **Step 6:** Encounter `2`. Found? No. Skip.

**Final Result:** 4.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $S$ be the set of input integers. The problem partitions $S$ into disjoint sets $C_1, C_2, \dots, C_k$, where each $C_i$ consists of consecutive integers $\{a, a+1, \dots, a+m\}$.
We define the objective function as:
$$
\text{Result} = \max_{1 \le i \le k} |C_i|
$$

### 2. Time Complexity Derivation

At first glance, the nested `while` loops might suggest $O(N^2)$. However, we use **Aggregate Analysis**:

1.  **Insertion:** Each of the $N$ elements is inserted into the set exactly once. -> $O(N)$.
2.  **Deletion:** The `allNums.erase()` function is called exactly once for each unique element. Once an element is removed, it is never processed again (the `if (it != allNums.end())` check prevents re-entry). -> $O(N)$.
3.  **Lookups:** The `find` operation runs successfully $N$ times (total across all clusters) and fails at most $2N$ times (at the boundaries of each cluster). -> $O(N)$.

Total Time Complexity:
$$
T(N) = O(N) + O(N) + O(N) \implies T(N) \in O(N)
$$

### 3. Space Complexity Analysis

We store all unique elements in the hash set.
$$
S(N) = O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int maxSeq = 0, curSeq = 0;
        unordered_set<int> allNums;
        for(int i = 0; i < nums.size(); i++) {
            allNums.insert(nums[i]);
        }
        for(int i = 0; i < nums.size(); i++) {
            curSeq = 0;
            auto it = allNums.find(nums[i]);
            
            if (it != allNums.end()) {
                allNums.erase(*it);
                curSeq++;
                int l = 1;
                while (true) {
                    auto lowerEl = allNums.find(nums[i] - l);
                    if (lowerEl != allNums.end()) {
                        curSeq++;
                        allNums.erase(*lowerEl);
                        l++;
                    } else {
                        break;
                    }
                }
                int r = 1;
                while (true) {
                    auto higherEl = allNums.find(nums[i] + r);
                    if (higherEl != allNums.end()) {
                        curSeq++;
                        allNums.erase(*higherEl); 
                        r++;
                    } else {
                        break;
                    }
                }
                
                maxSeq = max(maxSeq, curSeq);
            }
        }
        return maxSeq;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).