class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        int currentStreak = 0;
        int maxStreak = 0;
        for(int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(currentStreak);
                currentStreak = 0;
            } else {
                if (st.empty()) {
                    currentStreak = 0;
                } else {
                    currentStreak = 1 + currentStreak + st.top();
                    st.pop();
                    maxStreak = max(currentStreak, maxStreak);
                }
            }
        }        
        return maxStreak * 2;
    }
};