# Day 31: Prime Number of Set Bits in Binary Representation

- **Difficulty:** Easy
- **Topics:** Math, Bit Manipulation
- **LeetCode Link:** [Prime Number of Set Bits](https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given two integers `left` and `right`, return the **count** of numbers in the inclusive range `[left, right]` having a **prime number of set bits** in their binary representation.

Recall that the number of set bits an integer has is the number of `1`'s present when written in binary.
For example, `21` written in binary is `10101`, which has `3` set bits.

**Example 1:**
Input: `left = 6, right = 10`
Output: `4`
Explanation:
* `6`  -> `110` (2 set bits, 2 is prime)
* `7`  -> `111` (3 set bits, 3 is prime)
* `8`  -> `1000` (1 set bit, 1 is not prime)
* `9`  -> `1001` (2 set bits, 2 is prime)
* `10` -> `1010` (2 set bits, 2 is prime)
4 numbers have a prime number of set bits.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem requires us to evaluate every integer in a given range. The evaluation consists of two independent phases: counting the set bits (Hamming weight) and checking if that count is a prime number.

### 1. Bitwise Counting (Hamming Weight)
To count the number of set bits, we use a standard bitwise shift operation. 
We check the least significant bit (LSB) using the bitwise AND operator `tmp & 1`. Then, we discard the LSB by logically shifting the number to the right by one position `tmp >>= 1`. This loop continues until `tmp` becomes `0`.



### 2. $O(1)$ Primality Check via Constraints Analysis
A general primality test takes $O(\sqrt{k})$. However, we must analyze the problem constraints.
The maximum value for `right` is $10^6$.
Since $10^6 < 2^{20} = 1,048,576$, the maximum number of bits any number in our range can have is strictly under 20.

The only possible prime numbers of set bits are those under 20: 
$\{2, 3, 5, 7, 11, 13, 17, 19\}$.

By hardcoding these 8 primes into an array, the primality check becomes an $O(1)$ bounded loop (or a bitmask check in more advanced implementations), avoiding expensive modulo operations.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $B(x)$ be the function that returns the number of set bits in $x$:

$$
B(x) = \sum_{k=0}^{\lfloor \log_2 x \rfloor} \left( \lfloor \frac{x}{2^k} \rfloor \bmod 2 \right)
$$

Let $P$ be a set containing the primes $\{2, 3, 5, 7, 11, 13, 17, 19\}$.
We are asked to compute the cardinality of the set $S$:

$$
S = \{ x \in [\text{left}, \text{right}] \mid B(x) \in P \}
$$

$$
\text{Result} = |S|
$$

### 2. Time Complexity Analysis

Let $N = \text{right} - \text{left} + 1$ be the size of the range.
For each number $x$, counting the bits takes a number of operations proportional to the bit-length of $x$, which is bounded by $\lceil \log_2(10^6) \rceil = 20$.
The prime check iterates through an array of size 8, representing a strict $O(1)$ constant time limit.

$$
T(N) = \sum_{x=\text{left}}^{\text{right}} (\Theta(\log_2 x) + O(1)) \le N \cdot (20 + 8) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The algorithm utilizes a fixed-size integer array of 8 elements and a few integer accumulators. It does not scale with the input size.

$$
S(N) = \Theta(1)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        int primeCounter = 0;
        int primes[] = {2,3,5,7,11,13,17,19};
        for(int i = left; i <= right; i++) {
            int count = 0;
            int tmp = i;
            while (tmp) {
                count += tmp&1;
                tmp>>=1;
            }
            for(int j = 0; j < 8; j++) {
                if (primes[j] == count) {
                    primeCounter++;
                }
            }
        }
        return primeCounter;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).