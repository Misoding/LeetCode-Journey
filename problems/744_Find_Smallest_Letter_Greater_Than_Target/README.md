# Day 16: Find Smallest Letter Greater Than Target

- **Difficulty:** Easy
- **Topics:** Array, Binary Search
- **LeetCode Link:** [Find Smallest Letter Greater Than Target](https://leetcode.com/problems/find-smallest-letter-greater-than-target/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an array of characters `letters` that is sorted in **non-decreasing order**, and a character `target`. There are at least two different characters in `letters`.

Return the **smallest character** in `letters` that is strictly **greater** than `target`. If such a character does not exist, return the first character in `letters`.

**Example 1:**
Input: `letters = ["c", "f", "j"], target = "a"`
Output: `"c"`
Explanation: The smallest character strictly greater than 'a' is 'c'.

**Example 2:**
Input: `letters = ["c", "f", "j"], target = "c"`
Output: `"f"`
Explanation: The smallest character strictly greater than 'c' is 'f'.

**Example 3 (Wrap Around):**
Input: `letters = ["c", "f", "j"], target = "z"`
Output: `"c"`
Explanation: There are no characters > 'z', so we wrap around to the first character 'c'.

---

## 🏗️ Deep-Dive Implementation Strategy

Since the array is sorted, we can use **Binary Search** to find the answer in logarithmic time instead of scanning linearly.

### 1. The Search Logic (Upper Bound)
We are looking for the smallest element `x` such that `x > target`.
* **Initialization:** We assume the answer might default to `letters[0]` (the wrap-around case). We set `l = 0`, `r = n - 1`.
* **Decision at `mid`:**
    * If `letters[mid] <= target`: The candidate must be to the **right**. We discard the left half (`l = mid + 1`).
    * If `letters[mid] > target`: This is a valid candidate. It *might* be the smallest greater, or there might be an even smaller one to the left. We record it in `res` and try to move **left** (`r = mid - 1`).

### 2. Execution Visualization
Consider `letters = ["c", "f", "j"]`, `target = "c"`.
Init: `res = 'c'`, `l = 0`, `r = 2`.

* **Iteration 1:**
    * `mid = 1` ('f').
    * Is `'f' > 'c'`? **Yes**.
    * Update `res = 'f'`.
    * Move left: `r = 0`.
* **Iteration 2:**
    * `mid = 0` ('c').
    * Is `'c' > 'c'`? **No** (`'c' == 'c'`).
    * Move right: `l = 1`.
* **Termination:** `l (1) > r (0)`. Break.
* **Result:** `'f'`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let $L$ be the sorted sequence of characters. We define the solution as:
$$
ans = \min \{ c \in L \mid c > target \}
$$
If the set $\{ c \in L \mid c > target \}$ is empty, then $ans = L[0]$.

This corresponds to finding the **Upper Bound** of `target` in the sequence.

### 2. Time Complexity
Binary search halves the search space at every step.
Let $N$ be the number of characters in `letters`.
$$T(N) = O(\log N)$$

### 3. Space Complexity
We only use a few auxiliary variables (`l`, `r`, `mid`, `res`).
$$S(N) = O(1)$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int l = 0, r = letters.size() -1;
        int res = letters[0];
        while (l <= r) {
            int mid = l + (r-l) / 2;
            if (letters[mid] == target) {
                l = mid + 1;
            } else if (letters[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
                res = letters[mid];
            }
        }
        return res;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).