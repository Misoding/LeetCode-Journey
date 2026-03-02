class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> maxRightIndexes;
        for(int i = 0; i<n; i++) {
            int rightPos = -1;
            for(int r = n-1; r>=0;r--){
                if(grid[i][r]) {
                    rightPos = r;
                    break;
                }
            }
            maxRightIndexes.push_back(rightPos);
        }
        int steps = 0;
        for (int i = 0; i < n; i++) {
            int j = i;
            while (j < n && maxRightIndexes[j] > i) {
                j++;
            }
            if (j >= n) return -1;
            while(j>i) {
                swap(maxRightIndexes[j], maxRightIndexes[j-1]);
                swap(grid[j], grid[j-1]);
                steps++;
                j--;
            }
        }       
        return steps;


    }
};