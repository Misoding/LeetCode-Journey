# Day 2: Find the Largest Area of Square Inside Two Rectangles

- **Difficulty:** Medium
- **Topics:** Geometry, Array, Math
- **LeetCode Link:** [Find the Largest Area of Square Inside Two Rectangles](https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/)
- **Author:** [Mihail Iazinschi (LinkedIn)](https://www.linkedin.com/in/misoding)

---

## 📝 Problem Statement

Given $n$ rectangles in a 2D plane defined by their bottom-left coordinates $(ax_i, ay_i)$ and top-right coordinates $(bx_i, by_i)$, select a pair of rectangles $(i, j)$ such that the area of the largest square fitting inside their intersection $R_i \cap R_j$ is maximized.

Return this maximum area. If no intersection exists, return 0.

---

## 🔬 Formal Algorithmic Analysis

We approach this problem by reducing the 2D geometric intersection to a system of linear inequalities on 1D intervals.

### 1. Mathematical Abstraction
Let a rectangle $R_k$ be defined as the Cartesian product of two closed intervals:
$$R_k = [x_{start}^{(k)}, x_{end}^{(k)}] \times [y_{start}^{(k)}, y_{end}^{(k)}]$$

The intersection of two rectangles $R_i$ and $R_j$ is the intersection of their corresponding intervals on each axis independently:
$$R_i \cap R_j = \left( [x_{start}^{(i)}, x_{end}^{(i)}] \cap [x_{start}^{(j)}, x_{end}^{(j)}] \right) \times \left( [y_{start}^{(i)}, y_{end}^{(i)}] \cap [y_{start}^{(j)}, y_{end}^{(j)}] \right)$$

### 2. Derivation of Intersection Coordinates
For any two intervals $I_1 = [a, b]$ and $I_2 = [c, d]$, their intersection $I_{overlap}$ is given by:
$$\text{start}_{overlap} = \max(a, c)$$
$$\text{end}_{overlap} = \min(b, d)$$

Applying this to our 2D system, the intersection rectangle $R_{overlap}$ is defined by:
* $X_{start} = \max(bottomLeft[i][0], bottomLeft[j][0])$
* $X_{end} = \min(topRight[i][0], topRight[j][0])$
* $Y_{start} = \max(bottomLeft[i][1], bottomLeft[j][1])$
* $Y_{end} = \min(topRight[i][1], topRight[j][1])$

**Validity Condition:**
The intersection is a valid non-degenerate rectangle if and only if:
$$(X_{start} < X_{end}) \land (Y_{start} < Y_{end})$$

### 3. Optimization Function
Let $\Delta x = X_{end} - X_{start}$ and $\Delta y = Y_{end} - Y_{start}$.
The region of intersection is a rectangle of dimensions $\Delta x \times \Delta y$.

We seek to inscribe a square of side $S$. For a square to fit inside a rectangle of width $W$ and height $H$, its side must satisfy $S \le W$ and $S \le H$. To maximize the area $S^2$, we choose the largest valid $S$:
$$S_{ij} = \min(\Delta x, \Delta y)$$

The global solution is:
$$\text{Result} = \max_{\substack{0 \le i < n \\ i < j < n}} (S_{ij}^2)$$

### 4. Complexity Calculation
We analyze the number of operations required to compute the global maximum.

**Time Complexity:**
The algorithm iterates through all unique pairs $(i, j)$ such that $0 \le i < j \le n-1$.
The total number of iterations $T(n)$ is determined by the sum:

$$T(n) = \sum_{i=0}^{n-2} \sum_{j=i+1}^{n-1} C$$

where $C$ represents the constant number of arithmetic operations (min/max comparisons) performed inside the loop.
Expanding the sum:
$$T(n) = C \cdot [(n-1) + (n-2) + \dots + 1]$$
$$T(n) = C \cdot \frac{n(n-1)}{2}$$

Since the dominant term is $n^2$:
$$T(n) \in \Theta(n^2)$$

**Space Complexity:**
We allocate a fixed set of integer variables (`i_rectangle_x_start`, `max_overlap_x_start`, etc.) to store coordinates. No auxiliary arrays are used.
$$S(n) \in \Theta(1)$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
            int i_rectangle_x_start, i_rectangle_x_finish, j_rectangle_x_start, j_rectangle_x_finish;
            int i_rectangle_y_start, i_rectangle_y_finish, j_rectangle_y_start, j_rectangle_y_finish;
            int max_overlap_x_start, min_overlap_x_finish, max_overlap_y_start, min_overlap_y_finish;
            long long finalResult = 0;
            for (int i = 0; i < n; i++) {
                i_rectangle_x_start = bottomLeft[i][0];
                i_rectangle_x_finish = topRight[i][0];
                i_rectangle_y_start = bottomLeft[i][1];
                i_rectangle_y_finish = topRight[i][1];
                for (int j = i + 1; j < n; j++) {
                    j_rectangle_x_start = bottomLeft[j][0];
                    j_rectangle_x_finish = topRight[j][0];
                    j_rectangle_y_start = bottomLeft[j][1];
                    j_rectangle_y_finish = topRight[j][1];
                        max_overlap_x_start = max(i_rectangle_x_start, j_rectangle_x_start);
                        min_overlap_x_finish = min(i_rectangle_x_finish, j_rectangle_x_finish);

                        max_overlap_y_start = max(i_rectangle_y_start, j_rectangle_y_start);     
                        min_overlap_y_finish = min(i_rectangle_y_finish, j_rectangle_y_finish);
                        int squareSide = min ((min_overlap_x_finish - max_overlap_x_start),
                                              (min_overlap_y_finish - max_overlap_y_start));
                        if (squareSide <= 0)
                            continue;
                        finalResult = max((long long) (squareSide), finalResult);
                        
                }
            }
            return finalResult * finalResult;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).
