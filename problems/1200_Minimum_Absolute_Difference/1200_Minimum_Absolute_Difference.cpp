class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        vector<vector<int>> result;
        unordered_map<int, vector<int>> sum_indexes;
        int min_sum = INT_MAX;
        for(int i = 0; i < arr.size()-1; i++) {
            int sum = arr[i+1] - arr[i];
            if (sum < min_sum) {
                vector<int> current_sum_indexes;
                current_sum_indexes.push_back(i);
                sum_indexes[sum] = current_sum_indexes;
                min_sum = sum;
            } else if (sum == min_sum){
                sum_indexes[min_sum].push_back(i);
            }
        }
        for(int index : sum_indexes[min_sum]) {
            result.push_back({arr[index], arr[index+1]});
        }
        return result;
    }
};