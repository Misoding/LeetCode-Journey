class Solution {
public:
    int solveMemo(vector<int>& prices, vector<vector<int>>& dp, int i, int canBuy) {
        if (i >= prices.size()){
            return 0;
        }
        if (dp[i][canBuy] != -1) {
            return dp[i][canBuy];
        }
        if (canBuy){
            int buyEl = -prices[i] + solveMemo(prices, dp, i+1, 0);
            int skip = solveMemo(prices, dp, i+1, 1);
            dp[i][canBuy] = max(buyEl, skip);
        } else {
            int sellEl = prices[i] + solveMemo(prices, dp, i+2, 1);
            int skip = solveMemo(prices, dp, i+1, 0);
            dp[i][canBuy] = max(sellEl, skip);
        }
        return dp[i][canBuy];
    }
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2, -1));
        return solveMemo(prices, dp, 0, true);
    }
};