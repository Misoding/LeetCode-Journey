# Day 57: Best Time to Buy and Sell Stock with Cooldown

- **Difficulty:** Medium
- **Topics:** Array, Dynamic Programming
- **LeetCode Link:** [Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an array `prices` where `prices[i]` is the price of a given stock on the $i^{th}$ day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
* After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

**Example 1:**
Input: `prices = [1,2,3,0,2]`
Output: `3`
Explanation: transactions = [buy, sell, cooldown, buy, sell]

---

## 🏗️ Deep-Dive Implementation Strategy

The problem requires tracking absolute maximum profit across a timeline where decisions dictate future constraints. This maps perfectly to a **Dynamic Programming** state machine.

### 1. State Definition
At any given day `i`, the algorithm operates under one of two mutually exclusive states, represented by the boolean `canBuy`:
* **State 1 (`canBuy == 1`):** The agent does not hold any stock. The available actions are to either **buy** today's stock (costing `prices[i]` and transitioning to State 0 for tomorrow) or **skip** (remaining in State 1 for tomorrow).
* **State 2 (`canBuy == 0`):** The agent currently holds a stock. The available actions are to either **sell** today's stock (gaining `prices[i]`) or **skip** (remaining in State 0 for tomorrow).

### 2. The Cooldown Architectural Jump
Instead of explicitly modeling the "cooldown" day as a third state, the restriction is enforced procedurally. When the agent chooses to **sell**, the recursion advances the timeline index from `i` directly to `i + 2`. By mathematically bypassing the next chronological day (`i + 1`), the cooldown constraint is naturally and flawlessly enforced without bloating the state space.

### 3. Memoization
The DFS recursion evaluates the decision tree. Since different paths can lead to the same state on the same day (e.g., buying on day 1 and skipping day 2 vs. skipping day 1 and buying on day 2), the $N \times 2$ `dp` matrix intercepts overlapping subproblems, guaranteeing linear execution.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $DP(i, c)$ denote the maximum profit achievable from day $i$ to the end of the timeline, where $c \in \{0, 1\}$ dictates the capability to buy ($1$) or the obligation to sell ($0$).
The recurrence relation is defined as:

$$
DP(i, c) = \begin{cases} 
0 & \text{if } i \ge N \\
\max(-prices[i] + DP(i+1, 0), \ DP(i+1, 1)) & \text{if } c = 1 \text{ (Buy / Skip)} \\
\max(prices[i] + DP(i+2, 1), \ DP(i+1, 0)) & \text{if } c = 0 \text{ (Sell / Skip)}
\end{cases}
$$

The target configuration is $DP(0, 1)$, initializing the timeline on day 0 with purchasing power.

### 2. Time Complexity Analysis

The state parameters are bounded: $i \in \{0, \dots, N-1\}$ and $c \in \{0, 1\}$.
The memoization table limits evaluation to exactly $2N$ distinct states. Operations resolving each state are localized to $\Theta(1)$ arithmetic comparisons.

$$
T(N) = \Theta(N \times 2) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The auxiliary footprint comprises the $N \times 2$ integer matrix and the DFS call stack. In a scenario with continuous skips, the stack depth scales linearly to $N$.

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
    int solveMemo(vector<int>& prices, vector<vector<int>>& dp, int i, int canBuy) {
        if (i >= prices.size()){
            return 0;
        }
        if (dp[i][canBuy] != -1) {
            return dp[i][canBuy];
        }
        if (canBuy){
            int buyEl = -prices[i] + solveMemo(prices, dp, i+1, 0);
            int skip = solveMemo(prices, dp, i+1, 1);
            dp[i][canBuy] = max(buyEl, skip);
        } else {
            int sellEl = prices[i] + solveMemo(prices, dp, i+2, 1);
            int skip = solveMemo(prices, dp, i+1, 0);
            dp[i][canBuy] = max(sellEl, skip);
        }
        return dp[i][canBuy];
    }
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2, -1));
        return solveMemo(prices, dp, 0, true);
    }
};
```

---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).