class Solution {
public:
struct hardworker {
    long long actionCost;
    int workerTime;
    int idx;
    bool operator<(const hardworker& worker2) const {
        return actionCost > worker2.actionCost;
    }
};
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        priority_queue<hardworker> minHeap;
        long long maxTime = 0;
        for(int i = 0; i < workerTimes.size();i++){
            minHeap.push({workerTimes[i], workerTimes[i], 1});
        }
        while(mountainHeight) {
            mountainHeight--;
            hardworker cheap = minHeap.top();
            minHeap.pop();
            maxTime = max(cheap.actionCost, maxTime);
                        cheap.idx++;
            cheap.actionCost = (long long)cheap.workerTime * (((long long)cheap.idx * (cheap.idx+1))/2);
            minHeap.push(cheap);
        }
        return maxTime;
        
    }
};