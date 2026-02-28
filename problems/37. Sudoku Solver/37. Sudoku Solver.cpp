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