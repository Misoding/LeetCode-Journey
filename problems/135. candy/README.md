# Day 49: Candy

- **Difficulty:** Hard
- **Topics:** Array, Greedy, Graph Theory, Topological Sort
- **LeetCode Link:** [Candy](https://leetcode.com/problems/candy/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

There are `n` children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.

You are giving candies to these children subjected to the following requirements:
1. Each child must have at least one candy.
2. Children with a higher rating get more candies than their neighbors.

Return the minimum number of candies you need to have to distribute the candies to the children.

**Example 1:**
Input: `ratings = [1,0,2]`
Output: `5`
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

**Example 2:**
Input: `ratings = [1,2,2]`
Output: `4`
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.

---

## 🏗️ Deep-Dive Implementation Strategy

While the standard solution involves a two-pass Greedy algorithm, this implementation uses a highly robust **Graph Theory Architecture**. The rules of candy distribution dictate strict dependencies: if a child has a higher rating than an adjacent neighbor, their candy count *depends* on that neighbor's candy count.

### 1. Modeling as a Directed Acyclic Graph (DAG)
We map the 1D array into a Dependency Graph:
* **Nodes:** Each child $i$ is a node in the graph.
* **Directed Edges:** If `ratings[i] > ratings[i-1]`, child $i$ must receive more candies than child $i-1$. Thus, we draw a directed edge from $i-1 \to i$. This signifies that the optimal value of $i$ can only be calculated *after* $i-1$ is finalized. We also apply this logic for the right neighbor $i+1 \to i$.
* **In-Degree:** The number of dependencies a node has before it can be processed.

### 2. Kahn's Algorithm (Topological Sort)
1. **Initialization:** Every child starts with a baseline of 1 candy.
2. **Queueing:** We push all nodes with an `inDegree` of 0 into a processing queue. These are local minima—children who are not rated higher than any neighbor, so they strictly receive 1 candy.
3. **Propagation:** We pop a node `u` from the queue. For every neighbor `v` that depends on `u` (edge `u -> v`), we update `v`'s candies: `candies[v] = max(candies[v], candies[u] + 1)`.
4. We decrement the in-degree of `v`. If it reaches 0, all of its dependencies are resolved, and we push it into the queue.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the set of children be vertices $V = \{0, 1, \dots, n-1\}$.
We construct a Directed Acyclic Graph $G = (V, E)$, where a directed edge $(u, v) \in E$ exists if and only if $u$ and $v$ are adjacent in the original array and $ratings[v] > ratings[u]$.

The problem is equivalent to finding the longest path terminating at each vertex $v$ in $G$, given a base weight of 1 for all vertices.
Using Kahn's algorithm, the recurrence for topological relaxation is:

$$
C(v) = \max\left(1, \max_{(u,v) \in E} (C(u) + 1)\right)
$$

The total minimized cost is the sum of the optimal states:

$$
\text{Total} = \sum_{i=0}^{n-1} C(i)
$$

### 2. Time Complexity Analysis

1.  **Graph Construction:** Iterating through the array of length $N$ to build the adjacency list and in-degree array takes $\Theta(N)$. Since each node has at most 2 neighbors, $|E| \le 2N$.
2.  **Topological Sort:** Kahn's algorithm visits every vertex exactly once and relaxes every edge exactly once. Time taken is $O(|V| + |E|) = O(N + 2N) = O(N)$.

$$
T(N) = \Theta(N) + O(N) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The architectural transformation to a graph requires auxiliary structures:
* Adjacency List (`vector<vector<int>>`): Stores up to $2N$ edges $\to O(N)$.
* In-Degree Array (`vector<int>`): Stores $N$ integers $\to O(N)$.
* Queue (`queue<int>`): Holds at most $N$ elements $\to O(N)$.
* State Array (`vector<int> candies`): Stores $N$ elements $\to O(N)$.

$$
S(N) = O(N) + O(N) + O(N) + O(N) = \Theta(N)
$$

$$
S(N) \in O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        if (ratings.size() == 1) return 1;
        int n = ratings.size();
        vector<int> inDegreePriority(n);
        vector<vector<int>> adjency(n);
        for (int i = 0; i< n; i++) {
            if (i > 0 && ratings[i] > ratings[i-1]){
                adjency[i-1].push_back(i);
                inDegreePriority[i]++;
            }
            if (i < n-1 && ratings[i] > ratings[i+1]) {
                adjency[i+1].push_back(i);
                inDegreePriority[i]++;
            }
        }

        queue<int> topoQ;
        for(int i = 0; i < n; i++){
            if (inDegreePriority[i] == 0) {
                topoQ.push(i);
            }
        }
        vector<int> candies(n,1);
        while(!topoQ.empty()) {
            int fromNode = topoQ.front();
            topoQ.pop();
            for(auto to : adjency[fromNode]){
                inDegreePriority[to]--;
                candies[to] = max(candies[fromNode] + 1, candies[to]);
                if (inDegreePriority[to] == 0) {
                    topoQ.push(to);
                }
            }
        }
    int totalCandies = 0;
    for(int i = 0; i < n; i++) {
        totalCandies+=candies[i];
    }
    return totalCandies;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).