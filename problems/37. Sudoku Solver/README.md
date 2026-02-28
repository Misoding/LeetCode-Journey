# Day 38: Sudoku Solver

- **Difficulty:** Hard
- **Topics:** Array, Backtracking, Matrix
- **LeetCode Link:** [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:
1. Each of the digits `1-9` must occur exactly once in each row.
2. Each of the digits `1-9` must occur exactly once in each column.
3. Each of the digits `1-9` must occur exactly once in each of the 9 `3x3` sub-boxes of the grid.

The `'.'` character indicates empty cells.

---

## 🏗️ Deep-Dive Implementation Strategy

Sudoku is an exact cover problem, famously solved using **Backtracking (Depth-First Search)**. The algorithm explores the decision tree of possible digit placements, abandoning (backtracking) a path as soon as it determines that the current placement violates Sudoku rules.



### 1. Validation Logic (`validate` function)
Before placing a digit $d$ at coordinates $(x, y)$, we must ensure local consistency:
* **Row & Column Check:** We iterate $i$ from $0$ to $8$. If `board[x][i] == d` or `board[i][y] == d`, the placement is invalid.
* **Sub-box Check:** The grid is divided into nine $3 \times 3$ sub-boxes. To find the top-left coordinate $(r, c)$ of the sub-box containing $(x, y)$, we use integer division and modulo arithmetic:
  * `r = x - x % 3`
  * `c = y - y % 3`
  We then iterate over the $3 \times 3$ block starting at $(r, c)$ to check for duplicates.

### 2. State Space Search (`recursiveSolver` function)
The solver traverses the matrix cell by cell (left to right, top to bottom):
1.  **Row Transition:** If $y \ge 9$, move to the next row: `x + 1`, $y = 0$.
2.  **Termination:** If $x \ge 9$, we have successfully filled all rows. Return `true`.
3.  **Skip Pre-filled Cells:** If `board[x][y] != '.'`, skip to `y + 1`.
4.  **Backtracking Core:** Iterate through characters `'1'` to `'9'`.
    * If `validate()` is true, place the character.
    * Recurse to the next cell. If the recursive call returns `true`, propagate the success upwards.
    * If the recursive call fails (returns `false`), **backtrack**: revert the cell to `'.'` and try the next digit.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the board be a matrix $B \in \{1..9, \emptyset\}^{9 \times 9}$. We define a partial assignment state $S$.
The transition function attempts to map $\emptyset \to d \in \{1..9\}$ such that constraints $C_{row}$, $C_{col}$, and $C_{box}$ hold.
If a state $S$ has no valid transitions and contains $\emptyset$, it is a dead end (leaf node), triggering a rollback to the parent state $S_{parent}$.

### 2. Time Complexity Analysis

Let $m$ be the number of empty cells on the board (where $m \le 81$).
For each empty cell, we have a maximum of 9 possible branches. Therefore, the absolute upper bound on the number of operations is $O(9^m)$.
However, the `validate` function aggressively prunes the search space. The actual number of states visited is exponentially smaller than $9^{81}$, but for formal Big-O classification, the upper bound is dictated by the branching factor.
Validation takes strictly $\Theta(1)$ time (9 row checks + 9 col checks + 9 box checks = 27 constant operations).

$$
T(m) = O(9^m)
$$

### 3. Space Complexity Analysis

The auxiliary space is determined exclusively by the maximum depth of the call stack. Since we process exactly one cell per recursive depth level, the maximum depth is $m$ (the number of empty cells).
Because the board size is fixed ($9 \times 9$), $m$ is bounded by a constant ($81$).

$$
S(m) = O(m) \implies S(81) = \Theta(1)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    bool validate(vector<vector<char>>& board, int x, int y, int character) {
        for(int i = 0; i< 9; i++) {
            if (board[x][i] == character) return false;
            if (board[i][y] == character) return false;
        }
        int r = x - x % 3, c = y - y % 3;
        for(int i = 0; i<3; i++) {
            for(int j = 0; j<3; j++) {
                if(board[r + i][c + j] == character) return false;
            }
        }
        return true;
    }
    bool recursiveSolver(vector<vector<char>>& board, int x, int y) {
        if (x >= 9) return true;
        if (y >=9 ) return recursiveSolver(board, x+1, 0);
        if (board[x][y] != '.') return recursiveSolver(board, x, y+1);
        for(int i = '1'; i <= '9'; i++) {
            if (validate(board, x, y, i)) {
                board[x][y] = i;
                if (recursiveSolver(board, x, y+1)) return true;
                board[x][y] = '.';
            }
        }
        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
         recursiveSolver(board, 0,0);
    }
};
```

---


### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find the full collection of solutions and formal documentation in my [**GitHub Repository**](../../README.md).