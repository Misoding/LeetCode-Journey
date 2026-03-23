class Solution {
public:
    int solveDp(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp){
        if(i < 0 || j < 0) {
            return INT_MAX;
        }
        if (i == 0 && j == 0) {
            return grid[i][j];
        }
        if (dp[i][j] != -1) return dp[i][j];
        int topStep = solveDp(grid, i-1, j, dp);
        int leftStep = solveDp(grid, i, j-1, dp);
        dp[i][j] = grid[i][j] + min(topStep, leftStep);
        return dp[i][j];
    }
    int minPathSum(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid.size()+1, vector<int>(grid[0].size()+1, -1));
        return solveDp(grid, grid.size()-1, grid[0].size()-1, dp);
    }
};