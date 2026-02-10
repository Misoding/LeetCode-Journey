# Day 26: Linked List Cycle

- **Difficulty:** Easy
- **Topics:** Linked List, Two Pointers, Floyd's Cycle-Finding Algorithm
- **LeetCode Link:** [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given `head`, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the `next` pointer.

Return `true` if there is a cycle in the linked list. Otherwise, return `false`.

**Example 1:**
Input: `head = [3,2,0,-4]`, `pos = 1` (tail connects to node index 1)
Output: `true`

**Example 2:**
Input: `head = [1]`, `pos = -1`
Output: `false`

---

## 🏗️ Deep-Dive Implementation Strategy

Using a Hash Set to store visited nodes would take $O(N)$ memory. To solve this in $O(1)$ memory, we use **Floyd's Cycle-Finding Algorithm**.

### 1. The Tortoise and Hare Analogy
Imagine two runners on a track:
* **Tortoise (Slow):** Moves 1 step at a time.
* **Hare (Fast):** Moves 2 steps at a time.

If the track is a straight line (no cycle), the Hare will reach the finish line (null) long before the Tortoise.
However, if the track is circular (has a cycle), the Hare will eventually "lap" the Tortoise from behind. If they ever occupy the same position (node) at the same time, a cycle exists.



### 2. Execution Visualization
Consider a list: `3 -> 2 -> 0 -> -4` where `-4` points back to `2`.

* **Start:** Slow at `3`, Fast at `3`.
* **Step 1:**
    * Slow moves to `2`.
    * Fast moves to `0` (skips `2`).
* **Step 2:**
    * Slow moves to `0`.
    * Fast moves to `2` (from `-4` to `2`).
* **Step 3:**
    * Slow moves to `-4`.
    * Fast moves to `-4` (from `2` to `0` to `-4`).
* **Collision:** Slow == Fast (`-4`). **Cycle Detected.**

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model
Let the distance from head to the cycle start be $A$, and the cycle length be $C$.
When the Slow pointer enters the cycle, the Fast pointer is already some distance $k$ inside the cycle.
In each step, the distance between them decreases by 1 (Fast moves 2, Slow moves 1, relative speed is 1).
Therefore, they are guaranteed to meet after exactly $C - k$ steps inside the cycle.

### 2. Time Complexity
* **No Cycle:** The Fast pointer reaches the end in $N/2$ steps.
* **Cycle:** The Slow pointer will not traverse more than $A + C$ steps (linear distance + one loop).
$$T(N) = O(N)$$

### 3. Space Complexity
We only use two pointers (`firstPointer` and `secondPointer`) regardless of the list size.
$$S(N) = O(1)$$

---

## 💻 Implementation (C++)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * ListNode *next;
 * ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* firstPointer = head;  
        ListNode* secondPointer = head;
        while (head != nullptr && secondPointer != nullptr && secondPointer->next != nullptr) {
            firstPointer = firstPointer->next;          
            secondPointer = secondPointer->next->next; 
            if (firstPointer == secondPointer) {
                return true;
            }
        }
        return false;
    }
};
```
---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).