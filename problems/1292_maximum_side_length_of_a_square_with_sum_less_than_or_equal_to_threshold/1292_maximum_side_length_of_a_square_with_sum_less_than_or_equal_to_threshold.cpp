class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = mat.size();
        int m = mat[0].size();
        int squareEdgeMax = min(n,m), squareEdgeMin = 1;
        int sqSum, end_sq_i, end_sq_j;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == 0) {
                    continue;
                }
                mat[i][j]+=mat[i][j-1];
            }
        }
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0){
                    continue;
                }
                mat[i][j] += mat[i-1][j];
            }
        }
        int resEdge = 0;
        while (squareEdgeMin <= squareEdgeMax) {
            int midEdge = squareEdgeMin + (squareEdgeMax - squareEdgeMin) / 2;
            bool valid = false;
            for(int i = 0; i <= n - midEdge; i++) {
                for (int j = 0; j <= m - midEdge; j++) {
                    end_sq_i = i + midEdge - 1;
                    end_sq_j = j + midEdge - 1;
                    sqSum = mat[end_sq_i][end_sq_j];
                    if (i > 0) {
                        sqSum -= mat[i-1][end_sq_j];
                    }
                    if (j > 0) {
                        sqSum -= mat[end_sq_i][j-1];
                    }
                    if (i > 0 && j > 0) {
                        sqSum += mat[i-1][j-1];
                    }
                    if (sqSum <= threshold) {
                        valid = true;
                        break;
                    }
                }
                if (valid) break;
            }
            if(valid) {
                resEdge = midEdge;
                squareEdgeMin = midEdge + 1;
            } else {
                squareEdgeMax = midEdge - 1;
            }
        }
        return resEdge;
    }
};