class Solution {
public:
    int concatenatedBinary(int n) {
        unsigned long long res = 1;
        unsigned long long modulo = 1e9 + 7;
        for(int i = 2; i <= n;i++){
            res = ((res << (32 - __builtin_clz(i))) | i) % modulo;
        }
        return res;
    }
};