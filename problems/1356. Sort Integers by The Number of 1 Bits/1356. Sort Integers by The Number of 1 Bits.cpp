class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        unordered_map<int, vector<int>> bit_map;
        for(int i = 0; i < 32; i++) {
            bit_map[i] = vector<int>(0);
        }
        for(int i = 0; i<arr.size();i++){
            int c = 0;
            int tmp = arr[i];
            while(tmp) {
                c += (tmp & 1);
                tmp >>=1;
            }
            bit_map[c].push_back(arr[i]);
        }
        vector<int> res;
        for(int i = 0; i < 32; i++) {
            sort(bit_map[i].begin(), bit_map[i].end());
            for(int j = 0; j < bit_map[i].size();j++) {
                res.push_back(bit_map[i][j]);
            }
        }
        return res;
    }
};