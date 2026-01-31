class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int l = 0, r = letters.size() -1;
        int res = letters[0];
        while (l <= r) {
            int mid = l + (r-l) / 2;
            if (letters[mid] == target) {
                l = mid + 1;
            } else if (letters[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
                res = letters[mid];
            }
        }
        return res;
    }
};