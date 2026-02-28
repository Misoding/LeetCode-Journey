# Day 38: Concatenation of Consecutive Binary Numbers

- **Difficulty:** Medium
- **Topics:** Math, Bit Manipulation
- **LeetCode Link:** [Concatenation of Consecutive Binary Numbers](https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given an integer `n`, return the decimal value of the binary string formed by concatenating the binary representations of `1` to `n` in order, **modulo** $10^9 + 7$.

**Example 1:**
Input: `n = 3`
Output: `27`
Explanation: In binary, 1, 2, and 3 corresponds to `"1"`, `"10"`, and `"11"`.
After concatenating them, we have `"11011"`, which corresponds to the decimal value 27.

**Example 2:**
Input: `n = 12`
Output: `505379714`

---

## 🏗️ Deep-Dive Implementation Strategy

The problem demands simulating the concatenation of binary strings, but doing so using actual strings would lead to $O(N \log N)$ space and Time Limit Exceeded (TLE) errors. We must use bitwise math.

### 1. Bitwise Concatenation
Concatenating a new number $i$ to an existing binary result $R$ requires:
1.  Finding the bit-length of $i$ (let's call it $L$).
2.  Shifting $R$ to the left by $L$ bits (creating space of exactly $L$ zeros at the rightmost end).
3.  Bitwise OR-ing the new number $i$ into those zeros.

### 2. Hardware-Level Optimization: `__builtin_clz`
To find the bit-length $L$ of a 32-bit integer $i$, we can count its leading zeros.
The GCC compiler provides a built-in function `__builtin_clz(i)` which maps directly to hardware instructions (like `LZCNT` or `BSR` in x86 architecture). 
Since a 32-bit integer has 32 bits, the length of the number $i$ without leading zeros is exactly:

$$
L = 32 - \text{\_\_builtin\_clz}(i)
$$

This operates in strict $O(1)$ hardware time, vastly outperforming `log2(i) + 1` or iterative counting.

### 3. Overflow Prevention
The modulo is $10^9 + 7$. Since $n \le 10^5$, the maximum bit-length shifted is 17. Shifting a value bounded by $10^9+7$ left by 17 bits requires roughly $30 + 17 = 47$ bits. This exceeds a standard 32-bit `int` but fits perfectly inside a 64-bit `unsigned long long`, preventing overflow before the modulo operation truncates it back.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $R_i$ be the concatenated value up to integer $i$, and $L_i$ be the bit-length of $i$:

$$
L_i = \lfloor \log_2(i) \rfloor + 1
$$

The recurrence relation for the concatenation under modulo $M$ is defined as:

$$
R_i = (R_{i-1} \cdot 2^{L_i} + i) \pmod M
$$

Given the initial condition $R_1 = 1$, we iteratively apply this recurrence using bitwise equivalents: $R_{i-1} \cdot 2^{L_i} \equiv R_{i-1} \ll L_i$.

### 2. Time Complexity Analysis

The algorithm evaluates the recurrence relation inside a single loop from $2$ to $N$.
At each iteration, we perform hardware-accelerated leading-zero counting, bitwise shifts, bitwise ORs, and modulo arithmetic. All these operations resolve in constant $\Theta(1)$ time.

$$
T(N) = \sum_{i=2}^{N} \Theta(1) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The state is maintained via a single 64-bit integer (`res`), regardless of the input size $N$.

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
    int concatenatedBinary(int n) {
        unsigned long long res = 1;
        unsigned long long modulo = 1e9 + 7;
        
        for(int i = 2; i <= n; i++){
            res = ((res << (32 - __builtin_clz(i))) | i) % modulo;
        }
        return res;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).