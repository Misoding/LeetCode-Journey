class Solution {
public:
    // long long multiply;
    // vector<vector<int>> dp;
    // vector<int> numVect;
    // int removal(int l, int r) {
    //     if(l >= r) {
    //         return 0;
    //     }
    //     if (dp[l][r] != -1) {
    //         return dp[l][r];
    //     }
    //     if ((long long) numVect[l] * multiply >= (long long) numVect[r]) {
    //         return 0;
    //     }
    //     int currentMin = 1e9;
    //     currentMin = min(currentMin, 1 +  removal(l+1, r));
    //     currentMin = min(currentMin, 1 + removal(l, r-1));
    //     dp[l][r] = currentMin;
    //     return currentMin;
    // }
    int minRemoval(vector<int>& nums, int k) {
        // max element <= k * min_el
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int minRemoves = INT_MAX;
        for(int i = 0; i < n; i++) {
            long long searchFor = (long long) nums[i] * k;
            auto found = upper_bound(nums.begin() + i, nums.end(), searchFor);
            int rightElements = distance(found, nums.end());
            minRemoves = min(minRemoves, rightElements + i);
        }
        return minRemoves;
    }
};