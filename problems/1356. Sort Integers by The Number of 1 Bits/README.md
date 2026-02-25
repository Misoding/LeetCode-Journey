# Day 35: Sort Integers by The Number of 1 Bits

- **Difficulty:** Easy
- **Topics:** Array, Bit Manipulation, Sorting, Bucket Sort
- **LeetCode Link:** [Sort Integers by The Number of 1 Bits](https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an integer array `arr`. Sort the integers in the array in ascending order by the number of `1`'s in their binary representation. In case two or more integers have the same number of `1`'s, you have to sort them in ascending order of their integer values.

Return the array after sorting it.

**Example 1:**
Input: `arr = [0,1,2,3,4,5,6,7,8]`
Output: `[0,1,2,4,8,3,5,6,7]`
Explanation: 
* `[0]` is the only integer with 0 bits.
* `[1,2,4,8]` all have 1 bit.
* `[3,5,6]` have 2 bits.
* `[7]` has 3 bits.
Sorted array: `[0,1,2,4,8,3,5,6,7]`.

---

## 🏗️ Deep-Dive Implementation Strategy

Instead of using a custom comparator function for `std::sort` which recalculates bits multiple times, the implemented approach uses a **Bucket Sort** strategy combined with individual bucket sorting.

### 1. The Bucket Strategy
We map the Hamming weight (number of set bits) of each number to a specific bucket. Since integers are 32-bit, there are at most 33 possible buckets (0 to 32).
1.  **Count Bits:** For each number $x \in arr$, calculate its set bits using bitwise AND (`x & 1`) and bitwise right shift (`x >>= 1`).
2.  **Group:** Push the number into `bit_map[bits_count]`. This naturally partitions the array by the primary sorting condition.

### 2. Intra-Bucket Sorting
Once all numbers are distributed into their respective buckets based on their bit count, we process the buckets in ascending order (from 0 to 31).
* If a bucket has more than one element, these elements have the same number of `1`s.
* We apply standard `std::sort` on the bucket to satisfy the secondary sorting condition (ascending numerical value).
* Finally, we append the sorted bucket elements to our result vector.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $H(x)$ be the Hamming weight function:

$$
H(x) = \sum_{k=0}^{\lfloor \log_2 x \rfloor} \left( \lfloor \frac{x}{2^k} \rfloor \bmod 2 \right)
$$

The problem asks us to define a strict weak ordering relation $\prec$ such that for any $a, b \in arr$:

$$
a \prec b \iff (H(a) < H(b)) \lor (H(a) = H(b) \land a < b)
$$

The bucket sort isolates the primary condition by partitioning the set $A$ into disjoint subsets $B_k$:

$$
B_k = \{ x \in A \mid H(x) = k \}
$$

### 2. Time Complexity Analysis

Let $N$ be the length of the array, and let $N_k = |B_k|$ be the size of the $k$-th bucket.
1.  **Bit Counting Phase:** For each of the $N$ numbers, we shift at most $\lceil \log_2(\max(A)) \rceil$ times (which is $\le 14$ given constraints $A[i] \le 10^4$). This takes $\Theta(N)$.
2.  **Sorting Phase:** We sort each bucket $B_k$. The cost to sort bucket $k$ is $O(N_k \log N_k)$.
    The total sorting time is:
    
$$
T_{sort}(N) = \sum_{k=0}^{32} O(N_k \log N_k)
$$

Since $\sum N_k = N$, the worst-case time complexity (when all numbers have the same amount of bits) is $O(N \log N)$.

**Total Time Complexity:**

$$
T(N) = \Theta(N) + O(N \log N) = O(N \log N)
$$

### 3. Space Complexity Analysis

We allocate memory for the `unordered_map` (32 keys) and vectors storing a total of $N$ elements, plus the $N$-element result vector.

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
    vector<int> sortByBits(vector<int>& arr) {
        unordered_map<int, vector<int>> bit_map;
        for(int i = 0; i < 32; i++) {
            bit_map[i] = vector<int>(0);
        }
        for(int i = 0; i<arr.size();i++){
            int c = 0;
            int tmp = arr[i];
            while(tmp) {
                c += (tmp & 1);
                tmp >>=1;
            }
            bit_map[c].push_back(arr[i]);
        }
        vector<int> res;
        for(int i = 0; i < 32; i++) {
            sort(bit_map[i].begin(), bit_map[i].end());
            for(int j = 0; j < bit_map[i].size();j++) {
                res.push_back(bit_map[i][j]);
            }
        }
        return res;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).