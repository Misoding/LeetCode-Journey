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