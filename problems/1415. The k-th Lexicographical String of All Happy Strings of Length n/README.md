# Day 50: Minimum Number of Seconds to Make Mountain Height Zero

- **Difficulty:** Medium
- **Topics:** Array, Math, Binary Search, Priority Queue (Heap), Greedy
- **LeetCode Link:** [Minimum Number of Seconds to Make Mountain Height Zero](https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an integer `mountainHeight` denoting the height of a mountain. You are also given an integer array `workerTimes` representing the base time for different workers to reduce the mountain's height.

If worker $i$ reduces the mountain's height by $x$, it takes them `workerTimes[i] * x` seconds to reduce the $x$-th unit of height. The workers work in parallel.

Return the **minimum** number of seconds required to reduce the `mountainHeight` to 0.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem models parallel execution where the marginal cost of a task increases linearly for each specific worker. We must assign exactly `mountainHeight` units of work across all workers such that the absolute maximum cumulative time spent by any single worker is minimized.

### 1. The Min-Heap (Greedy Scheduler)
We define a custom data structure `hardworker` that holds three states for each worker:
1.  `workerTime`: The base multiplier (constant).
2.  `idx`: The next unit of mountain this worker will tackle (starts at 1).
3.  `actionCost`: The **absolute predicted timestamp** when this worker would finish their `idx`-th unit of work.

We maintain a Priority Queue (Min-Heap) ordered by `actionCost` in ascending order. The heap always surfaces the worker who can complete their next assigned unit of mountain at the earliest possible absolute time.

### 2. Arithmetic Progression Cumulative Cost
If a worker with base time $T$ reduces the mountain by $k$ units sequentially, the time taken for the $k$-th unit is $T \cdot k$.
The *total cumulative time* to process $k$ units is the sum of an arithmetic progression:
$T \cdot 1 + T \cdot 2 + \dots + T \cdot k = T \cdot \frac{k(k+1)}{2}$.

When a worker is popped from the heap, they are definitively assigned that unit of work. We update the global `maxTime` to accommodate this completion timestamp, increment their `idx`, calculate their *next* predicted completion timestamp using the arithmetic progression formula, and push them back into the heap.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $W$ be the set of workers. Let $x_i$ be the number of units assigned to worker $i \in W$. We must satisfy the constraint:

$$
\sum_{i \in W} x_i = H \quad \text{(where } H \text{ is the mountain height)}
$$

We want to minimize the objective function (makespan):

$$
\text{Total Time} = \max_{i \in W} \left( T_i \cdot \frac{x_i (x_i + 1)}{2} \right)
$$

The Greedy algorithm strictly minimizes this max-bound at every step by simulating the allocations dynamically over the absolute timeline.

### 2. Time Complexity Analysis

Let $H$ be `mountainHeight` and $W$ be the size of `workerTimes`.
1.  **Heap Initialization:** Inserting all $W$ workers into the priority queue takes $O(W \log W)$.
2.  **Greedy Allocation:** The `while` loop runs exactly $H$ times. In each iteration, we pop from and push to the heap. A heap operation takes $O(\log W)$.

$$
T(H, W) = \Theta(W \log W) + \Theta(H \log W) = \Theta((H + W) \log W)
$$

*(Note: For extremely large $H$, a Binary Search on the answer space yields $O(W \log(\text{MaxTime}))$, but the Min-Heap approach perfectly simulates the greedy logic and easily passes within standard limits if $H$ is bounded reasonably).*

### 3. Space Complexity Analysis

The Priority Queue stores exactly one `hardworker` state per element in `workerTimes`.

$$
S(W) = \Theta(W)
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