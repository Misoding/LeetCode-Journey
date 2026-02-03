# Day 19: Car Fleet

- **Difficulty:** Medium
- **Topics:** Array, Stack, Sorting, Monotonic Stack
- **LeetCode Link:** [Car Fleet](https://leetcode.com/problems/car-fleet/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

There are `n` cars traveling to the same destination (`target`). You are given two arrays: `position` (starting mile) and `speed` (miles per hour).

**Rules of the Road:**
1.  A car cannot pass another car ahead of it.
2.  If a faster car catches up to a slower car ahead, they form a **car fleet** and travel at the speed of the slower car.
3.  A car fleet is defined by its lead car.

Return the **number of car fleets** that will arrive at the destination.

**Example:**
Input: `target = 12`, `position = [10, 8, 0, 5, 3]`, `speed = [2, 4, 1, 1, 3]`
Output: `3`

---

## 🏗️ Deep-Dive Implementation Strategy

The core difficulty lies in the fact that cars interact only with those *ahead* of them. This suggests we should process cars starting from the one closest to the target.

### 1. Mathematical Modeling (Time to Target)
For any car $i$, the time it would take to reach the target *if strictly unobstructed* is:
$$ t_i = \frac{\text{target} - \text{position}_i}{\text{speed}_i} $$



### 2. The Logic: Processing Backwards
We sort the cars by their starting `position` in **descending order** (closest to target first).
Let's analyze two adjacent cars after sorting: $C_{ahead}$ and $C_{behind}$.
* If $t_{behind} \le t_{ahead}$: The car behind arrives sooner (is faster), meaning it will catch up to the car ahead. Since it cannot pass, it joins the fleet of $C_{ahead}$. It essentially "vanishes" into the fleet.
* If $t_{behind} > t_{ahead}$: The car behind arrives later (is slower). It will never catch up to $C_{ahead}$ before the target. It becomes the leader of a **new fleet**.

### 3. Execution Visualization
Input: `target = 12`, Pairs: `[(10, 2), (8, 4), (0, 1), (5, 1), (3, 3)]`

**Step 1: Sort by Position (Descending)**
1.  Pos 10, Spd 2 $\to t = (12-10)/2 = 1.0$
2.  Pos 8, Spd 4 $\to t = (12-8)/4 = 1.0$
3.  Pos 5, Spd 1 $\to t = (12-5)/1 = 7.0$
4.  Pos 3, Spd 3 $\to t = (12-3)/3 = 3.0$
5.  Pos 0, Spd 1 $\to t = (12-0)/1 = 12.0$

**Step 2: Stack Processing**
* **Car 1 (Pos 10, t=1.0):** Stack empty. Push `1.0`. Fleet count: 1. (Leader)
* **Car 2 (Pos 8, t=1.0):** $t(1.0) \le \text{StackTop}(1.0)$. Catches up. Ignored (joins fleet).
* **Car 3 (Pos 5, t=7.0):** $t(7.0) > \text{StackTop}(1.0)$. Too slow to catch up. New Fleet. Push `7.0`. Fleet count: 2.
* **Car 4 (Pos 3, t=3.0):** $t(3.0) \le \text{StackTop}(7.0)$. Catches up to the car at Pos 5. Ignored.
* **Car 5 (Pos 0, t=12.0):** $t(12.0) > \text{StackTop}(7.0)$. Too slow. New Fleet. Push `12.0`. Fleet count: 3.

**Result:** Stack size is 3.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let sorted cars be $c_1, c_2, \dots, c_n$ where $position(c_1) > position(c_2) > \dots$.
We define a fleet leader sequence $L$.
$c_i$ is a new fleet leader if and only if:
$$ \text{time}(c_i) > \text{time}(\text{latest\_leader}) $$
Otherwise, $c_i$ merges into the existing fleet.

### 2. Time Complexity
* **Sorting:** We sort $N$ cars based on position.
    $$ T_{sort} = O(N \log N) $$
* **Linear Scan:** We iterate through the sorted list once. Stack operations are $O(1)$.
    $$ T_{scan} = O(N) $$

**Total Time Complexity:**
$$ T(N) \in O(N \log N) $$

### 3. Space Complexity
* **Storage:** We store pairs of (position, speed) and a stack for time values.
    $$ S(N) = O(N) $$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int,int>> cars(n);
        for(int i = 0; i < n; i++) {
            cars[i] = {position[i], speed[i]};
        }
        sort(cars.rbegin(), cars.rend());
        stack<double> fleets;
        
        for(int i = 0; i < n; i++){
            double time = (double)(target - cars[i].first) / cars[i].second;
            if (fleets.empty()) {
                fleets.push(time);
            } 
            else if (time > fleets.top()) {
                fleets.push(time);
            }
        }
        return fleets.size();
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).