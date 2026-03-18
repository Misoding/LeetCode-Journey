#include <iostream>
#include <vector>

int main() {
    int n, in;
    cin>>n;
    vector<int> inputVector(n);
    vector<int> dp(n+1,0);
    for(int i = 0; i< n; i++) {
        cin>>inputVector[i];
    }

    dp[0] = inputVector[0];
    for(int i = 1; i < n; i++) {
        // dp[i] = max((dp[i-1] + inputVector[i]), inputVector[i]);
        //sau
        if (dp[i-1] < 0) {
            dp[i] = inputVector[i];
        } else {
            dp[i] = dp[i-1] + inputVector[i];
        }
    }
    return 0;
}