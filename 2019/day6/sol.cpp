#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
typedef unordered_map<string, pair<long, string>> Tree;
typedef unordered_map<string, vector<string>> Graph;

long count_orbits(Tree& tree, const string& current) 
{
    if (current == "COM")
        return 0;
    auto&[count, parent] = tree[current];
    if (count != 0)
        return count;
    tree[current].first = count_orbits(tree, parent) + 1;
    return tree[current].first;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Tree tree;
    Graph graph;

    string a, b;
    while (getline(cin, a, ')')) {
        getline(cin, b, '\n'); 
        tree[b].second = a;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }

    // part 1
    long sum = 0;
    for (auto&[key, rest] : tree)
        sum += count_orbits(tree, key);
    cout << sum << '\n';

    // part 2
    unordered_set<string> visited;
    queue<pair<string, int>> q;
    q.emplace("YOU", -1);
    while (!q.empty()) {
        auto&[current, dist] = q.front();
        q.pop();
        if (current == "SAN") {
            cout << dist-1 << '\n';
            break;
        }
        if (visited.find(current) != visited.end())
            continue;
        visited.insert(current);
        for (const string& next : graph[current])
            q.emplace(next, dist + 1);
    }
}
