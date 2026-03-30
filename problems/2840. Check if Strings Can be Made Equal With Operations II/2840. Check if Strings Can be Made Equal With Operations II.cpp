class Solution {
public:
    bool checkStrings(string s1, string s2) {
        if (s1.length() != s2.length()) return false;
        vector<int> s1_count_even(135, 0);
        vector<int> s1_count_odd(135, 0);
        vector<int> s2_count_even(135, 0);
       vector<int> s2_count_odd(135, 0);
        for(int i = 0; i<s1.length();i++) {
            if (i % 2) s1_count_odd[s1[i]-'a']++;
            else s1_count_even[s1[i] - 'a']++;
        }
        for(int i = 0; i<s2.length();i++) {
            if (i % 2) s2_count_odd[s2[i]-'a']++;
            else s2_count_even[s2[i] - 'a']++;
        }
        for(int i = 0; i < 135; i++) {
            if (s1_count_odd[i] != s2_count_odd[i] || s1_count_even[i] != s2_count_even[i]) return false;
        }
        return true;
    }
};