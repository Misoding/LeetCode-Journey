# Day 14: Minimum Cost to Convert String I

- **Difficulty:** Medium
- **Topics:** Graph, Shortest Path, Dijkstra, String Processing, Shortest path
- **LeetCode Link:** [Minimum Cost to Convert String I](https://leetcode.com/problems/minimum-cost-to-convert-string-i/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)
---

## 📝 Problem Statement

You are given two strings `source` and `target` of length $n$, and two arrays `original` and `changed` with an integer array `cost`. These arrays define a set of directed transformation rules where `original[i]` can be changed to `changed[i]` with cost `cost[i]`.

Your goal is to convert `source` into `target` character by character.
Return the **minimum total cost** to achieve this. If it is impossible, return `-1`.

**Example:**
Input: `source = "abcd", target = "acbe"`
Transformations: `a->b (2)`, `b->c (5)`, `c->b (5)`, `c->e (1)`, `e->b (2)`, `d->e (20)`
* 'a' $\to$ 'a': Cost 0.
* 'b' $\to$ 'c': Direct path `b->c` costs 5.
* 'c' $\to$ 'b': Path `c->e->b` costs $1 + 2 = 3$ (Better than direct 5!).
* 'd' $\to$ 'e': Direct `d->e` costs 20.
Total: $0 + 5 + 3 + 20 = 28$.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem effectively asks for the shortest path between characters in a weighted directed graph where nodes are lowercase English letters. The constraints ($N \le 10^5$ string length) require an efficient lookup mechanism. We implement an **On-Demand Dijkstra with Caching** strategy.

### 1. Data Structures Visualization

We utilize a hybrid approach: an Adjacency List for the graph structure and a Matrix for constant-time cost lookups once computed.

**State Definition:**
* `fullGraph[u]`: Adjacency list storing pairs `{v, weight}` for node `u`.
* `distTo[26][26]`: A 2D array acting as a **Cache**. `distTo[i][j]` stores the shortest distance from char `i` to `j`. Initialized to Infinity.
* `visited[26]`: A boolean flags array indicating if we have already computed Dijkstra starting from character `i`.

### 2. The "On-Demand" Caching Logic

Instead of pre-computing All-Pairs Shortest Paths (Floyd-Warshall) which runs in $O(V^3)$ regardless of input, or running Dijkstra for every query pair (inefficient for repeated characters), we compute paths **lazily**.

**Scenario:** `source = "abca"`, `target = "xyzx"`

**Step 1: Process index 0 ('a' $\to$ 'x')**
* Check `visited['a']`: **False**.
* **Action:** Run Dijkstra starting from `'a'`.
* **Result:** `distTo['a']` row is now fully populated with shortest paths to *all* other characters.
* **Update:** Set `visited['a'] = true`.
* **Cost:** Add `distTo['a']['x']`.

**Step 2: Process index 1 ('b' $\to$ 'y')**
* Check `visited['b']`: **False**.
* **Action:** Run Dijkstra starting from `'b'`. Populate `distTo['b']` row.
* **Cost:** Add `distTo['b']['y']`.

**Step 3: Process index 3 ('a' $\to$ 'x')**
* Check `visited['a']`: **True**.
* **Action:** **SKIP computation**.
* **Cost:** Immediately retrieve `distTo['a']['x']` from cache.

### 3. Visualizing Dijkstra on Alphabet Graph

The graph size is fixed at $\Sigma = 26$ nodes.

```text
       (2)         (5)
 [a] -------> [b] -------> [c]
  |            ^            |
  | (10)       | (2)        | (1)
  v            |            v
 [x] <------- [e] <------- [d]
        (1)          (1)

Target: Cost from 'a' to 'e'?
Dijkstra('a'):
1. Heap: {(0, 'a')}
2. Pop 'a'. Push ('b', 2), ('x', 10).
3. Pop 'b'. Push ('c', 2+5=7).
4. Pop 'c'. Push ('d', 7+1=8).
5. Pop 'd'. Push ('e', 8+1=9).
...
Cache distTo['a']['e'] = 9.
```

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let $\Sigma$ be the size of the alphabet ($\Sigma = 26$). Let $G=(V, E)$ be the graph constructed from the transformation rules.
The total cost is defined as:

$$
C_{total} = \sum_{i=0}^{n-1} d_G(source[i], target[i])
$$

where $d_G(u, v)$ denotes the shortest path distance from vertex $u$ to vertex $v$ in graph $G$.

### 2. Time Complexity Derivation

Let $N$ be the length of the strings `source` and `target`.
Let $M$ be the number of transformation rules (edges).

The algorithm proceeds in three phases:
1.  **Graph Construction:** Iterating over `original`, `changed`, `cost`.
    $$T_{build} = O(M)$$
2.  **Shortest Path Computation (On-Demand):** In the worst case, the `source` string contains all 26 distinct characters. We run Dijkstra exactly $\Sigma$ times.
    * Standard Dijkstra using Binary Heap on graph with $V=\Sigma$ and $E=M$.
    * Complexity per run: $O(M \log \Sigma)$ or $O(M \log M)$.
    $$T_{paths} = \Sigma \times O(M \log \Sigma)$$
3.  **Cost Summation:** We iterate through the string of length $N$, performing $O(1)$ table lookups.
    $$T_{sum} = O(N)$$

**Total Time Complexity:**

$$
T(N, M) = O(M) + O(\Sigma \cdot M \log \Sigma) + O(N)
$$

Since $\Sigma = 26$ is a small constant, the asymptotic complexity simplifies to:

$$
T(N, M) \in O(M + N)
$$

### 3. Space Complexity Analysis

1.  **Graph Storage:** Adjacency list stores $M$ edges.
    $$S_{graph} \approx O(M)$$
2.  **Distance Matrix:** Fixed size $26 \times 26$ integers.
    $$S_{matrix} = O(\Sigma^2) \approx O(1)$$
3.  **Priority Queue:** Stores at most $M$ edges in worst case during execution.
    $$S_{heap} \approx O(M)$$

**Total Space Complexity:**

$$
S(N, M) \in O(M)
$$

---

## 💻 Implementation (C++)

```cpp
#define ll long long
class Solution {
public:
    struct heap_element {
        ll node;
        ll weight;
        bool operator>(const heap_element& oElement) const {
            return weight > oElement.weight;
        }
    };
    vector<vector<pair<ll, ll>>> fullGraph;
    const long long cmpMax = LONG_LONG_MAX - 1000000000;
    ll distTo[26][26];
    vector<bool> visited;

    void dijkstra(ll startNode) {
        priority_queue<heap_element, vector<heap_element>, greater<heap_element>> minHeap;
        minHeap.push({startNode, 0});
        while (!minHeap.empty()) {
            auto node = minHeap.top();
            minHeap.pop();
            ll distCost = node.weight;
            ll destId = node.node;
            if (distCost > distTo[startNode][destId]) continue;
            for (auto neighNode : fullGraph[destId]) {
                ll to = neighNode.first;
                ll price = neighNode.second;
                if (distTo[startNode][destId] + price < distTo[startNode][to]) {
                    distTo[startNode][to] = distTo[startNode][destId] + price;
                    minHeap.push({to, distTo[startNode][to]});
                }
            }
        }
    }
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        vector<vector<pair<ll, ll>>> graph = vector<vector<pair<ll, ll>>>(26, vector<pair<ll,ll>>());
        visited = vector<bool>(26, false);
        for(int i = 0; i < 26; i++) {
            for(int j = 0; j < 26; j ++) {
                if (i == j) {
                    distTo[i][j] = 0;
                } else {
                    distTo[i][j] = cmpMax;
                }
            }
        }
        for(int i = 0; i < original.size(); i++) {
            ll origId = original[i] - 'a';
            ll destId = changed[i] - 'a';
            ll pathCost = (ll) cost[i];
            graph[origId].push_back(std::make_pair(destId, pathCost));
        }
        fullGraph = graph;
        ll resCost = 0;
        for (int i = 0; i < source.size(); i++) {
            ll from = (ll) source[i] - 'a';
            ll to = (ll) target[i] - 'a';
            if (from == to) {
                continue;
            }
            if (!visited[from]) {
                dijkstra(from);
                visited[from] = true;
            }
            if (distTo[from][to] == cmpMax) {
                return -1;
            } else {
                resCost += distTo[from][to];
            }
        }
        return resCost;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).