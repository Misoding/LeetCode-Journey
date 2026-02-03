class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int,int>> cars(position.size());
        stack<double> timeLeft;
        for(int i = 0; i < position.size(); i++) {
            cars[i] = std::make_pair(position[i], speed[i]);
        }
        sort(cars.rbegin(), cars.rend());
        timeLeft.push((double) (target - cars[0].first) / cars[0].second);
        for(int i = 1; i < cars.size();i++){
            double time = (double)(target - cars[i].first) / cars[i].second;
            if (timeLeft.size() >= 1){
                double lastFleetCar = timeLeft.top();
                if (time > lastFleetCar) {
                    timeLeft.push(time);
                }
            }
        }
        return timeLeft.size();
    }
};