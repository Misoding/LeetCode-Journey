class Solution {
public:
    int numSteps(string s) {
        int stepsLen = 0;
        deque<char> num(s.begin(), s.end());
        while(!(num.size() == 1 && num.front() == '1')) {
            char lastBit = num.back();
            stepsLen++;
            if (lastBit == '0') {
                num.pop_back();
            } else if(lastBit == '1') {
                bool carryBit = true;
                int i = num.size()-1;
                while(i >= 0 && carryBit) {
                    if (num[i] == '0') {
                        num[i] = '1';
                        carryBit=false;
                    } else if (num[i] == '1') {
                        num[i] = '0';
                    }
                    i--;
                }
                if (carryBit) {
                    num.push_front('1');
                    carryBit = false;
                }
            }

        }
        return stepsLen;

    }
};