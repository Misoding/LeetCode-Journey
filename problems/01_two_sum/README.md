# 1. Two Sum

- **Difficulty:** Easy
- **Topics:** Array, Hash Table
- **LeetCode Link:** [Two Sum Problem](https://leetcode.com/problems/two-sum/)
- **Author:** [Mihail Iazinschi (LinkedIn)](https://www.linkedin.com/in/misoding)

---

## 📝 Problem Statement

Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

You may assume that each input would have **exactly one solution**, and you may not use the same element twice. You can return the answer in any order.

---

## 💡 Algorithmic Analysis

This document explores the evolution of the solution from a naïve quadratic approach to an optimized linear time complexity solution using Hash Maps.

### Method 1: Brute Force Approach

The most straightforward way to solve this problem is to check every possible pair of numbers in the array to see if they add up to the `target`.

#### Mathematical Derivation
We iterate through all unique pairs $(i, j)$ with $0 \le i < j \le n-1$.
To determine the exact time complexity, we calculate the number of operations based on the nested loops:

$$ T(n) = \sum_{i=0}^{n-2} \sum_{j=i+1}^{n-1} 1 $$

Expanding this sum, we get an arithmetic progression:
$$ T(n) = (n-1) + (n-2) + \dots + 1 = \frac{n(n-1)}{2} $$

Since the dominant term is $n^2$, the time complexity is **quadratic**.

- **Time Complexity:** $O(n^2)$
- **Space Complexity:** $O(1)$

#### Implementation (C++)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> solution(2);
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    solution[0] = i;
                    solution[1] = j;
                }
            }
        }
        return solution;
    }
};
```

---

### Method 2: Two-Pass Hash Map (Optimized)

To reduce the time complexity strictly below $O(n^2)$, we need to trade space for time. We can utilize a **Hash Map** to store the indices of the elements we have processed or need to look up.
The mathematical condition $a_i + a_j = T$ can be rewritten as finding a complement $c_i$ such that:
$$ c_i = T - a_i $$

The algorithm proceeds in two phases:
1.  **Mapping Phase:** Store each number and its index in a Hash Table.
2.  **Search Phase:** For each element, calculate its complement and check if it exists in the map (ensuring indices are distinct).

#### Complexity Analysis
Let $n$ be the number of elements.
1.  **Build Phase:** Iterates $n$ times. Insertion into `unordered_map` is $O(1)$ on average. $\rightarrow T_1(n) \approx n$.
2.  **Search Phase:** Iterates $n$ times. Lookup is $O(1)$. $\rightarrow T_2(n) \approx n$.

Total Time Complexity:
$$ T(n) = T_1(n) + T_2(n) \in \Theta(n) $$

- **Time Complexity:** $O(n)$
- **Space Complexity:** $O(n)$ (auxiliary space for the map).

#### Implementation (C++)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> solution(2);
        unordered_map<int,int> initialNumbers;
        int n = nums.size();
        int mapIndex;
        
        // Phase 1: Build the Hash Map
        for (int i = 0; i < n; i++) {
            initialNumbers[nums[i]] = i;
        }
        
        // Phase 2: Search for the complement
        for (int i = 0; i < n; i++) {
            nums[i] = target - nums[i]; 
            
            if (initialNumbers.contains(nums[i])) {
                mapIndex = initialNumbers[nums[i]];
                if (i != mapIndex){
                    solution[0] = i;
                    solution[1] = mapIndex;
                }
            }
        }
        return solution;
    }
};
```

---

### 🔗 Connect
If you found this analysis helpful, feel free to connect:
- [**LinkedIn Profile**](https://www.linkedin.com/in/Misoding)
- [**Main Repository**](../../README.md)