class Solution {
public:
    bool checkOnesSegment(string s) {
        int blocks = 0;
        for(int i = 0; i < s.length();i++) {
            if (s[i] == '1') blocks++;
            while(i < s.length() && s[i] == '1') {
                i++;
            }
        }
        if (blocks == 1) return true;
        return false;
    }
};