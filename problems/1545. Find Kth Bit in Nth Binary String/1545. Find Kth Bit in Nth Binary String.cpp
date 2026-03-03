class Solution {
public:
     
    string invertString(string s) {
        string cpy = s;
        for(int i = 0; i<s.length();i++){
            cpy[i] = cpy[i] == '0' ? '1' : '0';
        }
        return cpy;
    }
    char findKthBit(int n, int k) {
        string startString = "0";
        for(int i = 0; i<n-1; i++) {
            string res = invertString(startString);
            reverse(res.begin(), res.end());
            startString = startString + "1" + res;
        }
        return startString[k-1];
    }
};