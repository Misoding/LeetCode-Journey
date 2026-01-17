class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        long reversedInt = 0;
        int tmpNum = 0, initialNumber = x;
        while (x) {
            reversedInt*=10;
            tmpNum = x % 10;
            reversedInt += tmpNum;
            x/=10;
        }
        if ((long) initialNumber == reversedInt) {
            return true;
        }
        return false;
    }
};