# Day 13: Palindrome Partitioning

- **Difficulty:** Medium
- **Topics:** String, Backtracking, Dynamic Programming, Recursion
- **LeetCode Link:** [Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a string `s`, partition `s` such that **every substring** of the partition is a **palindrome**. Return all possible palindrome partitioning.

**Example:**
Input: `s = "aab"`
Output: `[["a","a","b"],["aa","b"]]`

**Explanation:**
1.  Partition `["a", "a", "b"]`: "a" is a palindrome, "a" is a palindrome, "b" is a palindrome. **Valid**.
2.  Partition `["aa", "b"]`: "aa" is a palindrome, "b" is a palindrome. **Valid**.
3.  Partition `["a", "ab"]`: "ab" is NOT a palindrome. **Invalid**.

---

##  Deep-Dive Implementation Strategy

The problem asks to enumerate *all* valid ways to decompose a string. This nature of the problem suggests an exhaustive search strategy, specifically **Backtracking (Depth-First Search)**.

### 1. The Decision Tree Visualization

We can visualize the string as a sequence of characters where potential "cuts" can be placed between any two characters. For a string of length $N$, there are $N-1$ potential cut positions.

**State Definition:** `solve(begin, currentBuffer)`
* `begin`: The starting position of the substring we are currently considering.
* `currentBuffer`: A list storing the valid palindromes found so far in the current branch.

**Logic Flow:**
From the current `begin`, we try to extend a substring to every possible end position `i` (from `begin` to `N-1`).
* **Candidate:** Substring `s[begin...i]`.
* **Check:** Is this candidate a palindrome?
    * **Yes:** Add to `currentBuffer` and **recurse** for `i + 1`.
    * **No:** Prune this branch immediately (Backtracking).

#### Example Trace: `s = "aab"`

```text
Root: solve(0)
├── Cut after 'a' (index 0): "a" (Valid) -> recurse(1)
│   ├── Cut after 'a' (index 1): "a" (Valid) -> recurse(2)
│   │   ├── Cut after 'b' (index 2): "b" (Valid) -> recurse(3)
│   │   │   └── Base Case Reached (3 == len). Add ["a", "a", "b"]
│   │   └── (End of loop)
│   ├── Cut after 'ab' (index 1..2): "ab" (Invalid) -> Prune
│   └── (End of loop)
├── Cut after 'aa' (index 0..1): "aa" (Valid) -> recurse(2)
│   ├── Cut after 'b' (index 2): "b" (Valid) -> recurse(3)
│   │   └── Base Case Reached. Add ["aa", "b"]
│   └── (End of loop)
└── Cut after 'aab' (index 0..2): "aab" (Invalid) -> Prune
```

### 2. Palindrome Verification
To verify if a substring is a palindrome, we use a helper function that compares characters from the start and end moving inwards. While a naive check takes $O(N)$, this can be optimized using Dynamic Programming (pre-computation), though for smaller constraints, the iterative check is sufficient.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model (State Space)

Let $N$ be the length of string $s$.
Between every two characters, we have a binary choice: either place a cut or don't.
There are $N-1$ such positions.
Thus, the total number of possible partitions is bounded by $2^{N-1}$.

However, we are constrained by the palindrome property. We only explore branches where the prefix is a palindrome.

### 2. Time Complexity Derivation

The worst-case scenario occurs when **every** substring is a palindrome (e.g., `s = "aaaa"`).
In this case, the recursion tree explores all $2^{N-1}$ partitions.

For each valid partition found (leaf node in the recursion tree), we perform:
1.  **Palindrome Check:** In the worst case, checking all substrings in a partition takes roughly $O(N)$.
2.  **Result Construction:** Copying the substrings into the result vector takes $O(N)$.

Thus, the total time complexity is proportional to the number of partitions multiplied by the length of the string:

$$
T(N) \approx \sum_{k=0}^{N-1} \binom{N}{k} \cdot N = O(N \cdot 2^N)
$$

### 3. Space Complexity Analysis

We analyze the memory usage:

1.  **Recursion Stack:** The maximum depth of the recursion tree is $N$ (when we cut after every character).
    $$ S_{stack} = O(N) $$

2.  **Current Buffer:** The temporary vector storing the current path stores at most $N$ strings.
    $$ S_{buffer} = O(N) $$

3.  **Output Storage:** Storing all solutions. In the worst case, this can be exponential, but we usually exclude output storage from auxiliary space analysis.

**Total Auxiliary Space:**
$$
S(N) \in O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    bool palindromeCheck(string s){
        int i = 0;
        int n = s.length();
        while(i < n && s[i] == s[n-i-1]){
            i++;
        }
        if (i < n) return false;
        return true;
    }
    void solvePalindromes(int begin, string s, vector<string> &currentBuffer, vector<vector<string>> &res) {
        if (begin == s.length()){
            res.push_back(currentBuffer);
            return;
        }
        for(int i = begin; i < s.length(); i++) {
            string currentPalindrome = s.substr(begin, i-begin+1);
            if (palindromeCheck(currentPalindrome)) {
                currentBuffer.push_back(currentPalindrome);
                solvePalindromes(i+1, s, currentBuffer, res);
                currentBuffer.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> tempBuffer;
        solvePalindromes(0, s, tempBuffer, res);
        return res;
    }
};
```

---

### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).