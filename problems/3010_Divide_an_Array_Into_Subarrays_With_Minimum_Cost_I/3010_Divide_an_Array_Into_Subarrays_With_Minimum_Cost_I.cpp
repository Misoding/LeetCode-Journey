class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int n = nums.size();
        int minL = INT_MAX, minR = INT_MAX;
        for(int i = 1; i < n; i++) {
            if (nums[i] < minL) {
                minR = minL;
                minL = nums[i];
            } else if (nums[i] < minR) {
                minR = nums[i];
            }
        }
        return nums[0] + minL + minR;
    }
};