class Solution {
public:
    void generateStrings(const int& n, int pos,string& pair, vector<string>& pairs) {
        if (pos >= n) {
            pairs.push_back(pair);
            return;
        }
        for(int i = 'a'; i <= 'c'; i++) {
            if (pos > 0 && i == pair[pos-1]){
                continue;
            }
            pair[pos] = i;
            generateStrings(n,pos+1, pair, pairs);
        }
        return;
    }
    string getHappyString(int n, int k) {
        vector<string> pairs;
        string dummy(n, 'a');
        generateStrings(n,0, dummy, pairs);
        if(pairs.size() >= k) {
            return pairs[k-1];
        }
        return "";

    }
};