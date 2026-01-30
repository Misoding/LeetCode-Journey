# Day 15: Non-overlapping Intervals

- **Difficulty:** Medium
- **Topics:** Array, Greedy, Sorting, Dynamic Programming
- **LeetCode Link:** [Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given an array of intervals `intervals` where `intervals[i] = [start_i, end_i]`, return the **minimum number of intervals** you need to remove to make the rest of the intervals non-overlapping.

**Example:**
Input: `[[1,2],[2,3],[3,4],[1,3]]`
Output: `1`
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

---

## 🏗️ Deep-Dive Implementation Strategy

This is a classic **Interval Scheduling** problem. We want to find the *maximum* number of compatible intervals (Non-Overlapping) and subtract that from the total count to get the *minimum* removal count.

### 1. The Greedy Choice Property
To maximize the number of non-overlapping intervals we can keep, we should always pick the interval that **finishes earliest**.
* **Why?** By finishing as early as possible, we leave the maximum amount of "free time" for subsequent intervals to fit in.
* If we sorted by *start time*, we might pick a very long interval (e.g., `[0, 100]`) that starts early but blocks many short intervals (e.g., `[1,2], [3,4], [5,6]`).

### 2. Algorithm Workflow
1.  **Sort:** Sort the intervals based on their **end times** in ascending order.
2.  **Iterate:** Maintain a pointer `end` representing the end time of the last added interval.
3.  **Check:** For each subsequent interval:
    * If its **start time** is strictly less than the current `end`, it causes an overlap. We must remove it (increment `count`).
    * Otherwise, it fits. We "keep" it and update `end` to the new interval's end time.

### 3. Execution Visualization
Input: `[[1,2], [1,3], [2,3], [3,4]]`

**Step 1: Sort by End Time**
Sorted: `[1,2], [2,3], [1,3], [3,4]`
*(Note: [1,3] comes after [2,3] because they might be sorted stably or by start time as secondary key, but mainly end time matters).*

**Step 2: Linear Scan**
* **Init:** `lastInterval = [1,2]`. `res = -1` (Adjusted logic).
* **i=0 ([1,2]):** Overlaps with itself (logic artifact). `res` becomes 0. `lastInterval` remains `[1,2]`.
* **i=1 ([2,3]):** Start `2` >= Last End `2`. No overlap.
    * Update `lastInterval = [2,3]`.
* **i=2 ([1,3]):** Start `1` < Last End `3`. **Overlap!**
    * Increment removal: `res = 1`.
    * We discard `[1,3]` to keep the earlier ending `[2,3]`.
* **i=3 ([3,4]):** Start `3` >= Last End `3`. No overlap.
    * Update `lastInterval = [3,4]`.

**Final Result:** `1`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let $S = \{I_1, I_2, \dots, I_n\}$ be the set of intervals.
We seek a subset $S' \subseteq S$ of maximum size such that $\forall I_j, I_k \in S', I_j \cap I_k = \emptyset$.
The answer is $|S| - |S'|$.

**Correctness of Greedy:**
Let $i_1, i_2, \dots, i_k$ be the set of intervals chosen by Greedy (sorted by finish time $f_1 \le f_2 \le \dots \le f_k$).
Let $j_1, j_2, \dots, j_m$ be any optimal solution (sorted by finish time).
Since Greedy always picks the first available interval with the smallest finish time, we have $f(i_1) \le f(j_1)$. By induction, we can show that for any $r$, $f(i_r) \le f(j_r)$, meaning Greedy always leaves at least as much room as the optimal solution. Thus, Greedy finds a maximum set.

### 2. Time Complexity
* **Sorting:** The dominant operation is sorting the intervals.
    $$T_{sort}(N) = O(N \log N)$$
* **Linear Scan:** We iterate through the sorted array once.
    $$T_{scan}(N) = O(N)$$

**Total Time Complexity:**
$$
T(N) \in O(N \log N)
$$

### 3. Space Complexity
* **Sorting:** Depends on implementation (usually $O(\log N)$ stack space).
* **Storage:** No extra data structures used beyond loop variables.

$$
S(N) \in O(\log N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    static bool customCompare(vector<int> &a, vector<int> &b) {
        return a[1] < b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int res = -1;
        sort(intervals.begin(), intervals.end(), customCompare);
        vector<int> lastInterval = intervals[0];
        for(auto interval: intervals) {
            if (lastInterval[1] > interval[0]){
                res++;
            } else {
                lastInterval = interval;
            }
        }
        return res;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).