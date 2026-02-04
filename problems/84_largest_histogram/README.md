# Day 20: Largest Rectangle in Histogram

- **Difficulty:** Hard
- **Topics:** Array, Stack, Monotonic Stack
- **LeetCode Link:** [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given an array of integers `heights` representing the histogram's bar height where the width of each bar is `1`, return the **area of the largest rectangle** in the histogram.

**Example:**
Input: `heights = [2, 1, 5, 6, 2, 3]`
Output: `10`
Explanation: The largest rectangle has a height of 5 and a width of 2 (covering indices 2 and 3), giving an area of 10.

---

## 🏗️ Deep-Dive Implementation Strategy

The brute force approach checks every pair of bars, taking $O(N^2)$. We need an $O(N)$ approach. The key observation is that a rectangle is defined by its **minimum height** bar. For any bar `i` with height `h`, if we know the first bar to the left (`L`) and the first bar to the right (`R`) that are *shorter* than `h`, the maximum width for a rectangle of height `h` is `(R - L - 1)`.

We use a **Monotonic Increasing Stack** to efficiently find these boundaries.

### 1. The "Width Accumulation" Technique
Your implementation uses a clever variation where we calculate the width dynamically.
* We define a `stackBar` structure holding `{height, width}`.
* **Invariant:** The stack always contains bars with non-decreasing heights.
* **Sentinel:** We append a `0` at the end of `heights`. This forces the stack to be completely emptied at the end, ensuring all potential rectangles are calculated.

### 2. The Algorithm Flow
1.  Iterate through `heights`.
2.  **Push Condition:** If the current bar is taller than the stack top, simply push it with `width = 1`.
3.  **Pop Condition:** If the current bar is shorter, it means the rectangle formed by the stack top **cannot extend further to the right**.
    * We pop the top bar (`lastBar`).
    * We accumulate its width into a running `maxWidth`.
    * **Calculate Area:** The popped bar could extend to the right (up to current index) and to the left (based on its stored `barWidth`). The area is `lastBar.height * maxWidth`.
    * **Merge Width:** The current bar (which caused the pop) can technically "extend" backwards over the taller bars we just removed. We update `currentBar.width += maxWidth` before pushing it.

### 3. Execution Visualization
Input: `[2, 1, 5, 6, 2, 3]` + `[0]` (Sentinel)

* **i=0 (H=2):** Stack: `[{2, 1}]`
* **i=1 (H=1):** `1 < 2`. Pop `{2, 1}`.
    * `maxWidth = 1`. Area = `2 * 1 = 2`.
    * Current `{1, 1}` absorbs width: `{1, 1+1} -> {1, 2}`.
    * Push `{1, 2}`. Stack: `[{1, 2}]`.
* **i=2 (H=5):** Push `{5, 1}`. Stack: `[{1, 2}, {5, 1}]`.
* **i=3 (H=6):** Push `{6, 1}`. Stack: `[{1, 2}, {5, 1}, {6, 1}]`.
* **i=4 (H=2):** `2 < 6`. Pop `{6, 1}`.
    * `maxWidth = 1`. Area = `6 * 1 = 6`.
    * `2 < 5`. Pop `{5, 1}`.
    * `maxWidth` becomes `1 + 1 = 2`. Area = `5 * 2 = 10` (**Max**).
    * Current `{2, 1}` absorbs width: `{2, 1+2} -> {2, 3}`.
    * Push `{2, 3}`. Stack: `[{1, 2}, {2, 3}]`.
* **i=5 (H=3):** Push `{3, 1}`. Stack: `[{1, 2}, {2, 3}, {3, 1}]`.
* **i=6 (H=0):** Sentinel forces everything to pop.
    * Pop `{3, 1}`, Area `3*1`.
    * Pop `{2, 3}`, Area `2*(1+3)=8`.
    * Pop `{1, 2}`, Area `1*(1+3+2)=6`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let $H[i]$ be the height of the bar at index $i$.
For each $i$, we want to find:
$$ L_i = \max \{ k < i \mid H[k] < H[i] \} $$
$$ R_i = \min \{ k > i \mid H[k] < H[i] \} $$
The area centered at $i$ is $H[i] \times (R_i - L_i - 1)$.
The stack maintenance ensures that when we process index $i$, we determine $R$ for elements in the stack, and the accumulated width implicitly tracks $(R - L)$.

### 2. Time Complexity
Every element is pushed onto the stack exactly once and popped exactly once. The operations inside the loop are constant time.
$$ T(N) = O(N) $$

### 3. Space Complexity
In the worst case (a strictly increasing array), the stack stores all $N$ elements.
$$ S(N) = O(N) $$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    struct stackBar {
        int barHeight;
        int barWidth;
    };
    int largestRectangleArea(vector<int>& heights) {
        // area = max(min(cur_bar_min_height, stack_last_el_height) * (stack_last_el_width + 1), cur_bar_min_height)
        // fail on [5 9 9]
        stack<stackBar> bars;
        int maxRectangle = 0, n = heights.size();
        heights.push_back(0);
        for(int i = 0; i < n+1; i++) {
           stackBar currentBar = {heights[i], 1};
           int maxWidth = 0;
           while (!bars.empty() && bars.top().barHeight >= currentBar.barHeight) {
                stackBar lastBar = bars.top();
                bars.pop();
                maxWidth += lastBar.barWidth;
                maxRectangle = max(maxRectangle, maxWidth * lastBar.barHeight);
           }
           currentBar.barWidth +=maxWidth;
           bars.push(currentBar);
        }
        return maxRectangle;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).