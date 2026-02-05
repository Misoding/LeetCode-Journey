class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        vector<int> res(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            int finalIdx;
            int toCommit = nums[i];
            if (toCommit < 0) {
                finalIdx = i + (toCommit % n);
                if (finalIdx < 0) {
                    res[i] = nums[n+finalIdx];
                } else {
                    res[i] = nums[finalIdx];
                }
            } else {
                finalIdx = i + toCommit;
                    res[i] = nums[finalIdx %(n)];
            }
        }
        return res;
    }
};