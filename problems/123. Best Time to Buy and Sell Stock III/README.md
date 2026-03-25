# Day 59: Best Time to Buy and Sell Stock III

- **Difficulty:** Hard
- **Topics:** Array, Dynamic Programming
- **LeetCode Link:** [Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an array `prices` where `prices[i]` is the price of a given stock on the $i^{th}$ day.

Find the maximum profit you can achieve. You may complete **at most two transactions**.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

**Example 1:**
Input: `prices = [3,3,5,0,0,3,1,4]`
Output: `6`
Explanation: 
* Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3 - 0 = 3.
* Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4 - 1 = 3.

---

## 🏗️ Deep-Dive Implementation Strategy

The constraint of "at most two transactions" that cannot overlap naturally divides the timeline into two independent segments split at some arbitrary day $i$. The optimal strategy is to precompute the maximum profit achievable in every possible left segment and every possible right segment.

### 1. Left-to-Right Pass (Prefix Max Profit)
We iterate from day $0$ to $N-1$. We maintain the lowest price seen so far. At each day $i$, the maximum profit we could have made using one transaction ending on or before day $i$ is the maximum of:
1. The max profit achieved up to day $i-1$.
2. The current price minus the lowest historical price.
These values are stored in the `left_sell` array.

### 2. Right-to-Left Pass (Suffix Max Profit)
We iterate backwards from day $N-1$ down to $0$. We maintain the highest peak price seen from the future. At each day $i$, the maximum profit achievable using one transaction starting on or after day $i$ is the maximum of:
1. The max profit achievable from day $i+1$.
2. The highest future peak price minus the current price.
These values are stored in the `right_sell` array.

### 3. State Aggregation
With both arrays populated, we perform a final linear scan. For every day $i$, the sum `left_sell[i] + right_sell[i]` represents the absolute maximum profit if we split our two transactions exactly around day $i$. We track the global maximum of these sums.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the stock array be $P$ of length $N$.
We define the prefix profit array $L[i]$ (maximum profit in $P[0 \dots i]$):

$$
L[i] = \max(L[i-1], P[i] - \min_{0 \le k \le i} P[k])
$$

We define the suffix profit array $R[i]$ (maximum profit in $P[i \dots N-1]$):

$$
R[i] = \max(R[i+1], \max_{i \le k < N} P[k] - P[i])
$$

The global maximum profit $M$ for at most 2 non-overlapping transactions is:

$$
M = \max_{0 \le i < N} (L[i] + R[i])
$$

### 2. Time Complexity Analysis

The algorithm consists of three distinct, non-nested linear loops over the array of size $N$. 
1. Prefix calculation: $\Theta(N)$
2. Suffix calculation: $\Theta(N)$
3. Aggregation evaluation: $\Theta(N)$

$$
T(N) = \Theta(N) + \Theta(N) + \Theta(N) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The dynamic programming states are isolated into two auxiliary arrays of size $N$ (`left_sell` and `right_sell`).

$$
S_{aux}(N) = \Theta(N) + \Theta(N) = \Theta(N)
$$

$$
S_{aux}(N) \in O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 1) return 0;
        vector<int> left_sell(n,0);
        vector<int> right_sell(n,0);
        int max_price = prices[0];
        for(int i = 1; i < n; i++){
            max_price = min(max_price, prices[i]);
            left_sell[i] = max(left_sell[i-1], -max_price + prices[i]);
        }
        max_price = prices[n-1];
        for(int i = n-2; i>=0; i--) {
            max_price = max(prices[i], max_price);
            right_sell[i] = max(right_sell[i+1], -prices[i] + max_price);
        }
        int max_profit = 0;
        for(int i = 0; i < n; i++) {
            max_profit =  max((right_sell[i]+left_sell[i]), max_profit);
        }
        return max_profit;
    } 
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).