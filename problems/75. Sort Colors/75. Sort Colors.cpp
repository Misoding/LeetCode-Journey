class Solution {
public:
    int partition(vector<int>& nums, int l, int r) {
        int selectedNum = nums[r];
        int index = l-1;
        for (int j = l; j <= r-1; j++) {
            if (nums[j] <= selectedNum) {
                index++;
                swap(nums[index], nums[j]);
            }
        }
        swap(nums[index+1], nums[r]);
        return (index+1);
    }
    int partition_helper(vector<int>& nums, int l, int r){
        srand(time(NULL));
        int random = l + rand() % (r - l);
        swap(nums[random], nums[r]);
        return partition(nums, l, r);
    }
    void quickSort(vector<int>& nums, int l, int r) {
        if (l < r) {
            int idx = partition_helper(nums, l, r);
            quickSort(nums, l, idx-1);
            quickSort(nums, idx+1, r);
        }
    }
    void sortColors(vector<int>& nums) {
        quickSort(nums, 0, nums.size()-1);
    }
};