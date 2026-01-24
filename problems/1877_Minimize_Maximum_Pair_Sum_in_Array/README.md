# Day 9: Minimize Maximum Pair Sum in Array

- **Difficulty:** Medium
- **Topics:** Greedy, Two Pointers, Sorting
- **LeetCode Link:** [Minimize Maximum Pair Sum in Array](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/)
- **Author:** [Mihail Iazinschi (LinkedIn)](https://www.linkedin.com/in/misoding)

---

## 📝 Problem Statement

The **pair sum** of a pair $(a, b)$ is equal to $a + b$. The **maximum pair sum** is the largest pair sum in a list of pairs.

Given an array `nums` of even length $n$, pair up the elements of `nums` into $n/2$ pairs such that:
1.  Each element of `nums` is in exactly one pair.
2.  The **maximum pair sum** is **minimized**.

Return the minimized maximum pair sum.

**Example:**
Input: `nums = [3, 5, 2, 3]`
Sorted: `[2, 3, 3, 5]`
Pairs: `(2, 5), (3, 3)` $\rightarrow$ Sums: `7, 6`. Max is 7.
Output: `7`

---

## 🏗️ Deep-Dive Implementation Strategy

To minimize the maximum sum, we intuitively need to "balance" the pairs. A large number combined with another large number will produce a very large sum. To mitigate this, we should pair the largest available numbers with the smallest available numbers.

### 1. The Greedy Strategy
This problem is a classic example of a **Greedy Approach**.
* **Observation:** To keep the maximum sum as low as possible, we must dampen the impact of the largest element $max(S)$ by adding it to the smallest element $min(S)$.
* **Process:**
    1.  **Sort** the array in ascending order.
    2.  Use **Two Pointers**: one at the beginning (`left`) and one at the end (`right`).
    3.  Pair `nums[left]` with `nums[right]`.
    4.  Move pointers inward (`left++`, `right--`) until they meet.

### 2. Execution Visualization

Consider `nums = [3, 5, 4, 2, 4, 6]`.

**Step A: Sorting**
`nums` becomes `[2, 3, 4, 4, 5, 6]`.

**Step B: Two-Pointer Pairing**
* **Pair 1:** `nums[0]` (2) + `nums[5]` (6) = **8**
* **Pair 2:** `nums[1]` (3) + `nums[4]` (5) = **8**
* **Pair 3:** `nums[2]` (4) + `nums[3]` (4) = **8**

**Result:**
The maximum of `{8, 8, 8}` is `8`.

---

## 🔬 Formal Algorithmic Analysis

We formally prove that pairing the smallest element with the largest element minimizes the maximum pair sum.

### 1. Mathematical Proof (Exchange Argument)

Let the sorted array be $x_1 \le x_2 \le \dots \le x_n$.
We propose the optimal pairing is $(x_1, x_n), (x_2, x_{n-1}), \dots$.

Assume there exists a different optimal pairing where $x_1$ is NOT paired with $x_n$, but with some $x_k$ (where $k < n$), and $x_n$ is paired with some $x_j$ (where $j > 1$).
We have two pairs: $(x_1, x_k)$ and $(x_j, x_n)$ with sums $S_1 = x_1 + x_k$ and $S_2 = x_j + x_n$.
The maximum of this configuration is $\max(S_1, S_2)$. Since $x_n$ is the largest element, usually $S_2$ dominates.

If we swap to form the greedy pairs $(x_1, x_n)$ and $(x_j, x_k)$:
* New Sum A: $S'_A = x_1 + x_n$
* New Sum B: $S'_B = x_j + x_k$

Since $x_1 \le x_j$ and $x_k \le x_n$, it can be shown that $\max(S'_A, S'_B) \le \max(S_1, S_2)$.
By repeatedly applying this exchange, we transform any optimal solution into our greedy solution without increasing the maximum pair sum.

### 2. Time Complexity Derivation

The algorithm consists of two main phases:

**A. Sorting Phase:**
We use `std::sort`, which typically implements Introsort (QuickSort + HeapSort + InsertionSort).
$$T_{sort}(N) \in O(N \log N)$$

**B. Pairing Phase:**
We iterate through the array once using two pointers, performing constant time operations (addition, comparison) at each step. The loop runs $N/2$ times.
$$T_{pair}(N) = \frac{N}{2} \cdot O(1) \in O(N)$$

**Total Time Complexity:**
$$T(N) = T_{sort}(N) + T_{pair}(N) \approx O(N \log N)$$

### 3. Space Complexity Analysis

1.  **Sorting:** Depending on the implementation of `std::sort`, it requires $O(\log N)$ stack space for recursion.
2.  **Auxiliary Variables:** We use only `l`, `r`, `maxSum`.

$$S(N) \in O(\log N) \quad (\text{due to sorting stack})$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size()-1;
        int maxSum = 0;
        while (l < r){
            maxSum = max(maxSum, nums[l++] + nums[r--]);
        }
        return maxSum;
    }
};
```
### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).