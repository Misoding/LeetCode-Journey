# Day 41: Find Kth Bit in Nth Binary String

- **Difficulty:** Medium
- **Topics:** String, Recursion, Simulation
- **LeetCode Link:** [Find Kth Bit in Nth Binary String](https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given two positive integers `n` and `k`, the binary string $S_n$ is formed as follows:
* $S_1 = \text{"0"}$
* $S_i = S_{i-1} + \text{"1"} + \text{reverse}(\text{invert}(S_{i-1}))$ for $i > 1$

Where `+` denotes the concatenation operation, `reverse(x)` returns the reversed string `x`, and `invert(x)` inverts all the bits in `x` (`0` changes to `1` and `1` changes to `0`).

Return the $k^{th}$ bit in $S_n$. It is guaranteed that `k` is valid for the given `n`.

**Example 1:**
Input: `n = 3, k = 1`
Output: `"0"`
Explanation: $S_3$ is `"0111001"`. The 1st bit is `"0"`.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem defines a string sequence that grows fractally. Since $n$ is strictly bounded by 20, the length of $S_{20}$ is exactly $2^{20} - 1 = 1,048,575$ characters. This bound allows us to simulate the exact string construction process rather than relying strictly on implicit mathematical recursion.



### 1. Iterative String Construction
We start with the base case `startString = "0"`.
For each subsequent level from $2$ to $n$, we apply the defined transformation rules directly:
1.  **Inversion:** We iterate through a copy of the current string and flip every `'0'` to `'1'` and vice-versa.
2.  **Reversal:** We apply the standard `std::reverse` algorithm from the C++ STL to the inverted string.
3.  **Concatenation:** We assemble the new state as `startString + "1" + reversed_inverted_string`.

### 2. Execution Visualization
Input: `n = 4, k = 11`

* **Iteration 1 ($S_1$):** `"0"`
* **Iteration 2 ($S_2$):** `"0" + "1" + reverse(invert("0"))` $\to$ `"011"`
* **Iteration 3 ($S_3$):** `"011" + "1" + reverse(invert("011"))` $\to$ `"011" + "1" + "001"` $\to$ `"0111001"`
* **Iteration 4 ($S_4$):** `"0111001" + "1" + "0110001"` $\to$ `"011100110110001"`

We then simply return the character at the 0-indexed position $k-1$. For $k = 11$, index is 10, returning `'1'`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $L(n)$ be the length of the string $S_n$. The length follows the recurrence relation:

$$
L(n) = 2 \cdot L(n-1) + 1 \quad \text{with} \quad L(1) = 1
$$

Solving this linear recurrence yields:

$$
L(n) = 2^n - 1
$$

The string generation physically builds this sequence step-by-step.

### 2. Time Complexity Analysis

At each step $i$, we invert and reverse a string of length $2^{i-1}-1$, which takes $\Theta(2^{i-1})$ operations.
The total time required to build $S_n$ is the sum of operations across all iterations:

$$
T(n) = \sum_{i=2}^{n} \Theta(2^{i-1}) = \Theta(2^n)
$$

Given the maximum constraint $n=20$, $2^{20} \approx 10^6$ operations, which evaluates in just a few milliseconds.

$$
T(n) \in O(2^n)
$$

### 3. Space Complexity Analysis

The spatial requirement is defined by the maximum length of the string held in memory. At the final step, the string $S_n$ occupies exactly $2^n - 1$ bytes (characters).

$$
S(n) = \Theta(2^n)
$$

$$
S(n) \in O(2^n)
$$

*(Note: While an $O(n)$ space and time recursive algorithm exists by traversing the implicit tree structure mathematically, the $O(2^n)$ simulation is highly effective and optimal given the memory constraints of modern systems).*

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
     
    string invertString(string s) {
        string cpy = s;
        for(int i = 0; i<s.length();i++){
            cpy[i] = cpy[i] == '0' ? '1' : '0';
        }
        return cpy;
    }
    char findKthBit(int n, int k) {
        string startString = "0";
        for(int i = 0; i<n-1; i++) {
            string res = invertString(startString);
            reverse(res.begin(), res.end());
            startString = startString + "1" + res;
        }
        return startString[k-1];
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).