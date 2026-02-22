# Day 32: Binary Gap

- **Difficulty:** Easy
- **Topics:** Bit Manipulation, Math, String, Two Pointers
- **LeetCode Link:** [Binary Gap](https://leetcode.com/problems/binary-gap/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a positive integer `n`, find and return the **longest distance** between any two adjacent `1`'s in the binary representation of `n`. If there are no two adjacent `1`'s, return `0`.

Two `1`'s are adjacent if there are only `0`'s separating them (possibly no `0`'s). The distance between two `1`'s is the absolute difference between their bit positions.

**Example 1:**
Input: `n = 22`
Output: `2`
Explanation: `22` in binary is `10110`.
The first adjacent pair of `1`'s is `10110` (distance: 2).
The second adjacent pair of `1`'s is `10110` (distance: 1).
The maximum distance is 2.

**Example 2:**
Input: `n = 8`
Output: `0`
Explanation: `8` in binary is `1000`. There are not enough `1`'s to form a pair.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem requires measuring the positional difference between set bits. This can be conceptualized as finding the maximum difference between consecutive indices of `1`s in an array or string.

### 1. String Representation (Linearization)
Instead of tracking bit positions on the fly, the algorithm first linearizes the binary representation into a `std::string`.
* We repeatedly extract the Least Significant Bit (LSB) using `n & 1`.
* We logically shift `n` to the right (`n >>= 1`).
* **Mathematical Property:** This generates the binary string in *reverse* order (from LSB to MSB). However, spatial distance is symmetric: $|i - j| = |j - i|$. Therefore, reversing the sequence of bits does not alter the distances between the `1`s.



### 2. Two Pointers Measurement
Once the string is constructed, we apply a state-machine or Two Pointers logic:
* **Left Pointer (`l`):** Anchors the position of the *previously* seen `1`.
* **Right Pointer (`r`):** Scans forward to find the *next* `1`.
* When `r` finds a `1`, we compute the gap: `r - l`, update the global maximum `longestDist`, and then advance the anchor: `l = r`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the integer $n$ have the binary representation sequence $S = s_0, s_1, \dots, s_k$ where $k = \lfloor \log_2 n \rfloor$.
Let $B$ be the ordered set of indices $i$ such that $s_i = 1$.
If $|B| < 2$, the result is $0$.
Otherwise, the objective function to maximize is the discrete derivative (difference) of the sequence $B$:

$$
\text{MaxGap} = \max_{1 \le j < |B|} (B_{j} - B_{j-1})
$$

### 2. Time Complexity Analysis

The algorithm operates in two sequential phases:
1.  **Bit Extraction:** The `while(n)` loop runs exactly as many times as there are bits in $n$. The number of bits is bounded by $\lceil \log_2 n \rceil$.
2.  **String Traversal:** The `while` loops traverse the constructed string exactly once, with `i` strictly increasing.

Let $N = \log_2 n$ be the bit-length of the input integer.

$$
T(N) = \Theta(N) + \Theta(N) = \Theta(N)
$$

$$
T(n) \in O(\log n)
$$

### 3. Space Complexity Analysis

We allocate a string `binRep` to store the binary representation. The length of this string is exactly the bit-length of $n$.

$$
S(N) = \Theta(N)
$$

$$
S(n) \in O(\log n)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int binaryGap(int n) {
        string binRep = "";
        while(n){
            char x = (n & 1) + '0';
            binRep+=x;
            n>>=1;
        }
        int l = 0, r = 0;
        int longestDist = 0;
        cout<<binRep<<endl;
        int repLen = binRep.length();
        int i = 0;
        while(i < repLen) {
                if (binRep[i] == '1') {
                    l = i;
                    break;
                }
                i++;
        }
        for(i = i + 1; i<repLen; i++) {
            while(i < repLen) {
                if (binRep[i] == '1') {
                    r = i;
                    break;
                }
                i++;
            }
            longestDist = max(longestDist, r-l);
            l = r;
        }
        return longestDist;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).