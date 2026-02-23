class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_set<string> subStrings;
        for(int i = 0; i + k <= s.length(); i++){
            subStrings.insert(s.substr(i, k));
        }
        if(subStrings.size() == pow(2,k)) {
            return true;
        }
        return false;
    }
};