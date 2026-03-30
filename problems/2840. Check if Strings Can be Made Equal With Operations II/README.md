# Day 61: Check if Strings Can be Made Equal With Operations II

- **Difficulty:** Medium
- **Topics:** String, Hash Table
- **LeetCode Link:** [Check if Strings Can be Made Equal With Operations II](https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given two strings `s1` and `s2`, both of length `n`, consisting of lowercase English letters.

You can apply the following operation on any of the two strings any number of times:
* Choose any two indices `i` and `j` such that `i < j` and the difference `j - i` is **even**, then **swap** the two characters at those indices in the string.

Return `true` if you can make the strings `s1` and `s2` equal, and `false` otherwise.

---

## 🏗️ Deep-Dive Implementation Strategy

The operational constraint `j - i` being even implies that characters can only traverse across indices of the same parity. 
* A character at an **even** index can only jump to other **even** indices.
* A character at an **odd** index can only jump to other **odd** indices.

### 1. Parity Invariance Principle
Because the parity boundaries can never be crossed, the exact positioning of the characters does not matter. The two strings can be made equal if and only if they possess the exact same multiset of characters at their even indices, and the exact same multiset of characters at their odd indices.

### 2. Frequency Arrays (Histogram)
We maintain four frequency arrays (histograms) to count the character occurrences:
* `s1` even indices character count
* `s1` odd indices character count
* `s2` even indices character count
* `s2` odd indices character count

By scanning the strings in $O(N)$ time, we populate these arrays. Finally, we perform an $O(1)$ validation pass across the arrays to ensure perfect structural parity.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let string $S$ be partitioned into two disjoint subsets based on index parity:
$S_{even} = \{S[2k] \mid 0 \le 2k < N\}$
$S_{odd} = \{S[2k+1] \mid 0 \le 2k+1 < N\}$

The allowed permutation operation generates the symmetric group over the indices of $S_{even}$ and independently over $S_{odd}$. Therefore, $S1$ can be transformed into $S2$ if and only if there exists a bijection between their respective sets, implying multiset equality:
$$
S1_{even} \equiv S2_{even} \quad \land \quad S1_{odd} \equiv S2_{odd}
$$

### 2. Time Complexity Analysis

Let $N$ be the length of the strings. Populating the frequency vectors requires a single linear pass traversing both strings, taking $\Theta(N)$ operations. The subsequent equality check iterates over a fixed alphabet size $\Sigma$ (bounded by the allocated 135, or theoretically 26), which operates in $\Theta(1)$ constant time.

$$
T(N) = \Theta(N) + \Theta(\Sigma) = \Theta(N)
$$

### 3. Space Complexity Analysis

The auxiliary spatial requirement is strictly isolated to the four static frequency vectors tracking the character spectrum. Because their dimension relies strictly on the character encoding set size $\Sigma$ and is independent of $N$, the space complexity is strictly bounded.

$$
S_{aux}(N) = \Theta(\Sigma) \implies \Theta(1)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    bool checkStrings(string s1, string s2) {
        if (s1.length() != s2.length()) return false;
        vector<int> s1_count_even(135, 0);
        vector<int> s1_count_odd(135, 0);
        vector<int> s2_count_even(135, 0);
       vector<int> s2_count_odd(135, 0);
        for(int i = 0; i<s1.length();i++) {
            if (i % 2) s1_count_odd[s1[i]-'a']++;
            else s1_count_even[s1[i] - 'a']++;
        }
        for(int i = 0; i<s2.length();i++) {
            if (i % 2) s2_count_odd[s2[i]-'a']++;
            else s2_count_even[s2[i] - 'a']++;
        }
        for(int i = 0; i < 135; i++) {
            if (s1_count_odd[i] != s2_count_odd[i] || s1_count_even[i] != s2_count_even[i]) return false;
        }
        return true;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).   