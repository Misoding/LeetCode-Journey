# Day 6: Merge Two Sorted Lists

- **Difficulty:** Easy
- **Topics:** Linked List, Recursion, Two Pointers
- **LeetCode Link:** [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
- **Author:** [Mihail Iazinschi (LinkedIn)](https://www.linkedin.com/in/misoding)

---

## 📝 Problem Statement

You are given the heads of two sorted linked lists, `list1` and `list2`.
Merge the two lists into one **sorted** linked list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

**Constraints:**
* The number of nodes in both lists is in the range $[0, 50]$.
* $-100 \le Node.val \le 100$
* Both `list1` and `list2` are sorted in non-decreasing order.

---

## 🔬 Formal Algorithmic Analysis

We approach this problem using the **Two Pointers** technique (Iterative Approach). Since both input lists are already sorted, we can construct the result by sequentially selecting the smallest current element.

### 1. Mathematical Abstraction

Let $L_1$ and $L_2$ be the two sorted sequences of nodes.
We define a new sequence $R$ (Result) and a pointer $P$ initially pointing to a dummy head node.

In each step $k$, we compare the heads of the remaining parts of $L_1$ and $L_2$:

$$
\text{next\_node} = \min(\text{head}(L_1), \text{head}(L_2))
$$

We append $\text{next\_node}$ to $P$ and advance the corresponding list pointer. This process repeats until one list is empty.

### 2. Algorithmic Steps

1.  **Initialization:** Create a dummy node `res` to simplify edge cases (handling the head of the result list). Initialize a `tail` pointer to `&res`.
2.  **Merge Loop:** While both `list1` $\neq$ `nullptr` and `list2` $\neq$ `nullptr`:
    * If `list1->val` < `list2->val`, append `list1` to `tail` and advance `list1`.
    * Otherwise, append `list2` to `tail` and advance `list2`.
    * Advance `tail`.
3.  **Terminal Append:** Once one list is exhausted, the other list (if non-empty) contains elements strictly greater than or equal to all processed elements. We append the remainder directly to `tail`.
4.  **Result:** Return `res.next`.

### 3. Complexity Calculation

**Time Complexity Analysis:**
Let $n$ be the length of `list1` and $m$ be the length of `list2`.
In the worst case, we compare and append each node exactly once. The loop runs at most $n + m$ times.

$$
T(n, m) = \sum_{k=1}^{n+m} O(1)
$$

$$
T(n, m) \in \Theta(n + m)
$$

**Space Complexity Analysis:**
We rearrange the existing nodes by changing their `next` pointers. We only use a fixed number of auxiliary pointers (`res`, `tail`). No new nodes are allocated (except the stack-allocated dummy node).

$$
S(n, m) \in O(1)
$$

---

## 💻 Implementation (C++)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * ListNode *next;
 * ListNode() : val(0), next(nullptr) {}
 * ListNode(int x) : val(x), next(nullptr) {}
 * ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode res = ListNode(0);
        ListNode* tail = &res;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                tail->next = list1;
                list1 = list1->next;
                tail = tail->next;

            } else {
                tail->next = list2;
                list2 = list2->next;
                tail = tail->next;
            }
        }
        if (list1 != nullptr){
            tail->next = list1;
        }
        if (list2 != nullptr) {
            tail->next = list2;
        }
        return res.next;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).