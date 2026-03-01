class Solution {
public:
    int minPartitions(string n) {
        int max_num = 0;
        for(int i = 0; i<n.length();i++){
            max_num = max(n[i]-'0', max_num);
        }
        return max_num;
        
    }
};