class Solution {
public:
    bool palindromeCheck(string s){
        int i = 0;
        int n = s.length();
        while(i < n && s[i] == s[n-i-1]){
            i++;
        }
        if (i < n) return false;
        return true;
    }
    void solvePalindromes(int begin, string s, vector<string> &currentBuffer, vector<vector<string>> &res) {
        if (begin == s.length()){
            res.push_back(currentBuffer);
            return;
        }
        for(int i = begin; i < s.length(); i++) {
            string currentPalindrome = s.substr(begin, i-begin+1);
            if (palindromeCheck(currentPalindrome)) {
                currentBuffer.push_back(currentPalindrome);
                solvePalindromes(i+1, s, currentBuffer, res);
                currentBuffer.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> tempBuffer;
        solvePalindromes(0, s, tempBuffer, res);
        return res;
    }
};