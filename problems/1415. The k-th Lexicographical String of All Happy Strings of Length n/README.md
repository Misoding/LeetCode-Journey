# Day 51: The k-th Lexicographical String of All Happy Strings of Length n

- **Difficulty:** Medium
- **Topics:** String, Backtracking
- **LeetCode Link:** [The k-th Lexicographical String of All Happy Strings of Length n](https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

A **happy string** is a string that:
* Consists only of letters of the set `['a', 'b', 'c']`.
* $s[i] \neq s[i + 1]$ for all values of $i$ from 1 to $s.length - 1$ (1-indexed).

Given two integers `n` and `k`, consider a list of all happy strings of length `n` sorted in lexicographical order.
Return the $k^{th}$ string of this list or return an empty string if there are less than `k` happy strings of length `n`.

**Example:**
Input: `n = 3, k = 9`
Output: `"cab"`
Explanation: There are 12 different happy strings of length 3. The 9th string is `"cab"`.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem requires exploring a constrained combinatorial space. A Depth-First Search (DFS) backtracking algorithm perfectly models this requirement.

### 1. State Space Tree Generation
The algorithm constructs a virtual decision tree of depth $N$:
1.  **Root Node (Depth 0):** Has 3 branching choices (`'a'`, `'b'`, `'c'`).
2.  **Child Nodes (Depth > 0):** Each node has exactly 2 branching choices, as the character must differ from its immediate parent (the preceding character in the string).
3.  **Lexicographical Ordering:** By strictly iterating the choices in ASCII ascending order (`'a'` $\to$ `'c'`), the DFS naturally traverses the tree in lexicographical order. The leaves of this tree represent the complete happy strings.

### 2. Backtracking Pruning
The condition `if (pos > 0 && i == pair[pos-1]) continue;` acts as the pruning mechanism. It prevents the DFS from ever entering an invalid state, ensuring that $100\%$ of the strings reaching the base case `pos >= n` are valid happy strings. 

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model (Combinatorics)

Let $S_n$ be the set of all happy strings of length $n$.
The cardinality of this set is derived from the branching factor. The first character has 3 possibilities. Every subsequent character has 2 possibilities (excluding the immediate predecessor).

$$
|S_n| = 3 \cdot 2^{n-1}
$$

If $k > 3 \cdot 2^{n-1}$, the requested string falls outside the valid combinatorial space, returning $\emptyset$.

### 2. Time Complexity Analysis

The DFS explores exactly the number of valid paths. For each leaf node reached, a string of length $N$ is deep-copied into the `pairs` vector.
The total number of states visited is bounded by the cardinality of $S_n$.

$$
T(N) = \Theta(|S_n| \cdot N) = \Theta(N \cdot 3 \cdot 2^{n-1})
$$

Given $N \le 10$, the maximum operations approximate $10 \cdot 3 \cdot 512 = 15,360$, executing in a fraction of a millisecond.

$$
T(N) \in O(N \cdot 2^N)
$$

### 3. Space Complexity Analysis

The auxiliary space is consumed by:
1.  **The Call Stack:** Maximum recursion depth is exactly $N$.
2.  **The String Storage:** The `pairs` vector holds all valid strings. Total storage requires $N$ bytes per string for $3 \cdot 2^{n-1}$ strings.

$$
S(N) = \Theta(N) + \Theta(N \cdot 3 \cdot 2^{n-1}) = \Theta(N \cdot 2^N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    void generateStrings(const int& n, int pos,string& pair, vector<string>& pairs) {
        if (pos >= n) {
            pairs.push_back(pair);
            return;
        }
        for(int i = 'a'; i <= 'c'; i++) {
            if (pos > 0 && i == pair[pos-1]){
                continue;
            }
            pair[pos] = i;
            generateStrings(n,pos+1, pair, pairs);
        }
        return;
    }
    string getHappyString(int n, int k) {
        vector<string> pairs;
        string dummy(n, 'a');
        generateStrings(n,0, dummy, pairs);
        if(pairs.size() >= k) {
            return pairs[k-1];
        }
        return "";

    }
};
```

---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).