class Solution {
public:
    string makeLargestSpecial(string s) {
        vector<string> blocks;
        int openCounter = 0, begin = 0;
        for(int i = 0;i < s.length(); i++) {
            if (s[i] == '1'){
                openCounter++;
            } else {
                openCounter--;
            }
            if (openCounter == 0) {
                string internBracket = s.substr(begin + 1, i - begin - 1);
                string orderedIntern = "1" + makeLargestSpecial(internBracket) + "0";
                blocks.push_back(orderedIntern);
                begin = i + 1;
            }
        }
        sort(blocks.begin(), blocks.end(), greater<string>());
            string orderedString = "";
            for(int j = 0; j < blocks.size(); j++) {
                orderedString += blocks[j];
            }
            return orderedString;
    }
};