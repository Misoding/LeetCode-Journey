# Day 12: Minimum Cost Path (Dijkstra)

- **Difficulty:** Medium
- **Topics:** Graph, Shortest Path, Dijkstra, Heap (Priority Queue)
- **LeetCode Link:** [Shortest Path in Weighted Graph](https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

You are given an integer `n` representing the number of nodes in a graph (labeled from `0` to `n-1`) and a list of `edges`. Each edge is represented as `[u, v, w]`.

The graph has a specific asymmetric property regarding traversal costs:
1.  Traversing from `u` to `v` costs `w`.
2.  Traversing from `v` to `u` (backward) costs `2 * w`.

Find the **minimum cost** to travel from node `0` to node `n-1`. If it is impossible to reach node `n-1`, return `-1`.

**Example:**
Input: `n = 3`, `edges = [[0, 1, 10], [1, 2, 10]]`
* Path $0 \to 1$: Cost 10.
* Path $1 \to 2$: Cost 10.
* Total Cost: 20.

---

## 🏗️ Deep-Dive Implementation Strategy

This problem is a classic **Shortest Path** problem on a weighted directed graph with non-negative weights. The optimal approach is **Dijkstra's Algorithm**. The key challenge lies in correctly constructing the graph to reflect the asymmetric costs ($w$ vs $2w$).

### 1. Data Structures Visualization

We transform the input `edges` into a directed graph using an **Adjacency List**. We also maintain a **Min-Heap** to efficiently select the next closest node.

**State Definition:**
* `graph[u]`: A list of pairs `{v, weight}` representing outgoing edges.
* `distanceTo[i]`: Stores the minimum cost found so far to reach node `i`.
* `minHeap`: Stores `{cost, node}`, ordered by cost ascending.

#### Example Scenario: `edges = [[0, 1, 5]]`

**Graph Construction (Logical Representation):**
The single input edge `[0, 1, 5]` creates *two* directed edges in our internal graph structure:

```text
Input Edge:  [0] ----- 5 -----> [1]

Internal Graph Representation:
Node 0:  --> [ {to: 1, cost: 5} ]        (Forward)
Node 1:  --> [ {to: 0, cost: 10} ]       (Backward: 2 * 5)
```

**Memory State (Initial):**
```text
distanceTo:   [ 0,    INF,    INF ]
visited:      [ F,     F,      F  ]
minHeap:      { (0, 0) }              <-- Top: Cost 0, Node 0
```

### 2. Dijkstra's Execution Flow

The algorithm proceeds by repeatedly extracting the node with the smallest tentative distance and relaxing its neighbors.

**Step 1: Process Node 0**
* **Extract:** `(0, 0)` from heap. Mark `0` as visited.
* **Neighbors of 0:**
    * Node `1`: New cost = `dist[0] + 5` = 5.
    * Update `dist[1] = 5`. Push `(5, 1)` to heap.

**Visual State After Step 1:**
```text
distanceTo:   [ 0,     5,     INF ]
visited:      [ T,     F,      F  ]
minHeap:      { (5, 1) }
```

**Step 2: Process Node 1**
* **Extract:** `(5, 1)` from heap. Mark `1` as visited.
* **Neighbors of 1:**
    * Node `0`: New cost = `dist[1] + 10` = 15.
    * Check: Is `15 < dist[0]`? No ($15 \not< 0$). **No Update**.

---

## 🔬 Formal Algorithmic Analysis

We formally model the problem as finding the minimum weight path in a directed graph $G = (V, E')$.

### 1. Mathematical Model

Let the set of vertices be $V = \{0, 1, \dots, n-1\}$.
The set of directed edges $E'$ is constructed from the input edge set $E_{in}$ as follows:
$$
E' = \bigcup_{(u, v, w) \in E_{in}} \{ (u, v, w), (v, u, 2w) \}
$$

The objective is to find a sequence of vertices $P = (v_0, v_1, \dots, v_k)$ such that $v_0 = 0$, $v_k = n-1$, and the path cost is minimized:
$$
\text{Minimize } C(P) = \sum_{i=0}^{k-1} \text{Weight}(v_i, v_{i+1})
$$

### 2. Time Complexity Derivation

We use Dijkstra's algorithm with a binary heap. Let $N$ be the number of nodes and $M$ be the number of input edges.

* **Graph Construction:** Iterating through $M$ input edges takes $\Theta(M)$. The resulting graph has $|E'| = 2M$ edges.
* **Heap Operations:**
    * Each vertex is extracted from the min-queue once: $N \times O(\log N)$.
    * Each edge is relaxed once. In the worst case, every relaxation triggers a `push` operation: $2M \times O(\log N)$.

Total Time Complexity:
$$
T(N, M) = O(N \log N + M \log N) \approx O(M \log N)
$$
*(Assuming the graph is connected, $M \ge N-1$)*.

### 3. Space Complexity Analysis

We utilize auxiliary structures proportional to the graph size.

1.  **Adjacency List:** Stores $2M$ edges. $S_{graph} \in O(N + M)$.
2.  **Distance & Visited Arrays:** Size $N$. $S_{arrays} \in O(N)$.
3.  **Priority Queue:** In the worst case, stores up to $O(M)$ entries.

$$
S(N, M) \in \Theta(N + M)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    struct heap_element {
        int node;
        int weight;
        bool operator>(const heap_element& oElement) const {
            return weight > oElement.weight;
        }
    };
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> graph(n);
        for (auto edge : edges) {
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];
            graph[from].push_back(std::make_pair(to, weight));
            graph[to].push_back(std::make_pair(from, 2 * weight));
        }
        vector<int> distanceTo(n, INT_MAX);
        vector<bool> visited(n,false);

        priority_queue<heap_element, vector<heap_element>, greater<heap_element>> minHeap;
        minHeap.push({0,0});
        distanceTo[0] = 0;
        while (!minHeap.empty()) {
            int node = minHeap.top().node;
            minHeap.pop();
            if (visited[node]) {
                continue;
            }
            visited[node] = true;
            for (auto toNode : graph[node]) {
                int toId = toNode.first;
                int toWeight = toNode.second;
                if (distanceTo[node] + toWeight < distanceTo[toId]) {
                    distanceTo[toId] = distanceTo[node] + toWeight;
                    minHeap.push({toId, distanceTo[toId]});
                }
            }
        }
        if (distanceTo[n-1] == INT_MAX) return -1;
        return distanceTo[n-1];
    }
};
```

---

### 📂 Repository
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).