class Solution {
public:
    struct heap_element {
        int node;
        int weight;
        bool operator>(const heap_element& oElement) const {
            return weight > oElement.weight;
        }
    };
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> graph(n);
        for (auto edge : edges) {
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];
            graph[from].push_back(std::make_pair(to, weight));
            graph[to].push_back(std::make_pair(from, 2 * weight));
        }
        vector<int> distanceTo(n, INT_MAX);
        vector<bool> visited(n,false);

        priority_queue<heap_element, vector<heap_element>, greater<heap_element>> minHeap;
        minHeap.push({0,0});
        distanceTo[0] = 0;
        while (!minHeap.empty()) {
            int node = minHeap.top().node;
            minHeap.pop();
            if (visited[node]) {
                continue;
            }
            visited[node] = true;
            for (auto toNode : graph[node]) {
                int toId = toNode.first;
                int toWeight = toNode.second;
                if (distanceTo[node] + toWeight < distanceTo[toId]) {
                    distanceTo[toId] = distanceTo[node] + toWeight;
                    minHeap.push({toId, distanceTo[toId]});
                }
            }
        }
        if (distanceTo[n-1] == INT_MAX) return -1;
        return distanceTo[n-1];
    }
};