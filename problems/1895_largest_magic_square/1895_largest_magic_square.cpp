class Solution {
public:
    void calcRowPrefixSum(vector<vector<int>>& originalGrid,
                          vector<vector<int>>& row_grid,
                          int& m,
                          int& n) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0) {
                    row_grid[i][j] = originalGrid[i][j];
                    continue;
                }
                row_grid[i][j] = row_grid[i][j-1] + originalGrid[i][j];
            }
        }
    }
    void calcColumnPrefixSum(vector<vector<int>>& originalGrid,
                            vector<vector<int>>& column_grid,
                            int& m,
                            int& n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == 0) {
                    column_grid[j][i] = originalGrid[j][i];
                    continue;
                }
                column_grid[j][i] = column_grid[j-1][i] + originalGrid[j][i];
            }
        }
    }
    void calcPrincipalDiagonalSum(vector<vector<int>>& originalGrid,
                          vector<vector<int>>& principalDiagonal,
                          int& m,
                          int& n) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 || j == 0) {
                    principalDiagonal[i][j] = originalGrid[i][j];
                    continue;
                }
                principalDiagonal[i][j] = principalDiagonal[i-1][j-1] + originalGrid[i][j];
            }
        }
    }
    void calcSecondaryDiagonalSum(vector<vector<int>>& originalGrid,
                          vector<vector<int>>& secondaryDiagonal,
                          int& m,
                          int& n) {
        for (int i = 0; i < m; i++) {
           for (int j = n-1; j >= 0; j--) {
                if (j == n-1 || i == 0) {
                    secondaryDiagonal[i][j] = originalGrid[i][j];
                    continue;
                }
                secondaryDiagonal[i][j] = secondaryDiagonal[i-1][j+1] + originalGrid[i][j];
           }
        }
    }
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int squareDimension = min(m,n);
        int oneSum, prevRowSum, prevColSum;
        bool validSquare;
        vector<vector<int>> rowPrefixSum(m, vector<int>(n));
        vector<vector<int>> columnPrefixSum(m, vector<int>(n));
        vector<vector<int>> principalDiagonalSum(m, vector<int>(n));
        vector<vector<int>> secondaryDiagonal(m, vector<int>(n));

        calcRowPrefixSum(grid, rowPrefixSum, m, n);
        calcColumnPrefixSum(grid, columnPrefixSum, m, n);
        calcPrincipalDiagonalSum(grid, principalDiagonalSum, m, n);
        calcSecondaryDiagonalSum(grid, secondaryDiagonal, m, n);

        for (int edge = squareDimension; edge > 0; edge--) {
            for (int i = 0; i <= m - edge; i++) {
                for (int j = 0; j <= n - edge; j++) {
                    validSquare = true;
                    prevRowSum = 0;
                    if (j > 0) {
                        prevRowSum = rowPrefixSum[i][j-1]; 
                    }
                    oneSum = rowPrefixSum[i][j + edge-1] - prevRowSum;

                    for (int sqRow = 0; sqRow < edge; sqRow++) {
                        prevRowSum = 0;
                        if (j > 0) {
                            prevRowSum = rowPrefixSum[i + sqRow][j-1];
                        }
                        if (rowPrefixSum[i + sqRow][j + edge - 1] - prevRowSum != oneSum) {
                            validSquare = false;
                            break;
                        }
                    }
                    if (validSquare == false){
                        continue;
                    }
                    for (int sqCol = 0; sqCol < edge; sqCol++) {
                        prevColSum = 0;
                        if (i > 0) {
                            prevColSum = columnPrefixSum[i-1][j + sqCol];
                        }
                        if (columnPrefixSum[i + edge - 1][j + sqCol] - prevColSum != oneSum) {
                            validSquare = false;
                            break;
                        }
                    }
                    if (validSquare == false) {
                        continue;
                    }
                    int prevPrincipalSum = 0, prevSecondarySum = 0;
                    if (i != 0 && j != 0) {
                      prevPrincipalSum = principalDiagonalSum[i-1][j-1];
                    }
                    if (i != 0 && (j + edge) < n) {
                        prevSecondarySum = secondaryDiagonal[i-1][j+edge];
                    }
                    if (principalDiagonalSum[i + edge-1][j + edge-1] - prevPrincipalSum != oneSum ||
                        secondaryDiagonal[i + edge-1][j] - prevSecondarySum != oneSum ){
                            continue;
                        }
                    return edge;
                }
            }
        }
        return 1;
    }
};