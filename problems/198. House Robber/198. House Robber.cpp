class Solution {
public:
    int robHouse(vector<int>& nums, int idx, vector<int> &dp) {
        if (idx >= nums.size()) return 0;
        if (dp[idx] != -1) return dp[idx];
        int num = nums[idx];
        int robCurrent =  num + robHouse(nums, idx + 2, dp);
        int noRobCurrent = robHouse(nums, idx+1, dp);
        dp[idx] = max(robCurrent, noRobCurrent);
        return dp[idx];
    }
    int rob(vector<int>& nums) {
        vector<int> dp(nums.size(), -1);
        dp[nums.size()-1] =  robHouse(nums, 0, dp);
        return dp[nums.size() - 1];
    }
};