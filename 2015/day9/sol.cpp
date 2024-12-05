#include <climits>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <bitset>

#define BITS 10

using namespace std;
using Graph = unordered_map<string, vector<pair<string, int>>>;

unordered_map<string, int> to_id;
unordered_map<int, string> to_name;

pair<int, int> tsp(const Graph& g, const string& current, bitset<BITS> visited)
{
    if (g.size() == visited.count())
        return {0, 0};
    int b = to_id[current];

    int lo = INT_MAX;
    int hi = INT_MIN;
    for (auto&[next, dist] : g.at(current)) {
        int nb = to_id[next];
        if (visited[nb])
            continue;
        visited[nb] = true;
        auto[ret_lo, ret_hi] = tsp(g, next, visited); 
        ret_lo += dist;
        ret_hi += dist;

        visited[nb] = false;
        if (ret_lo < lo) lo = ret_lo;
        if (ret_hi > hi) hi = ret_hi;
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

    int i = 0;
    for (auto&[loc, _] : graph) {
        to_id[loc] = i;
        to_name[i++] = loc; 
    }

    int lo = INT_MAX;
    int hi = INT_MIN;
    bitset<BITS> start_set{};
    for (const auto&[loc, _] : graph) {
        int id = to_id[loc];
        start_set[id] = true;
        auto[ret_lo, ret_hi] = tsp(graph, loc, start_set);
        start_set[id] = false;
        if (ret_lo < lo) lo = ret_lo;
        if (ret_hi > hi) hi = ret_hi;
    }
    cout << lo << '\n';
    cout << hi << '\n';
}
