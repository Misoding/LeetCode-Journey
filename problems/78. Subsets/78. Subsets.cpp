class Solution {
public:
    void formSubsets(vector<int>& initialArr, vector<int>& curSubset, vector<vector<int>>& res, int id) {
        if (id == initialArr.size()) {
            res.push_back(curSubset);
            return;
        }
        // include current element at index id
        curSubset.push_back(initialArr[id]);
        formSubsets(initialArr, curSubset, res, id+1);
        
        //don't include current element
        curSubset.pop_back();
        formSubsets(initialArr,curSubset,res,id+1);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> curSubset;
        formSubsets(nums, curSubset, res, 0);
        return res;
    }

};