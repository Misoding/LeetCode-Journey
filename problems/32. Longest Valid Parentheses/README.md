# Day 43: Longest Valid Parentheses

- **Difficulty:** Hard
- **Topics:** String, Stack, Dynamic Programming
- **LeetCode Link:** [Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a string containing just the characters `'('` and `')'`, return the length of the longest valid (well-formed) parentheses substring.

**Example 1:**
Input: `s = "(()"`
Output: `2`
Explanation: The longest valid parentheses substring is `"()"`.

**Example 2:**
Input: `s = ")()())"`
Output: `4`
Explanation: The longest valid parentheses substring is `"()()"`.

---

## 🏗️ Deep-Dive Implementation Strategy

The classical stack approach for this problem involves pushing string *indices* to calculate distances. However, this implementation uses a more functional, **State Preservation Stack** approach that counts *valid pairs*.

### 1. The State Machine Logic
We maintain a variable `currentStreak` which tracks the number of adjacent valid parenthesis pairs formed at the current depth level.
* **Encountering `'('` (State Push):** We are entering a new depth level. We must pause our current sequence. We push the `currentStreak` onto the stack (saving the valid pairs formed *just before* this new open parenthesis) and reset `currentStreak = 0` to start evaluating the inner contents.
* **Encountering `')'` (State Pop & Merge):**
    * **Invalid Case (`st.empty()`):** There is no matching open parenthesis. The contiguous chain is definitively broken. We reset `currentStreak = 0`.
    * **Valid Case:** A valid pair is formed. The new chain length at this level is the sum of:
        1. `1` (The pair just closed: `()`)
        2. `currentStreak` (Any valid pairs that were completely enclosed within this pair)
        3. `st.top()` (The contiguous valid pairs that existed immediately before the matching `'('`)
    We pop the stack and update the global `maxStreak`.

### 2. Execution Visualization
Input: `s = "()(())"`

1. `i = 0`, char = `'('` $\to$ Push `0`. `currentStreak = 0`. Stack: `[0]`
2. `i = 1`, char = `')'` $\to$ Stack not empty. `currentStreak = 1 + 0 + Pop(0) = 1`. `maxStreak = 1`. Stack: `[]`
3. `i = 2`, char = `'('` $\to$ Push `currentStreak` (1). `currentStreak = 0`. Stack: `[1]`
4. `i = 3`, char = `'('` $\to$ Push `currentStreak` (0). `currentStreak = 0`. Stack: `[1, 0]`
5. `i = 4`, char = `')'` $\to$ Stack not empty. `currentStreak = 1 + 0 + Pop(0) = 1`. `maxStreak = 1`. Stack: `[1]`
6. `i = 5`, char = `')'` $\to$ Stack not empty. `currentStreak = 1 + 1 (inner) + Pop(1) (before) = 3`. `maxStreak = 3`. Stack: `[]`

Final result: `maxStreak * 2 = 6`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $S_i$ be the contiguous valid pair streak accumulated up to index $i$.
The stack maintains a history of streaks $H$.
The transition function upon processing character $C_i$ is defined as:

$$
S_i = \begin{cases} 
0 & \text{if } C_i = \text{'('} \ (\text{and push } S_{i-1} \text{ to } H) \\
0 & \text{if } C_i = \text{')'} \land H = \emptyset \ (\text{invalid configuration}) \\
1 + S_{i-1} + \text{pop}(H) & \text{if } C_i = \text{')'} \land H \neq \emptyset
\end{cases}
$$

The objective is to find $2 \cdot \max(S_i)$ for all $i \in \{0, \dots, N-1\}$.

### 2. Time Complexity Analysis

The string is parsed exactly once from left to right.
For each character, the stack operations (`push`, `pop`, `top`) and basic arithmetic operations evaluate in strict $\Theta(1)$ constant time.

$$
T(N) = \sum_{i=0}^{N-1} \Theta(1) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

In the worst-case scenario where the string consists entirely of left parentheses (e.g., `"(((((((("`), the stack will push $N$ zero-values, occupying space proportional to the input length.

$$
S(N) = O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        int currentStreak = 0;
        int maxStreak = 0;
        for(int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(currentStreak);
                currentStreak = 0;
            } else {
                if (st.empty()) {
                    currentStreak = 0;
                } else {
                    currentStreak = 1 + currentStreak + st.top();
                    st.pop();
                    maxStreak = max(currentStreak, maxStreak);
                }
            }
        }        
        return maxStreak * 2;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).