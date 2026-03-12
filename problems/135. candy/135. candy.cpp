class Solution {
public:
    int candy(vector<int>& ratings) {
        if (ratings.size() == 1) return 1;
        int n = ratings.size();
        vector<int> inDegreePriority(n);
        vector<vector<int>> adjency(n);
        for (int i = 0; i< n; i++) {
            if (i > 0 && ratings[i] > ratings[i-1]){
                adjency[i-1].push_back(i);
                inDegreePriority[i]++;
            }
            if (i < n-1 && ratings[i] > ratings[i+1]) {
                adjency[i+1].push_back(i);
                inDegreePriority[i]++;
            }
        }

        queue<int> topoQ;
        for(int i = 0; i < n; i++){
            if (inDegreePriority[i] == 0) {
                topoQ.push(i);
            }
        }
        vector<int> candies(n,1);
        while(!topoQ.empty()) {
            int fromNode = topoQ.front();
            topoQ.pop();
            for(auto to : adjency[fromNode]){
                inDegreePriority[to]--;
                candies[to] = max(candies[fromNode] + 1, candies[to]);
                if (inDegreePriority[to] == 0) {
                    topoQ.push(to);
                }
            }
        }
    int totalCandies = 0;
    for(int i = 0; i < n; i++) {
        totalCandies+=candies[i];
    }
    return totalCandies;
    }
};