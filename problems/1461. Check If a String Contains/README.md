# Day 33: Check If a String Contains All Binary Codes of Size K

- **Difficulty:** Medium
- **Topics:** String, Hash Table, Sliding Window
- **LeetCode Link:** [Check If a String Contains All Binary Codes](https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a binary string `s` and an integer `k`, return `true` if every binary code of length `k` is a substring of `s`. Otherwise, return `false`.

**Example 1:**
Input: `s = "00110110", k = 2`
Output: `true`
Explanation: The binary codes of length 2 are `"00"`, `"01"`, `"10"`, and `"11"`. They can be found as substrings at indices 0, 1, 3, and 2 respectively.

**Example 2:**
Input: `s = "0110", k = 1`
Output: `true`
Explanation: The binary codes of length 1 are `"0"` and `"1"`, both exist as substrings.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem asks if all permutations of a binary string of length $k$ exist within $s$. 
By combinatorial mathematics, there are exactly $2^k$ unique binary strings of length $k$. 
Instead of generating all $2^k$ combinations and searching the string for each one (which would be extremely slow), we reverse the logic: we scan the string, collect all unique substrings of length $k$, and count them.



### 1. Sliding Window & Hash Set
We can use a sliding window of fixed size $k$ that moves one character at a time from left to right across the string $s$.
1.  **Extract:** At each step $i$, extract the substring `s.substr(i, k)`.
2.  **Store:** Insert this substring into an `unordered_set`. A set automatically handles duplicates, ensuring only unique binary codes are kept.
3.  **Verify:** After processing the entire string, check if the size of the set is equal to $2^k$. If it is, the string contains all possible binary codes of length $k$.

### 2. Execution Visualization
Input: `s = "00110", k = 2`
Target Unique Codes: $2^2 = 4$.

* **i = 0:** Substring `"00"`. Set = `{"00"}`.
* **i = 1:** Substring `"01"`. Set = `{"00", "01"}`.
* **i = 2:** Substring `"11"`. Set = `{"00", "01", "11"}`.
* **i = 3:** Substring `"10"`. Set = `{"00", "01", "11", "10"}`.

Final Set Size: 4. Since $4 == 2^2$, return `true`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $S$ be the input string of length $N$. We define the set of observed substrings $U$ as:

$$
U = \{ S[i \dots i+k-1] \mid 0 \le i \le N-k \}
$$

The total number of possible binary codes of length $k$ is $2^k$. The condition for the function to return `true` is:

$$
|U| = 2^k
$$

### 2. Time Complexity Analysis

The `for` loop iterates $N - k + 1$ times.
Inside the loop, `s.substr(i, k)` takes $O(k)$ time to extract the string, and inserting it into the `unordered_set` takes $O(k)$ time on average (to hash the string of length $k$).

$$
T(N, k) = \sum_{i=0}^{N-k} \Theta(k) = \Theta((N - k + 1) \cdot k)
$$

Since $k \le 20$ (a small constant boundary), this effectively simplifies to linear time proportional to $N$.

$$
T(N, k) \in O(N \cdot k)
$$

### 3. Space Complexity Analysis

The `unordered_set` stores unique strings of length $k$. The maximum number of elements the set can hold is bounded by both the number of possible unique combinations ($2^k$) and the total number of substrings we can extract ($N - k + 1$).

$$
S(N, k) = \Theta(\min(N - k + 1, 2^k) \cdot k)
$$

$$
S(N, k) \in O(N \cdot k)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_set<string> subStrings;
        for(int i = 0; i + k <= s.length(); i++){
            subStrings.insert(s.substr(i, k));
        }
        if(subStrings.size() == pow(2,k)) {
            return true;
        }
        return false;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).