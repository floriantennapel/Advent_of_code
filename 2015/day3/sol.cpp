#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct HashTup
{
    size_t operator()(const pair<int, int>& p) const {
        return p.first ^ p.second;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const unordered_map<char, pair<int, int>> dirs = {{'^', {0, 1}}, {'v', {0, -1}}, {'>', {1, 0}}, {'<', {-1, 0}}}; 
    unordered_set<pair<int, int>, HashTup> visited;
    
    string input;
    cin >> input;

    // part 1
    pair<int, int> pos(0, 0);
    visited.insert(pos);
    for (char c : input) {
        auto[a, b] = dirs.at(c);
        pos.first  += a;
        pos.second += b;
        visited.insert(pos);
    }
    cout << visited.size() << '\n';

    // part 2
    vector<pair<int, int>> poss = {{0, 0}, {0, 0}};
    visited = {};
    visited.insert({0, 0});
    int p = 0;
    for (char c : input) {
        auto[a, b] = dirs.at(c); 
        poss[p].first  += a;
        poss[p].second += b;
        visited.insert(poss[p]);
        p = (p + 1) % 2;
    }
    cout << visited.size() << '\n';
}
