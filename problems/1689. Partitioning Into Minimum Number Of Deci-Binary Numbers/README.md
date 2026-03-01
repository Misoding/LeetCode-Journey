# Day 39: Partitioning Into Minimum Number Of Deci-Binary Numbers

- **Difficulty:** Medium
- **Topics:** String, Math, Greedy
- **LeetCode Link:** [Partitioning Into Minimum Number Of Deci-Binary Numbers](https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

A decimal number is called **deci-binary** if each of its digits is either `0` or `1` without any leading zeros. For example, `101` and `1100` are deci-binary, while `112` and `3001` are not.

Given a string `n` that represents a positive decimal integer, return the **minimum** number of positive deci-binary numbers needed so that they sum up to `n`.

**Example 1:**
Input: `n = "32"`
Output: `3`
Explanation: `10 + 11 + 11 = 32`

**Example 2:**
Input: `n = "82734"`
Output: `8`

---

## 🏗️ Deep-Dive Implementation Strategy

### 1. Core Logic (The LeetCode Solution)
The deduced logic is perfectly correct 🎯. If we decompose the values of each position vertically, the problem transforms into a matrix addition. 
A digit $d$ at a specific position requires exactly $d$ instances of `1` in that same position across the deci-binary addends. Therefore, the minimum number of deci-binary numbers required to form the string `n` is strictly equal to the **maximum digit** present in `n`.

### 2. Solution Architecture 🛠️ (Extended: Generating the Numbers)
To algorithmically generate these numbers without expensive memory operations, we allocate a vector of strings with a size equal to the maximum digit found.
* **Size Determination:** Find the maximum digit $M$ in the string $n$ (e.g., for `2432`, $M = 4$). This is the exact number of deci-binary elements needed.
* **Matrix Generation:** Iterate to construct each of the $M$ numbers. For the $i$-th deci-binary number ($i$ goes from $0$ to $M-1$), evaluate each character of the original string.
* **Bit Condition:** If the current digit is strictly greater than the index $i$, insert the character `1`. Otherwise, insert `0`.
* **Leading Zero Detection (LZD):** To respect the deci-binary format constraint, use a boolean flag to ignore initial zeros during construction, avoiding memory reallocations or subsequent `.trim()` functions.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the string representation of the number be $S = d_k d_{k-1} \dots d_1 d_0$.
We need to find a set of deci-binary numbers $B_1, B_2, \dots, B_m$ such that $\sum B_j = S$.
Since the maximum digit in any position $p$ is $\max(S)$, and a deci-binary number can contribute at most $1$ to position $p$, we minimally require exactly $\max(S)$ deci-binary numbers.

### 2. Time Complexity Analysis
* **Finding Max Digit:** Scanning the string of length $N$ takes $\Theta(N)$.
* **Generation Phase:** We iterate $M$ times over the string of length $N$. 
Because $M \le 9$ (base-10 constraint), the constant factor is negligible.

$$
T(N) = \Theta(N \times M) \approx \Theta(N)
$$

### 3. Space Complexity Analysis
* **Finding Max Digit:** $O(1)$ auxiliary space.
* **Generation Phase:** Allocating a vector of $M$ strings, each of maximum length $N$, on the heap 🚀.

$$
S(N) = \Theta(N \times M) \approx \Theta(N)
$$

---

## 💻 Implementation (C++)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 1. LeetCode Solution: Just return the max digit
    int minPartitions(string n) {
        int max_num = 0;
        for(int i = 0; i < n.length(); i++){
            max_num = max(n[i] - '0', max_num);
        }
        return max_num;
    }

    // 2. Proper Concept: Actually generating the deci-binary partitions
    vector<string> generateDeciBinaries(string n) {
        int max_digit = 0;
        for (char c : n) {
            max_digit = max(max_digit, c - '0');
        }
        
        vector<string> result(max_digit, "");
        
        // Effective construction of deci-binary numbers
        for (int i = 0; i < max_digit; ++i) {
            bool leading_zero = true;
            
            for (char c : n) {
                int digit = c - '0';
                
                if (digit > i) {
                    result[i] += '1';
                    leading_zero = false; // First '1' cancels the leading zero state
                } else if (!leading_zero) {
                    // Add '0' only if we have already encountered a previous '1'
                    result[i] += '0';
                }
            }
        }
        
        return result;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).