# Day 29: Reorder List

- **Difficulty:** Medium
- **Topics:** Linked List, Two Pointers, Stack, Array
- **LeetCode Link:** [Reorder List](https://leetcode.com/problems/reorder-list/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given the head of a singly linked-list. The list can be represented as:

$$
L_0 \rightarrow L_1 \rightarrow \dots \rightarrow L_{n-1} \rightarrow L_n
$$

Reorder the list to be on the following form:

$$
L_0 \rightarrow L_n \rightarrow L_1 \rightarrow L_{n-1} \rightarrow L_2 \rightarrow L_{n-2} \rightarrow \dots
$$

You may not modify the values in the list's nodes. Only nodes themselves may be changed.

**Example 1:**
Input: `head = [1,2,3,4]`
Output: `[1,4,2,3]`

**Example 2:**
Input: `head = [1,2,3,4,5]`
Output: `[1,5,2,4,3]`

---

## 🏗️ Deep-Dive Implementation Strategy

The standard "optimal" solution involves finding the middle, reversing the second half, and merging ($O(1)$ space). However, your approach simplifies the problem by **linearizing the linked list** into an array (vector) of pointers. This allows random access to nodes, making the reordering trivial using the **Two Pointers** technique.

### 1. The Vector Approach (Linearization)
A linked list only supports Sequential Access ($O(N)$). The reordering pattern requires alternating between the start and the end of the list.
By storing pointers in a vector, we upgrade the data structure to support **Random Access ($O(1)$)**.

### 2. The Algorithm
1.  **Storage:** Traverse the linked list and store every `ListNode*` in a `vector<ListNode*>`.
2.  **Two Pointers:** Initialize `l = 0` (start) and `r = n-1` (end).
3.  **Wiring Loop:**
    * Link `nodes[l]` to `nodes[r]`.
    * Increment `l`.
    * If pointers meet (`l == r`), break immediately.
    * Link `nodes[r]` to `nodes[l]` (the next node in the original sequence).
    * Decrement `r`.
4.  **Termination:** Ensure the last processed node (where `l` meets `r`) points to `nullptr` to avoid cycles (infinite loops).

[Image of linked list reordering steps]

---

## 🔬 Formal Algorithmic Analysis

We analyze the algorithm based on the transformation of indices and operational cost.

### 1. Mathematical Model (Permutation)

Let the set of nodes be $V = \{v_0, v_1, \dots, v_n\}$.
The problem asks for a permutation $\pi$ of the indices $\{0, 1, \dots, n\}$ such that the new order is:

$$
\pi(0), \pi(n), \pi(1), \pi(n-1), \pi(2), \dots
$$

Using the vector $A$ where $A[i]$ stores the address of $v_i$, we perform pointer manipulations to satisfy:

$$
v_{\pi(k)} \rightarrow \text{next} = v_{\pi(k+1)}
$$

### 2. Time Complexity Analysis

The total time complexity $T(N)$ is the sum of the linearization phase and the reordering phase.

**Phase 1: Linearization**
We traverse the list exactly once to populate the vector. Let $c_1$ be the cost of `push_back`.

$$
T_{fill}(N) = \sum_{i=0}^{n} c_1 = \Theta(N)
$$

**Phase 2: Reordering (Two Pointers)**
The pointers $l$ and $r$ start at opposite ends and move towards the center. In each iteration, we perform constant time pointer assignments ($c_2$). The loop runs for $N/2$ iterations.

$$
T_{link}(N) = \sum_{k=0}^{\lfloor N/2 \rfloor} c_2 \approx \frac{N}{2} \cdot c_2 = \Theta(N)
$$

**Total Time Complexity:**

$$
T(N) = T_{fill}(N) + T_{link}(N) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

We allocate a vector to store pointers to the nodes. Let $S_p$ be the size of a pointer (typically 8 bytes on 64-bit systems).

$$
S(N) = N \cdot S_p = \Theta(N)
$$

$$
S(N) \in O(N)
$$

*(Note: While $O(N)$ space is technically less optimal than the $O(1)$ approach involving list reversal, the constant factor is small since we store addresses, not data copies).*

---

## 💻 Implementation (C++)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> nodes;
        ListNode* tmpNode = head;
        while(tmpNode != nullptr) {
            nodes.push_back(tmpNode);
            tmpNode = tmpNode->next;
        }
        int l = 0, r = nodes.size()-1;
        //[1->2 2->3 3->4 4->5 5->null] l = 0 r = n-1 
        //[1->5 2->3 3->4 4->5 5->null] l = 1 r = n-1
        //[1->5 2->3 3->4 4->5 5->2] l = 1 r = n-2
        //[1->5 2->4 ] ...
        while(l < r) {
            nodes[l]->next = nodes[r];
            l++;
            if(l == r) {
                break;
            }
            nodes[r]->next = nodes[l];
            r--;
        }
        nodes[l]->next=nullptr;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).