class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        int primeCounter = 0;
        int primes[] = {2,3,5,7,11,13,17,19};
        for(int i = left; i <= right; i++) {
            int count = 0;
            int tmp = i;
            while (tmp) {
                count += tmp&1;
                tmp>>=1;
            }
            for(int j = 0; j < 8; j++) {
                if (primes[j] == count) {
                    primeCounter++;
                }
            }
        }
        return primeCounter;
    }
};