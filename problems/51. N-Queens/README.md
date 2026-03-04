# Day 42: N-Queens

- **Difficulty:** Hard
- **Topics:** Array, Backtracking
- **LeetCode Link:** [N-Queens](https://leetcode.com/problems/n-queens/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.

Given an integer `n`, return all distinct solutions to the **n-queens puzzle**. You may return the answer in **any order**.

Each solution contains a distinct board configuration of the n-queens' placement, where `'Q'` and `'.'` both indicate a queen and an empty space, respectively.

**Example 1:**
Input: `n = 4`
Output: `[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]`

---

## 🏗️ Deep-Dive Implementation Strategy

The N-Queens problem is the standard benchmark for exact-cover problems solved via **Backtracking (Depth-First Search)**. The goal is to explore the decision space by placing one queen per row and pruning paths that lead to invalid board states.



### 1. State Space Traversal
The function `solveNQueensBack` traverses the board row by row (`y` variable). 
* If we successfully reach `y >= n`, it implies $N$ queens have been placed without conflicts. The current board state is appended to the results.
* For a given row `y`, we iterate through every column `i` from $0$ to $n-1$.
* If placing a queen at `(y, i)` is valid, we mutate the board (`table[y][i] = 'Q'`) and recurse to the next row (`y + 1`).
* **Backtrack:** If the recursion returns, we undo the mutation (`table[y][i] = '.'`) to explore the next column.

### 2. 8-Directional Validation
To ensure no two queens attack each other, the `checkGoodPosition` function verifies the lines of sight.
By utilizing direction arrays `OX` and `OY`, the algorithm acts like a raycaster, projecting lines in all 8 cardinal and ordinal directions. If any ray intersects an existing `'Q'`, the position is immediately invalidated.



---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the chessboard be a matrix $M \in \{Q, \cdot\}^{N \times N}$. We are looking for a set of coordinates $C = \{(r_0, c_0), (r_1, c_1), \dots, (r_{N-1}, c_{N-1})\}$ such that:
1.  $\forall i \neq j, \ r_i \neq r_j$ (No two queens share a row).
2.  $\forall i \neq j, \ c_i \neq c_j$ (No two queens share a column).
3.  $\forall i \neq j, \ |r_i - r_j| \neq |c_i - c_j|$ (No two queens share a diagonal).

The backtracking algorithm constructively enforces the row constraint by advancing the recursion depth exactly by 1 row at a time. The column and diagonal constraints are enforced by the `checkGoodPosition` raycasting validation.

### 2. Time Complexity Analysis

The first row has $N$ potential placements. The second row has at most $N-1$ valid placements, the third has at most $N-2$, leading to a bounded permutation space of $O(N!)$.
For each placement attempt, the `checkGoodPosition` function performs validation. Scanning 8 directions up to distance $N$ takes $O(N)$ operations.

$$
T(N) = \sum_{k=1}^{N!} O(N) = O(N \cdot N!)
$$

For small values of $N$ (e.g., $N \le 9$), $9! = 362,880$, making this brute-force with pruning highly efficient.

### 3. Space Complexity Analysis

The memory footprint consists of:
1.  **Board State:** A vector of strings occupying $\Theta(N^2)$ space.
2.  **Call Stack:** The maximum recursion depth is $N$, requiring $\Theta(N)$ frames.

Excluding the memory required to store the final solutions (which can be large depending on the number of valid configurations), the auxiliary space is dominated by the board matrix.

$$
S_{aux}(N) = \Theta(N^2)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    vector<int> OX;
    vector<int> OY;
    bool checkGoodPosition(int n, int y, int x, vector<string>& table){
        int new_x, new_y;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < n; j++) {
                new_x = x + j * OX[i];
                new_y = y + j * OY[i];
                if (new_x >= n || new_x < 0 || new_y < 0 || new_y >= n) break;
                if (table[new_y][new_x] != '.') return false;
            }
        }
        return true;
    }
    bool solveNQueensBack(int n, int y, int x, vector<string>& table, vector<vector<string>>& res){
        if (y >= n) {
            res.push_back(table);
            return true;
        }
        if (x >= n) return solveNQueensBack(n, y+1, 0, table, res);
        for(int i = x; i < n; i++) {
            if (checkGoodPosition(n, y, i, table)){
                table[y][i] = 'Q';
                solveNQueensBack(n,y+1,0, table, res);
                table[y][i] = '.';
            }
        }
        return false;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<int> x_axis = {1,1,1,0,-1,-1,-1,0};
        vector<int> y_axis = {1,0,-1,-1,-1,0,1,1};
        string initial = "";
                vector<vector<string>> res;
        for(int i  = 0; i<n;i++) {
         initial+=".";
        }
        vector<string> table(n, initial);
        cout<<table[0].size();
        OX = x_axis;
        OY = y_axis;
        solveNQueensBack(n,0,0,table, res);
        //res.push_back(table);
        return res;
    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).