# Day 46: Swap Nodes in Pairs

- **Difficulty:** Medium
- **Topics:** Linked List, Recursion
- **LeetCode Link:** [Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a singly linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed).

**Example 1:**
Input: `head = [1,2,3,4]`
Output: `[2,1,4,3]`

**Example 2:**
Input: `head = []`
Output: `[]`

**Example 3:**
Input: `head = [1]`
Output: `[1]`

---

## 🏗️ Deep-Dive Implementation Strategy

The problem exhibits perfect optimal substructure, making it an ideal candidate for **Recursion**. 

### 1. The Recursive Architecture
At any given state, we are only concerned with a localized sub-problem: a pair of nodes.
Let the current node be `head` and its adjacent node be `secondNode` (`head->next`).
1.  **Recursive Leap of Faith:** We assume our recursive function `swapPairs` works perfectly for the rest of the list. We call `swapPairs(head->next->next)` and store the result (which is the head of the processed remaining list).
2.  **Pointer Wiring (The Swap):**
    * The `head` (which was 1st) must now point to the processed remaining list.
    * The `secondNode` (which was 2nd) must now point to `head`.
3.  **Return New Head:** The `secondNode` becomes the new head of this local pair, so we return it.

### 2. Base Case Edge-Handling
The recursion terminates when there are fewer than 2 nodes left to process:
* If `head == nullptr`, the list is empty (or an even-length list ends).
* If `head->next == nullptr`, there is only one node left (an odd-length list ends). It has no pair, so it must be returned intact (`return head`) to be appended to the rest of the reversed structure.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let a linked list be represented as a sequence $L = (v_1, v_2, v_3, v_4, \dots)$.
The swap function $S(L)$ is defined recursively:

$$
S(L) = \begin{cases} 
\emptyset & \text{if } L = \emptyset \\
(v_1) & \text{if } L = (v_1) \\
(v_2, v_1) \oplus S(L \setminus \{v_1, v_2\}) & \text{if } |L| \ge 2 
\end{cases}
$$

Where $\oplus$ denotes the concatenation operator (implemented via pointer assignment).

### 2. Time Complexity Analysis

The recursive function processes the list in pairs. For a list of $N$ nodes, there are $\lfloor N / 2 \rfloor$ recursive calls. Inside each call, we perform exactly three pointer assignments (which take $\Theta(1)$ constant time).

$$
T(N) = \lfloor \frac{N}{2} \rfloor \cdot \Theta(1) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The recursion builds a call stack. The maximum depth of the call stack corresponds to the number of pairs.
Memory overhead per stack frame is $\Theta(1)$ (storing local pointers).

$$
S_{aux}(N) = \Theta(\frac{N}{2}) = \Theta(N)
$$

$$
S(N) \in O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* secondNode = head->next;
        ListNode* nextList = swapPairs(head->next->next);
        head->next = nextList; 
        secondNode->next = head; 
        return secondNode;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).