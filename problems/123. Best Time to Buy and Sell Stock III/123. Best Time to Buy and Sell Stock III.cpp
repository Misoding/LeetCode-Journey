class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 1) return 0;
        vector<int> left_sell(n,0);
        vector<int> right_sell(n,0);
        int max_price = prices[0];
        for(int i = 1; i < n; i++){
            max_price = min(max_price, prices[i]);
            left_sell[i] = max(left_sell[i-1], -max_price + prices[i]);
        }
        max_price = prices[n-1];
        for(int i = n-2; i>=0; i--) {
            max_price = max(prices[i], max_price);
            right_sell[i] = max(right_sell[i+1], -prices[i] + max_price);
        }
        int max_profit = 0;
        for(int i = 0; i < n; i++) {
            max_profit =  max((right_sell[i]+left_sell[i]), max_profit);
        }
        return max_profit;
    } 
};