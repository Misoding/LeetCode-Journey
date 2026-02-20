# Day 30: Special Binary String

- **Difficulty:** Hard
- **Topics:** String, Recursion, Sorting, Divide and Conquer
- **LeetCode Link:** [Special Binary String](https://leetcode.com/problems/special-binary-string/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Special binary strings are binary strings with the following two properties:
1. The number of `0`'s is equal to the number of `1`'s.
2. Every prefix of the binary string has at least as many `1`'s as `0`'s.

You are given a special binary string `s`. A move consists of choosing two consecutive, non-empty, special substrings of `s`, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.

Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.

**Example 1:**
Input: `s = "11011000"`
Output: `"11100100"`
Explanation: The strings `"10"` [substrings(2,3)] and `"1100"` [substrings(4,7)] are swapped.

---

## 🏗️ Deep-Dive Implementation Strategy

This problem is deeply mathematical. A "Special Binary String" is structurally identical to a **Valid Parentheses String**, where `1` acts as an open parenthesis `(` and `0` acts as a close parenthesis `)`.

The allowed operation—swapping adjacent special substrings—is equivalent to rearranging the order of sibling subtrees in the hierarchical tree representation of the parentheses. To maximize the lexicographical value, we must sort the siblings at every level in descending order.

### 1. The Divide and Conquer Approach
We can decompose the algorithm into three phases:
1.  **Decomposition (Parsing):** We scan the string using a counter (`+1` for `1`, `-1` for `0`). When the counter hits `0`, we have found a "primitive" or "irreducible" special substring. An irreducible substring cannot be split into two smaller special strings and always takes the form `1 + M + 0` (or `( M )`).
2.  **Recursion:** For each irreducible substring, we extract the inner core `M`, recursively apply the `makeLargestSpecial` algorithm to it, and then reconstruct the component as `1 + M' + 0`.
3.  **Sorting & Reassembly:** We collect all the optimally transformed irreducible components at the current level into a vector, sort them in lexicographically descending order, and concatenate them.

### 2. Execution Visualization
Input: `s = "11011000"`

* **Phase 1: Decomposition**
    * Scan: `1` (c=1), `1` (c=2), `0` (c=1), `1` (c=2), `1` (c=3), `0` (c=2), `0` (c=1), `0` (c=0).
    * Entire string is one irreducible block: `1 [101100] 0`.
* **Recursion on inner core `M = "101100"`:**
    * Scan `101100`:
        * `10` -> c=0. Block 1: `1 [] 0`. Inner is empty.
        * `1100` -> c=0. Block 2: `1 [10] 0`.
            * Recursion on `10`: Block `1 [] 0`. Returns `"10"`.
            * Block 2 becomes `"1100"`.
    * Blocks of `M`: `{"10", "1100"}`.
    * Sort descending: `{"1100", "10"}`.
    * Reassemble `M'`: `"110010"`.
* **Final Reassembly:**
    * Reconstruct original block: `1 + "110010" + 0` = `"11100100"`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model (Bijection to Trees)

Let $\mathcal{S}$ be the set of special binary strings. There exists a bijection between $\mathcal{S}$ and ordered rooted trees.
Any $S \in \mathcal{S}$ can be uniquely factorized into irreducible special strings:

$$
S = P_1 P_2 \dots P_k
$$

Every irreducible string $P_i$ can be written as:

$$
P_i = 1 \cdot M_i \cdot 0 \quad \text{where } M_i \in \mathcal{S}
$$

The operation of swapping adjacent valid substrings $P_i$ and $P_{i+1}$ allows us to achieve any permutation of the irreducible components. To maximize the string lexicographically, we simply require:

$$
P'_1 \ge P'_2 \ge \dots \ge P'_k \quad \text{(lexicographically)}
$$

where $P'_i = 1 \cdot \text{Optimize}(M_i) \cdot 0$.

### 2. Time Complexity Analysis

Let $N$ be the length of the string.
* In the worst case (a flat string like `"10101010"`), the recursion depth is 1, but we sort $N/2$ strings of length 2. Sorting strings takes $O(K \log K \cdot L)$ where $K$ is the number of strings and $L$ is their length.
* In the worst deeply nested case (e.g., `"111...000"`), the recursion depth is $N/2$, and we do $O(N)$ string slicing at each level.

The string concatenation and substring extraction `s.substr()` at each recursive level dictate the upper bound.
The recurrence relation for the worst-case nested structure is $T(N) = T(N-2) + O(N)$, which resolves to:

$$
T(N) = \Theta(N^2)
$$

### 3. Space Complexity Analysis

Each recursive call allocates new strings (`internBracket`, `orderedIntern`) and vectors. The maximum recursion depth is $N/2$.

$$
S(N) = \Theta(N^2) \quad \text{(due to substring copies on the call stack)}
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    string makeLargestSpecial(string s) {
        vector<string> blocks;
        int openCounter = 0, begin = 0;
        for(int i = 0;i < s.length(); i++) {
            if (s[i] == '1'){
                openCounter++;
            } else {
                openCounter--;
            }
            if (openCounter == 0) {
                string internBracket = s.substr(begin + 1, i - begin - 1);
                string orderedIntern = "1" + makeLargestSpecial(internBracket) + "0";
                blocks.push_back(orderedIntern);
                begin = i + 1;
            }
        }
        sort(blocks.begin(), blocks.end(), greater<string>());
            string orderedString = "";
            for(int j = 0; j < blocks.size(); j++) {
                orderedString += blocks[j];
            }
            return orderedString;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).