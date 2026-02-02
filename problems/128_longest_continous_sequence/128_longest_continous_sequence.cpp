class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int maxSeq = 0, curSeq = 0;
        unordered_set<int> allNums;
        for(int i = 0; i < nums.size(); i++) {
            allNums.insert(nums[i]);
        }
        for(int i = 0; i < nums.size(); i++) {
            curSeq = 0;
            auto it = allNums.find(nums[i]);
            if (it != allNums.end()) {
                allNums.erase(*it);
                curSeq++;
                int l = 1, r = 1;
                while (true) {
                    auto lowerEl = allNums.find(nums[i] - l);
                    if (lowerEl != allNums.end()) {
                        l++;
                        curSeq++;
                        allNums.erase(*lowerEl);
                    } else {
                        break;
                    }
                }
                while (true) {
                    auto higherEl = allNums.find(nums[i] + r);
                    if (higherEl != allNums.end()) {
                        r++;
                        curSeq++;
                        allNums.erase(*higherEl);
                    } else {
                        break;
                    }
                }
                maxSeq = max(maxSeq, curSeq);
            }
        }
        return maxSeq;
    }
};