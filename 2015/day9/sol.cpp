#include <climits>
#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
using Graph = unordered_map<string, vector<pair<string, int>>>;

pair<int, int> tsp(const Graph& g, const string& current, unordered_set<string> visited)
{
    if (g.size() == visited.size())
        return {0, 0};

    int lo = INT_MAX;
    int hi = INT_MIN;
    for (auto&[next, dist] : g.at(current)) {
        if (visited.find(next) != end(visited))
            continue;
        visited.insert(next);
        auto[ret_lo, ret_hi] = tsp(g, next, visited); 
        ret_lo += dist;
        ret_hi += dist;

        visited.erase(next);
        if (ret_lo < lo)
            lo = ret_lo;
        if (ret_hi > hi)
            hi = ret_hi;
    }
    return {lo, hi};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Graph graph;

    string a, b, ign;
    int dist;
    while (cin >> a >> ign >> b >> ign >> dist) {
        graph[a].emplace_back(b, dist);
        graph[b].emplace_back(a, dist);
    } 

    // part 1
    int lo = INT_MAX;
    int hi = INT_MIN;
    for (const auto&[loc, _] : graph) {
        auto[ret_lo, ret_hi] = tsp(graph, loc, {loc});
        if (ret_lo < lo)
            lo = ret_lo;
        if (ret_hi > hi)
            hi = ret_hi;
    }
    cout << lo << '\n';
    cout << hi << '\n';
}
