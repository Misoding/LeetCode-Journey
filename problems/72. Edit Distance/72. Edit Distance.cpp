class Solution {
public:
    int minDist_Helper(string w1, string w2, int idx1, int idx2, vector<vector<int>> &dp) {
        if (idx1 == w1.length()) return w2.length() - idx2;
        if (idx2 == w2.length()) return w1.length() - idx1;
        if (dp[idx1][idx2] != -1) return dp[idx1][idx2];
        if (w1[idx1] == w2[idx2]) {
            dp[idx1][idx2] = minDist_Helper(w1,w2,idx1+1,idx2+1, dp);
            return dp[idx1][idx2];}
        dp[idx1][idx2] =  1 + min(
            minDist_Helper(w1,w2,idx1+1,idx2+1, dp),
            min(
                minDist_Helper(w1,w2,idx1,idx2+1, dp),
                minDist_Helper(w1,w2,idx1+1,idx2, dp)
            )
        );
        return dp[idx1][idx2];
    }
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.length()+1, vector<int>(word2.length()+1, -1));
        return minDist_Helper(word1,word2,0,0, dp);
    }
};