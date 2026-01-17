class Solution {
public:
    vector<int> twoSumBrute(vector<int>& nums, int target) {
        vector<int> solution(2);
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    solution[0] = i;
                    solution[1] = j;
                }
            }
        }
        return solution;
    }


    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> solution(2);
        unordered_map<int,int> initialNumbers;
        int n = nums.size();
        int mapIndex;
        for (int i = 0; i < n; i++) {
            initialNumbers[nums[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            nums[i] = target-nums[i];
            if (initialNumbers.contains(nums[i])) {
                mapIndex = initialNumbers[nums[i]];
                if (i != mapIndex){
                    solution[0] = i;
                    solution[1] = mapIndex;
                }
            }
        }
        return solution;
    }

};