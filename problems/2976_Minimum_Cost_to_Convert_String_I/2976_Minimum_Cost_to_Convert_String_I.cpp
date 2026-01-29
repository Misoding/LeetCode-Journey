#define ll long long
class Solution {
public:
    struct heap_element {
        ll node;
        ll weight;
        bool operator>(const heap_element& oElement) const {
            return weight > oElement.weight;
        }
    };
    vector<vector<pair<ll, ll>>> fullGraph;
    const long long cmpMax = LONG_LONG_MAX - 1000000000;
    ll distTo[26][26];
    vector<bool> visited;

    void dijkstra(ll startNode) {
        priority_queue<heap_element, vector<heap_element>, greater<heap_element>> minHeap;
        minHeap.push({startNode, 0});
        while (!minHeap.empty()) {
            auto node = minHeap.top();
            minHeap.pop();
            ll distCost = node.weight;
            ll destId = node.node;
            if (distCost > distTo[startNode][destId]) continue;
            for (auto neighNode : fullGraph[destId]) {
                ll to = neighNode.first;
                ll price = neighNode.second;
                if (distTo[startNode][destId] + price < distTo[startNode][to]) {
                    distTo[startNode][to] = distTo[startNode][destId] + price;
                    minHeap.push({to, distTo[startNode][to]});
                }
            }
        }
    }
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        vector<vector<pair<ll, ll>>> graph = vector<vector<pair<ll, ll>>>(26, vector<pair<ll,ll>>());
        visited = vector<bool>(26, false);
        for(int i = 0; i < 26; i++) {
            for(int j = 0; j < 26; j ++) {
                if (i == j) {
                    distTo[i][j] = 0;
                } else {
                    distTo[i][j] = cmpMax;
                }
            }
        }
        for(int i = 0; i < original.size(); i++) {
            ll origId = original[i] - 'a';
            ll destId = changed[i] - 'a';
            ll pathCost = (ll) cost[i];
            graph[origId].push_back(std::make_pair(destId, pathCost));
        }
        fullGraph = graph;
        ll resCost = 0;
        for (int i = 0; i < source.size(); i++) {
            ll from = (ll) source[i] - 'a';
            ll to = (ll) target[i] - 'a';
            if (from == to) {
                continue;
            }
            if (!visited[from]) {
                dijkstra(from);
                visited[from] = true;
            }
            if (distTo[from][to] == cmpMax) {
                return -1;
            } else {
                resCost += distTo[from][to];
            }
        }
        return resCost;
    }
};