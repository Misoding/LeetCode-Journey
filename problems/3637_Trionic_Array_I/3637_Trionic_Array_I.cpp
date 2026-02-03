class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int i = 0; int n = nums.size();
        if (n <= 3) return false;
        bool validArray = true;
        int s = -2000, q = -2000, p = -2000;
        while (i < n-1){
            if (!(nums[i+1] > nums[i])) {
                break;
            }
            i++;
        }
        if (i == 0) return 0;
        p = nums[i];
        while (i < n-1){
            if (!(nums[i+1] < nums[i])) {
                break;
            }
            i++;
        }
        q = nums[i];
        while (i < n-1){
            if (!(nums[i+1] > nums[i])) {
                break;
            }
            i++;
        }
        if (i == n-1 && nums[n-1] > q  && q < p && p > s) {
            return validArray;
        }
        return false;
    }
};