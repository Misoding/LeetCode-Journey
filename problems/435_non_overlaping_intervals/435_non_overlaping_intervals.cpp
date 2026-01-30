class Solution {
public:
    static bool customCompare(vector<int> &a, vector<int> &b) {
        return a[1] < b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int res = -1;
        sort(intervals.begin(), intervals.end(), customCompare);
        vector<int> lastInterval = intervals[0];
        for(auto interval: intervals) {
            if (lastInterval[1] > interval[0]){
                res++;
            } else {
                lastInterval = interval;
            }
        }
        return res;
    }
};