# Day 5: Construct the Minimum Bitwise Array I

- **Difficulty:** Easy
- **Topics:** Bit Manipulation, Array, Math
- **LeetCode Link:** [Construct the Minimum Bitwise Array I](https://leetcode.com/problems/construct-the-minimum-bitwise-array-i/)
- **Author:** [Mihail Iazinschi](https://github.com/Misoding)

---

## 📝 Problem Statement

You are given an array `nums` consisting of $n$ prime integers. You need to construct an array `ans` of length $n$ such that, for each index $i$, the following condition holds:

$$
\text{ans}[i] \text{ OR } (\text{ans}[i] + 1) = \text{nums}[i]
$$

Additionally, you must **minimize** the value of `ans[i]`. If no such value exists for a given `nums[i]`, set `ans[i] = -1`.

**Constraints:**
* $1 \le \text{nums.length} \le 100$
* $2 \le \text{nums}[i] \le 1000$
* `nums[i]` is a prime number.

---

## 🔬 Formal Algorithmic Analysis

Although the constraints allow for a brute-force approach ($N \le 1000$), we implement an optimal bitwise solution with $O(1)$ complexity per element, derived from the properties of binary arithmetic.

### 1. Mathematical Abstraction

We analyze the operation $f(x) = x \lor (x+1)$.
Adding 1 to an integer $x$ flips the trailing sequence of `1`s to `0`s and flips the rightmost `0` bit to `1`.
Let the binary representation of $x$ be:
$$
x = \dots 0 \underbrace{11\dots1}_{k-1}
$$
Then:
$$
x+1 = \dots 1 \underbrace{00\dots0}_{k-1}
$$
The bitwise OR combines these, resulting in a sequence of $1$s:
$$
x \lor (x+1) = \dots 1 \underbrace{11\dots1}_{k-1}
$$

**Key Insight:** The result $P = \text{nums}[i]$ is identical to $x$, except that the bit at the position of the rightmost `0` in $x$ (let's say position $k$) has been flipped to `1`.
To reverse this and find the minimal $x$, we must take $P$ and flip the bit at position $k-1$ (the most significant bit of the trailing ones) back to `0`.

### 2. Algorithm Derivation

For each prime number $P$:
1.  **Parity Check:** If $P=2$ (even), the LSB is 0. The function $x \lor (x+1)$ always produces an odd number. Thus, for $P=2$, no solution exists ($ans[i] = -1$).
2.  **Bit Manipulation:** For odd primes, we isolate the sequence of trailing ones.
    * We can isolate the lowest `0` bit of $P$ using `~P`.
    * The expression `(P + 1)` sets the lowest `0` to `1` and clears trailing `1`s.
    * We use the formula: `mask = (P + 1) & ~P`. This gives us the bit at position $k$ (the first zero).
    * Shifting right `mask >> 1` gives us the bit at position $k-1$.
    * Subtracting this from $P$ gives the minimal $x$.

### 3. Complexity Calculation

**Time Complexity Analysis:**
We process each element using constant-time bitwise operations.
$$
T(n) = \sum_{i=0}^{n-1} O(1) \in \Theta(n)
$$

**Space Complexity Analysis:**
We allocate an array of size $n$ for the result.
$$
S(n) \in \Theta(n)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            if (nums[i] & 1){
                int new_bit_mask = (nums[i] + 1) & ~nums[i];
                new_bit_mask >>= 1;
                ans[i] = nums[i] - new_bit_mask;
            } else {
                ans[i] = -1;
            }
        }
        return ans;
    }
};
```

---

### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).