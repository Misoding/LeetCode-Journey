class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> maxArr;
        int l = 0, r = 0;
        multiset<int> window;
        for(int i = 0; i < nums.size(); i++) {
            if (r - l < k) {
                if (r < nums.size()) {
                    window.insert(nums[r]);
                }
                r++;
            }
            if (r-l == k) {
                maxArr.push_back(*(window.rbegin()));
                window.erase((window.find(nums[l])));
                l++;
            }
        }
        return maxArr;
    }
};