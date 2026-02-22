class Solution {
public:
    int binaryGap(int n) {
        string binRep = "";
        while(n){
            char x = (n & 1) + '0';
            binRep+=x;
            n>>=1;
        }
        int l = 0, r = 0;
        int longestDist = 0;
        cout<<binRep<<endl;
        int repLen = binRep.length();
        int i = 0;
        while(i < repLen) {
                if (binRep[i] == '1') {
                    l = i;
                    break;
                }
                i++;
        }
        for(i = i + 1; i<repLen; i++) {
            while(i < repLen) {
                if (binRep[i] == '1') {
                    r = i;
                    break;
                }
                i++;
            }
            longestDist = max(longestDist, r-l);
            l = r;
        }
        return longestDist;
    }
};