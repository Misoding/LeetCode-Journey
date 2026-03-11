class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int squares = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j< m; j++) {
                if (matrix[i][j] == 1){
                    if (i > 0 && j > 0) {
                        matrix[i][j] = min(matrix[i-1][j-1], min(
                            matrix[i-1][j], matrix[i][j-1]
                        )) + 1;
                    }
                    squares += matrix[i][j];
                }
            }
        }
        return squares;
    }
};