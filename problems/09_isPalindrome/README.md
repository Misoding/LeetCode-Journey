# 9. Palindrome Number

- **Difficulty:** Easy
- **Topics:** Math
- **LeetCode Link:** [Palindrome Number](https://leetcode.com/problems/palindrome-number/)
- **Author:** [Mihail Iazinschi](https://github.com/Misoding)

---

## 📝 Problem Statement

Given an integer `x`, return `true` if `x` is a **palindrome**, and `false` otherwise.

An integer is a palindrome when it reads the same forward and backward.
* For example, `121` is a palindrome while `123` is not.
* Negative numbers (e.g., `-121`) are not palindromes due to the minus sign.

---

## 💡 Algorithmic Analysis

This solution avoids converting the integer to a string (which would require extra space) and instead uses arithmetic operations to reverse the number mathematically.

### Method: Integral Reversal

The core idea is to construct the reverse of the number `x` by iteratively extracting the last digit. We then compare this reversed number with the original `x`.

#### Mathematical Derivation

1.  **Negative Case:** If $x < 0$, it cannot be a palindrome because of the sign (e.g., $-121$ reversed becomes $121-$).

2.  **Reversal Process:**
    Let $x$ be the input integer. We construct a new integer $R$ (reversed).
    In each iteration $k$, we extract the last digit $d_k = x \pmod{10}$ and append it to $R$:

$$
R_{new} = R_{old} \cdot 10 + (x \pmod{10})
$$

We then update $x$ by removing the last digit:

$$
x \leftarrow \lfloor x / 10 \rfloor
$$

3.  **Termination:** The loop continues until $x = 0$.

#### Complexity Analysis

Let $n$ be the value of the input integer `x`. The number of iterations in the `while` loop is determined by the number of digits in $x$.
The number of digits $d$ in an integer $x$ is given by:

$$
d = \lfloor \log_{10}(x) \rfloor + 1
$$

Therefore, the algorithm performs a constant number of arithmetic operations for each digit.

- **Time Complexity:** $O(\log n)$ (Since the loop runs proportional to the number of digits).
- **Space Complexity:** $O(1)$ (We only use a few variables for storage).

#### Implementation (C++)

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        // Step 1: Handle edge case for negative numbers
        if (x < 0) {
            return false;
        }

        long reversedInt = 0;
        int tmpNum = 0, initialNumber = x;

        // Step 2: Reverse the number mathematically
        while (x) {
            reversedInt *= 10;
            tmpNum = x % 10;
            reversedInt += tmpNum;
            x /= 10;
        }

        // Step 3: Compare original with reversed
        if ((long) initialNumber == reversedInt) {
            return true;
        }
        return false;
    }
};
```

---

### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).