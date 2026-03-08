# Day 45: Rotate List

- **Difficulty:** Medium
- **Topics:** Linked List, Two Pointers
- **LeetCode Link:** [Rotate List](https://leetcode.com/problems/rotate-list/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given the `head` of a linked list, rotate the list to the right by `k` places.

**Example 1:**
Input: `head = [1,2,3,4,5], k = 2`
Output: `[4,5,1,2,3]`
Explanation:
* Rotate 1 steps to the right: `[5,1,2,3,4]`
* Rotate 2 steps to the right: `[4,5,1,2,3]`

**Example 2:**
Input: `head = [0,1,2], k = 4`
Output: `[2,0,1]`

---

## 🏗️ Deep-Dive Implementation Strategy

The problem requires shifting the linked list elements to the right. In a singly linked list, we cannot easily traverse backwards, meaning detaching the tail requires traversing from the head to find the second-to-last node.

### 1. Modulo Arithmetic Optimization
If $k$ is greater than or equal to the length of the list $N$, rotating the list $N$ times results in the exact original list. Therefore, the effective number of rotations required is strictly:

$$
K' = k \bmod N
$$

This initial $O(N)$ pass to determine the length guarantees that we do not perform redundant full-cycle rotations.

### 2. Iterative Tail Detachment
For each of the $K'$ effective rotations:
1. Traverse the list using two pointers: `tmp` (which will land on the tail) and `lastNode` (which will land on the node right before the tail).
2. Detach the tail by setting `lastNode->next = nullptr`.
3. Reattach the tail to the front by setting `tmp->next = head`.
4. Update the `head` pointer to the newly moved node `tmp`.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the linked list be a sequence of nodes $L = (v_0, v_1, \dots, v_{n-1})$.
A right rotation by $k$ places is equivalent to a circular shift of the sequence, resulting in:

$$
L' = (v_{(n - k') \bmod n}, \dots, v_{n-1}, v_0, \dots, v_{(n - k' - 1) \bmod n})
$$

Where $k' = k \bmod n$. The algorithm achieves this through repeated application of a 1-step right shift $R(L)$:

$$
L' = R^{k'}(L)
$$

### 2. Time Complexity Analysis

1. **Length Calculation:** Traversing the list to find `len` takes strictly $\Theta(N)$ operations.
2. **Rotation Loop:** The `for` loop executes $k' = k \bmod N$ times.
3. **Inner Traversal:** Inside the loop, the `while` loop traverses from the head to the end of the list to find the penultimate node. This takes $\Theta(N)$ steps per iteration.

The total time complexity is defined by the product of the effective rotations and the traversal depth:

$$
T(N) = \Theta(N) + \sum_{i=1}^{K \bmod N} \Theta(N) = \Theta(N \cdot (K \bmod N))
$$

In the worst-case scenario, $K \bmod N = N - 1$. This causes the algorithm to degrade to quadratic time:

$$
T(N) \in O(N^2)
$$

*(Note: The optimal $O(N)$ solution involves creating a cycle by connecting the tail to the head, finding the new break-point at $N - (K \bmod N)$, and severing the connection).*

### 3. Space Complexity Analysis

The algorithm operates strictly in-place, utilizing only a few auxiliary pointers (`tmp`, `lastNode`).

$$
S(N) = \Theta(1)
$$

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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return nullptr;
        ListNode* tmp = head;
        int len = 0;
        while(tmp != nullptr) {
            len++;
            tmp = tmp -> next;
        }
        tmp = head;

        for(int i = 0; i < (k%len); i++) {
            ListNode* lastNode = head;
            tmp = head;
            while(tmp->next != nullptr){
                lastNode = tmp;
               tmp = tmp->next;
            }
            lastNode->next = nullptr;
            tmp->next = head;
            head = tmp;
        }
    return head;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).