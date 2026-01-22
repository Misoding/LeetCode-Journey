# Day 7: Minimum Pair Removal to Sort Array I

- **Difficulty:** Easy
- **Topics:** Heap (Priority Queue), Linked List Simulation, Greedy, Lazy Deletion
- **LeetCode Link:** [Minimum Pair Removal to Sort Array I](https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/)
- **Author:** [Mihail Iazinschi](https://github.com/Misoding)
---

## 📝 Problem Statement

Given an array `nums`, you can perform the following operation any number of times:
1.  Select the **adjacent** pair with the **minimum** sum. If multiple exist, choose the leftmost one.
2.  Replace the pair with their sum.

Return the **minimum number of operations** needed to make the array **non-decreasing**.

**Example:**
Input: `[5, 2, 3, 1]`
1. Pair `(3, 1)` has min sum 4. Array becomes `[5, 2, 4]`.
2. Pair `(2, 4)` has min sum 6. Array becomes `[5, 6]`.
Result: Sorted in 2 steps.

---

##  Deep-Dive Implementation Strategy

This problem requires efficiently finding the minimum sum of neighbors and merging them dynamically. A standard `std::vector` `erase` operation would cost $O(N)$, leading to $O(N^2)$ complexity. To achieve $O(N \log N)$, we simulate a **Doubly Linked List** using arrays and utilize a **Min-Heap** with **Lazy Deletion**.

### 1. Data Structures Visualization

Instead of allocating actual nodes, we use three parallel vectors to simulate a Linked List where indices act as pointers.

**State Definition:**
* `linkedList[i]`: Stores `{current_value, next_index}`.
* `reverseLinkedList[i]`: Stores `{current_value, prev_index}`.
* `minHeap`: Stores `{sum, index_of_left_element}`.

#### Example Scenario: `nums = [5, 2, 3, 1]`

**Initial State (Logical Representation):**
```text
Indices:      0      1      2      3
Values:      [5] -> [2] -> [3] -> [1]
Next Ptr:     1      2      3     -1
Prev Ptr:    -1      0      1      2
Heap:        {(7,0), (5,1), (4,2)}  <-- Min is (4, index 2) i.e., 3+1
```

### 2. The Merge Operation & Lazy Deletion

When we extract the minimum `{sum: 4, id: 2}` from the heap, we perform a merge on index 2 and its neighbor (index 3).

**Visualizing the Merge (Step 1):**
We combine node `2` and `3`. Node `2` absorbs `3`. Node `3` is logically deleted.

```text
       (Modified)            (Deleted)
Index:     2                    3
Val:   3 + 1 = 4              Ignore
Next:  old_next(3) -> -1
```

**Pointer Updates (The "Wiring"):**
The pointers "skip" over the deleted index 3.
* `linkedList[2].next` becomes `-1`.
* (If index 3 had a next neighbor, its prev pointer would now point to 2).

**Logical State After Step 1:**
```text
Indices:      0      1      2      (3 is dead)
Values:      [5] -> [2] -> [4] ->  X
Next Ptr:     1      2     -1
```

**Heap & Lazy Deletion Logic:**
The heap might contain "stale" sums involving index 3 (e.g., if index 3 had a right neighbor). Since we cannot easily search and remove from a `priority_queue`, we use **Lazy Deletion**:
1.  We mark `deleted_origin_nums[3] = true`.
2.  When we pop from the heap, we check: *Is the calculated sum valid? Does it match the current values in `linkedList`? Is the neighbor deleted?*
3.  If invalid, we simply **discard (`continue`)** and pop the next element.

### 3. The "Wrong Order" Counter Optimization
We maintain a counter `wrong_order_count` tracking how many pairs satisfy $nums[i] > nums[i+1]$.
* Before merging, we check if the pair `(2, 3)` or their neighbors contributed to unsorted-ness. If yes, decrement counter.
* After merging to `[5, 2, 4]`, we check the new neighbors. `5 > 2` (Still bad), `2 < 4` (Good).
* **Termination:** We stop immediately when `wrong_order_count == 0`.

---

## 🔬 Formal Algorithmic Analysis

To ensure an efficient solution for constraints up to $N=10^5$, we model the problem using a dynamic sequence data structure and analyze the cost using the **Aggregate Method** (Amortized Analysis).

### 1. Mathematical Model & State Definition

Let the sequence at step $t$ be denoted as $S^{(t)} = \{v_1, v_2, \dots, v_{k_t}\}$.
We define the set of candidate operations (adjacent sums) at step $t$ as:

$$
\Sigma^{(t)} = \{ (s_i, i) \mid s_i = v_i + v_{i+1}, \ 1 \le i < k_t \}
$$

The greedy strategy dictates selecting the operation corresponding to:

$$
m^{(t)} = \min_{(s, i) \in \Sigma^{(t)}} (s)
$$

Since standard array deletions operate in $O(N)$, leading to a total complexity of $O(N^2)$, we map the sequence indices to a **Virtual Doubly Linked List** topology.
Let $\mathcal{L}$ be the mapping function such that for any active index $i$:
* $next(i)$ points to the index of the element immediately following $v_i$.
* $prev(i)$ points to the index of the element immediately preceding $v_i$.

### 2. Time Complexity Derivation (Amortized)

We analyze the runtime by partitioning the algorithm into **Initialization** and **Processing** phases. Let $N$ be the initial size of the array.

#### A. Initialization Phase ($T_{init}$)
We construct the initial heap and linked list topology.
1.  **Topology Setup:** Linking $N$ nodes takes $\sum_{i=0}^{N-1} O(1) = O(N)$.
2.  **Heap Construction:** We insert all $N-1$ initial adjacent sums into the priority queue.

$$
T_{init} = O(N)
$$

#### B. Processing Phase ($T_{process}$)
Let $K$ be the number of merge operations performed. Since the array size decreases by 1 at each step, $K < N$.
The algorithm uses a **Min-Heap** with **Lazy Deletion**. This means "stale" sums (involving indices that have already been merged) remain in the heap until extracted.

**Total Heap Operations (Aggregate Analysis):**
Let $N_{push}$ be the total number of elements pushed into the heap over the entire execution.
* **Initial Load:** $N-1$ elements.
* **Dynamic Load:** When merging nodes $u$ and $v$, we potentially add two new sums (left neighbor + new node, new node + right neighbor).

Thus, the total number of pushes is bounded by:

$$
N_{push} \le (N-1) + \sum_{k=1}^{K} 2 \le 3N
$$

**Cost per Operation:**
The cost of a heap extraction or insertion is logarithmic with respect to the heap size $H$. Since $H \le N_{push} \le 3N$:

$$
Cost_{op} \in O(\log(3N)) = O(\log N)
$$

**Total Processing Cost:**
The `while` loop extracts elements until the array is sorted. In the worst case (including lazy deletions), we extract every element ever pushed.

$$
T_{process} = \sum_{j=1}^{N_{push}} Cost_{op} \approx \sum_{j=1}^{3N} O(\log N)
$$

$$
T_{process} \in O(N \log N)
$$

#### C. Total Time Complexity
Combining both phases:

$$
T(N) = T_{init} + T_{process} \approx O(N) + O(N \log N)
$$

$$
T(N) \in O(N \log N)
$$

### 3. Space Complexity Analysis

We analyze the memory requirements for the auxiliary structures used to simulate the linked list and maintain state.

1.  **Topology Vectors:** We use two vectors of size $N$ (`linkedList`, `reverseLinkedList`) storing pairs of `{value, pointer}`.
    $$S_{topology} = 2 \cdot N \cdot \text{sizeof(pair)}$$

2.  **State Vector:** A boolean/integer vector `deleted` of size $N$ to track valid nodes.
    $$S_{state} = N \cdot \text{sizeof(int)}$$

3.  **Heap Storage:** The priority queue stores tuples `{sum, index}`. As derived above, the maximum capacity is bounded by $O(N)$.
    $$S_{heap} \le O(N)$$

**Total Space Complexity:**

$$
S(N) = S_{topology} + S_{state} + S_{heap} \approx 4N
$$

$$
S(N) \in \Theta(N)
$$


---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        // pair<int,int> -> sum, id where sum start
        std::priority_queue<pair<long long,int>, std::vector<pair<long long,int>>, std::greater<pair<long long,int>>> minHeap;
        int n = nums.size();
        int commitedSteps = 0;
        vector<pair<long long,int>> linkedList(n); // [5, 1], [2, 3], [3, 3], [1, -1];
        vector<pair<long long,int>> reverseLinkedList(n); // [5, -1], [2, 0], [3,1], [1, 2];
        vector<int> deleted_origin_nums(n);
        int wrong_order_count = 0;
        for (int i = 0; i < n-1; i++) {
            minHeap.push(std::make_pair((long long)nums[i] + nums[i+1], i));
            linkedList[i] = std::make_pair((long long)nums[i], i+1);
            reverseLinkedList[i] = std::make_pair((long long)nums[i], i-1);
            if (nums[i] > nums[i+1]) wrong_order_count++;
        }
        linkedList[n-1] = std::make_pair((long long)nums[n-1], -1);
        if (wrong_order_count == 0) {
            return 0;
        }
        while (wrong_order_count > 0 && !minHeap.empty()) {
            std::pair<long long,int> min_sum = minHeap.top();
            minHeap.pop();
            int min_sum_id = min_sum.second;
            long long min_sum_sum = min_sum.first;

            int sumPairSecondNumId = linkedList[min_sum_id].second;
            if (deleted_origin_nums[min_sum_id] || sumPairSecondNumId == -1 || deleted_origin_nums[sumPairSecondNumId]) {
                continue;
            }
            if ((long long) linkedList[min_sum_id].first + linkedList[sumPairSecondNumId].first != min_sum_sum){
                continue;
            }
            int prevNumId = reverseLinkedList[min_sum_id].second;
            int nextNum_afterSumId = linkedList[sumPairSecondNumId].second;
            if (prevNumId != -1) {
                if (linkedList[prevNumId].first > linkedList[min_sum_id].first) {
                    wrong_order_count--;
                }
            }

            if (linkedList[min_sum_id].first > linkedList[sumPairSecondNumId].first){
                wrong_order_count--;
            }
            if (nextNum_afterSumId != -1) {
                if (linkedList[sumPairSecondNumId].first > linkedList[nextNum_afterSumId].first) {
                    wrong_order_count--;
                }
            }

            commitedSteps++;
            linkedList[min_sum_id].first = min_sum_sum;
            deleted_origin_nums[sumPairSecondNumId] = true;

            linkedList[min_sum_id].second = nextNum_afterSumId;
            if (nextNum_afterSumId != -1) {
                reverseLinkedList[nextNum_afterSumId].second = min_sum_id;
            }

            if (prevNumId != -1) {
                if (linkedList[prevNumId].first > linkedList[min_sum_id].first){
                    wrong_order_count++;
                }
                minHeap.push(std::make_pair(linkedList[prevNumId].first + linkedList[min_sum_id].first, prevNumId));
            }

            if (nextNum_afterSumId != -1) {
                if (linkedList[min_sum_id].first > linkedList[nextNum_afterSumId].first) {
                    wrong_order_count++;
                }
                minHeap.push(std::make_pair(linkedList[nextNum_afterSumId].first + linkedList[min_sum_id].first, min_sum_id));
            }
        }
        return commitedSteps;
    }
};
```

---

### 🔗 Connect
### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).