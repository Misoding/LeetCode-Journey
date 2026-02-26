# Day 36: Number of Steps to Reduce a Number in Binary Representation to One

- **Difficulty:** Medium
- **Topics:** String, Bit Manipulation, Simulation
- **LeetCode Link:** [Number of Steps to Reduce a Number in Binary Representation to One](https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given the binary representation of an integer as a string `s`, return the number of steps to reduce it to `1` under the following rules:
* If the current number is even, you have to divide it by `2`.
* If the current number is odd, you have to add `1` to it.

It is guaranteed that you can always reach one for all test cases.

**Example 1:**
Input: `s = "1101"`
Output: `6`
Explanation: `"1101"` corresponds to `13`.
1. 13 is odd, add 1 $\to$ 14 (`"1110"`)
2. 14 is even, divide by 2 $\to$ 7 (`"111"`)
3. 7 is odd, add 1 $\to$ 8 (`"1000"`)
4. 8 is even, divide by 2 $\to$ 4 (`"100"`)
5. 4 is even, divide by 2 $\to$ 2 (`"10"`)
6. 2 is even, divide by 2 $\to$ 1 (`"1"`)

---

## 🏗️ Deep-Dive Implementation Strategy

The string length can be up to 500 characters, meaning the numeric value can reach $2^{500}$. This completely overflows standard 64-bit integers (`unsigned long long`). We must simulate the arithmetic directly on the string structure.



### 1. Data Structure Choice: `std::deque`
A `std::deque<char>` is the optimal container for this simulation:
* **Division by 2:** Mathematically equivalent to a logical right shift (`>> 1`). On a string representation, this means discarding the last character. `deque.pop_back()` handles this in $O(1)$ time.
* **Addition by 1:** If the LSB is `1`, adding `1` causes a cascade of carry bits moving from right to left. We traverse backwards, flipping `1`s to `0`s until we find a `0` to flip to `1`.
* **Overflow Handling:** If the carry propagates past the Most Significant Bit (MSB), we need to prepend a new `1`. `deque.push_front('1')` handles this efficiently in $O(1)$ time.

### 2. Execution State Machine
We loop until the `deque` contains exactly one character, which is `'1'`.
* Extract `lastBit = num.back()`.
* If `'0'`: Remove it (`pop_back()`).
* If `'1'`: Start carry propagation loop. Flip trailing `'1'`s to `'0'`s, and set the first encountered `'0'` to `'1'`. Handle terminal overflow if needed.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the binary string denote an integer $X$. The state transition function $f(X)$ is defined as:

$$
f(X) = \begin{cases} \frac{X}{2} & \text{if } X \equiv 0 \pmod 2 \\ X + 1 & \text{if } X \equiv 1 \pmod 2 \end{cases}
$$

In the binary domain, $X \equiv 0 \pmod 2$ implies the LSB is `0`. 
When $X \equiv 1 \pmod 2$, adding 1 transforms a suffix of the form `011...1` into `100...0`. This operation increases the bit-length by 1 if there is no leading `0` (e.g., `111` $\to$ `1000`).

### 2. Time Complexity Analysis

Let $N$ be the initial length of the string `s`.
At first glance, the nested `while` loop for carry propagation might suggest an $O(N^2)$ complexity. However, we must use **Amortized Analysis**.
* Every time we flip a sequence of $K$ bits of `'1'` to `'0'`, we do $O(K)$ work.
* But those $K$ bits are now `'0'`. In the subsequent steps, they will simply be popped off in $O(1)$ time per bit.
* A bit can be flipped from `'1'` to `'0'` at most once during the addition phase before it is eventually popped.
* The maximum number of operations is strictly bounded by $2N$ (since adding 1 to a sequence of `1`s generates trailing `0`s that are immediately consumed).

$$
T(N) = \Theta(N) \text{ (Amortized)}
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

We copy the input string into a `std::deque` of characters. In the worst case, the deque grows by at most 1 character (from terminal overflow) before elements are consumed.

$$
S(N) = \Theta(N)
$$

$$
S(N) \in O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int numSteps(string s) {
        int stepsLen = 0;
        deque<char> num(s.begin(), s.end());
        while(!(num.size() == 1 && num.front() == '1')) {
            char lastBit = num.back();
            stepsLen++;
            if (lastBit == '0') {
                num.pop_back();
            } else if(lastBit == '1') {
                bool carryBit = true;
                int i = num.size()-1;
                while(i >= 0 && carryBit) {
                    if (num[i] == '0') {
                        num[i] = '1';
                        carryBit=false;
                    } else if (num[i] == '1') {
                        num[i] = '0';
                    }
                    i--;
                }
                if (carryBit) {
                    num.push_front('1');
                    carryBit = false;
                }
            }

        }
        return stepsLen;

    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).