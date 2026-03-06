# Day 44: Check if Binary String Has at Most One Segment of Ones

- **Difficulty:** Easy
- **Topics:** String
- **LeetCode Link:** [Check if Binary String Has at Most One Segment of Ones](https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a binary string `s` without leading zeros, return `true` if `s` contains **at most one contiguous segment of ones**. Otherwise, return `false`.

**Example 1:**
Input: `s = "1001"`
Output: `false`
Explanation: The ones do not form a contiguous segment.

**Example 2:**
Input: `s = "110"`
Output: `true`

---

## 🏗️ Deep-Dive Implementation Strategy

The problem requires us to determine the number of distinct, isolated groups (blocks) of `1`s in the string. Since the string is guaranteed to start with `'1'` (no leading zeros), a valid string must have exactly one block of `1`s, possibly followed by `0`s.

### 1. Block Counting via Pointer Acceleration
Instead of tracking previous states, the algorithm uses a direct block-counting simulation:
1.  **Scan:** Iterate through the string with index `i`.
2.  **Identify Block Start:** If `s[i] == '1'`, we found the start of a block. We increment our `blocks` counter.
3.  **Consume Block:** We enter an inner `while` loop that continues to increment `i` as long as `s[i]` remains `'1'`. This effectively consumes the entire contiguous segment in one go.
4.  **Validation:** After the string is fully parsed, we check if `blocks == 1`. Since the first character is always `'1'`, the block count will be at least 1. If it's exactly 1, the condition holds.

### 2. Execution Visualization
Input: `s = "1001"`

* `i = 0`, char = `'1'`:
    * `blocks = 1`.
    * Inner `while` loop consumes `s[0]`. `i` becomes 1.
* `i = 1`, char = `'0'`: Loop continues.
* `i = 2`, char = `'0'`: Loop continues.
* `i = 3`, char = `'1'`:
    * `blocks = 2`.
    * Inner `while` loop consumes `s[3]`. `i` becomes 4.
* End of string. `blocks` is 2 $\neq$ 1. Returns `false`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the binary string be a sequence of bits $S = s_0, s_1, \dots, s_{n-1}$.
We define a connected component (segment) of `1`s as a maximal contiguous subsequence $s_i, \dots, s_j$ such that $\forall k \in [i, j], s_k = 1$.
The algorithm calculates the cardinality of the set of all such components, $|C|$. 
The string is valid if and only if $|C| \le 1$. Given the constraint $s_0 = 1$, the requirement tightens to $|C| = 1$.

### 2. Time Complexity Analysis

Although there is a nested `while` loop inside the `for` loop, the index `i` is strictly incremented and never reset. Every character in the string is evaluated at most twice (once in the outer loop boundary check, once in the inner loop). 
Let $N$ be the length of the string.

$$
T(N) = \sum_{i=0}^{N-1} \Theta(1) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The algorithm utilizes only two primitive integer variables (`blocks`, `i`) irrespective of the string's length.

$$
S(N) = \Theta(1)
$$

$$
S(N) \in O(1)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    bool checkOnesSegment(string s) {
        int blocks = 0;
        for(int i = 0; i < s.length();i++) {
            if (s[i] == '1') blocks++;
            while(i < s.length() && s[i] == '1') {
                i++;
            }
        }
        if (blocks == 1) return true;
        return false;
    }
};
```

---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).