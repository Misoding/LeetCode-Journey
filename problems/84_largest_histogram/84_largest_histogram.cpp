class Solution {
public:
    struct stackBar {
        int barHeight;
        int barWidth;
    };
    int largestRectangleArea(vector<int>& heights) {
        // area = max(min(cur_bar_min_height, stack_last_el_height) * (stack_last_el_width + 1), cur_bar_min_height)
        // fail on [5 9 9]
        stack<stackBar> bars;
        int maxRectangle = 0, n = heights.size();
        heights.push_back(0);
        for(int i = 0; i < n+1; i++) {
           stackBar currentBar = {heights[i], 1};
           int maxWidth = 0;
           while (!bars.empty() && bars.top().barHeight >= currentBar.barHeight) {
                stackBar lastBar = bars.top();
                bars.pop();
                maxWidth += lastBar.barWidth;
                maxRectangle = max(maxRectangle, maxWidth * lastBar.barHeight);
           }
           currentBar.barWidth +=maxWidth;
           bars.push(currentBar);
        }
        return maxRectangle;
    }
};