# Day 52: Add Two Numbers

- **Difficulty:** Medium
- **Topics:** Linked List, Math
- **LeetCode Link:** [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in **reverse order**, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Example 1:**
Input: `l1 = [2,4,3], l2 = [5,6,4]`
Output: `[7,0,8]`
Explanation: $342 + 465 = 807$.

**Example 2:**
Input: `l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]`
Output: `[8,9,9,9,0,0,0,1]`

---

## 🏗️ Deep-Dive Implementation Strategy

The problem conceptually mimics binary or decimal addition performed in hardware ALUs (Arithmetic Logic Units), implementing a **Ripple Carry Adder** using a linked list structure. Since the digits are already in reverse order (Least Significant Digit at the head), we can process them sequentially in a single pass.

### 1. Architectural Pattern: Sentinel Node (Dummy Head)
To prevent constant branching logic (checking if the `head` of the result list is `nullptr` before appending), we initialize a `newListHead` with a default value. A `start` pointer acts as the iterator building the list. At the end, we simply return `newListHead->next`, cleanly bypassing the dummy node.

### 2. The Arithmetic State Machine
The algorithm processes the lists iteratively, maintaining a `carryIn` state:
1.  **Synchronous Addition:** While both `l1` and `l2` have valid nodes, calculate the positional sum: `res = l1->val + l2->val + carryIn`.
2.  **State Extraction:** * The new node's value is the remainder: `res % 10`.
    * The new carry for the next positional magnitude is the quotient: `res / 10`.
3.  **Asynchronous Tail Processing:** Since lists can be of unequal lengths, we extract the non-null remainder (`remainPart`) and continue the addition strictly with the `carryIn`.
4.  **Terminal Overflow:** If the lists are fully processed but `carryIn > 0` (e.g., $9+1=10$), an absolute final node containing `1` must be appended.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $A$ and $B$ be two integers represented by sequences of digits $a_i$ and $b_i$, where $i \in \{0, \dots, N-1\}$ and $j \in \{0, \dots, M-1\}$.
The sum sequence $S = s_0, s_1, \dots, s_K$ is defined via the recurrence relation:

$$
s_k = (a_k + b_k + c_k) \bmod 10
$$

With the carry $c_k$ defined as:

$$
c_{k+1} = \lfloor \frac{a_k + b_k + c_k}{10} \rfloor, \quad c_0 = 0
$$

Where undefined elements $a_k$ (for $k \ge N$) or $b_k$ (for $k \ge M$) evaluate to $0$.
The length of the resulting sequence $K$ is bounded by $\max(N, M) + 1$.

### 2. Time Complexity Analysis

The algorithm iterates through both linked lists exactly once. The primary loop runs $\min(N, M)$ times, and the secondary remainder loop runs $|N - M|$ times.
Memory allocation and pointer assignments are $\Theta(1)$ operations.

$$
T(N, M) = \Theta(\min(N, M)) + \Theta(|N - M|) = \Theta(\max(N, M))
$$

$$
T(N, M) \in O(\max(N, M))
$$

### 3. Space Complexity Analysis

The algorithm allocates a strictly new linked list to store the sum. The number of nodes generated equals the length of the longest input list, plus at most 1 extra node for terminal overflow.

$$
S(N, M) = \Theta(\max(N, M) + 1) = \Theta(\max(N, M))
$$

$$
S(N, M) \in O(\max(N, M))
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carryIn = 0;
        ListNode* newListHead = new ListNode();
        ListNode* start = newListHead;
        while(l1 != nullptr && l2 != nullptr){
            int res = l1->val + l2->val + carryIn;
            carryIn = res / 10;
            ListNode* node = new ListNode(res%10);
            if (newListHead->next == nullptr) {
                newListHead->next = node;
                start = start -> next;
            } else {
                start->next = node;
                start = start->next;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        ListNode* remainPart = l1 == nullptr ? l2 : l1;
        while(remainPart != nullptr) {
            int res = remainPart->val + carryIn;
            carryIn = res / 10;
            ListNode* node = new ListNode(res%10);
            if (newListHead->next == nullptr) {
                newListHead->next = node;
                start = start -> next;
            } else {
                start->next = node;
                start = start->next;
            }
            remainPart = remainPart->next;
        }
        if (carryIn) {
            ListNode* lastEl = new ListNode(1);
            start->next = lastEl;
        }
        return newListHead->next;
    }
};
```

---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).