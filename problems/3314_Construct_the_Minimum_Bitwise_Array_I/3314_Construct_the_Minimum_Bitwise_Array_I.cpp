class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            if (nums[i] & 1){
                int new_bit_mask = (nums[i] + 1) & ~nums[i];
                new_bit_mask>>=1;
                ans[i] = nums[i] - new_bit_mask;
            } else{
                ans[i] = -1;
            }
        }
        return ans;
    }
};