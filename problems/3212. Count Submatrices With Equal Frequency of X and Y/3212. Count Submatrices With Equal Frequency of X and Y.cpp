class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        vector<vector<uint64_t>> transformed(grid.size(), vector<uint64_t>(grid[0].size()));
        
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size();j++){
                uint64_t currentIntX = grid[i][j] == 'X' ? 1ULL : 0;
                uint64_t currentIntY = grid[i][j] == 'Y' ? 1ULL : 0;
                transformed[i][j] = (currentIntX << 32) | currentIntY;
                if (i > 0) transformed[i][j] += transformed[i-1][j];
                if (j > 0) transformed[i][j] += transformed[i][j-1];
                if (i > 0 && j > 0) transformed[i][j]-=transformed[i-1][j-1];
            }
        }
        int countSubMatrices = 0;
        for(int i = 0; i < grid.size();i++){
            for(int j = 0; j< grid[0].size(); j++) {
                if ((transformed[i][j] >> 32) == ((transformed[i][j]<<32)>>32) && (transformed[i][j]>>32) > 0) {
                    countSubMatrices++;
                }
            }
        }
        return countSubMatrices;
    }
};