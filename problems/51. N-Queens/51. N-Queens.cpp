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