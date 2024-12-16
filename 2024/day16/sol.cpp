#include <iostream>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <boost/container_hash/hash.hpp>

using namespace std;
using Pos = pair<int, int>;

const vector<Pos> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct PQElem
{
    long dist;
    Pos pos;
    int dir;
    vector<PQElem*> preds;

    bool operator()(const PQElem* left, const PQElem* right) const 
    {
        return left->dist > right->dist;
    }
};


template<>
struct std::hash<pair<Pos, int>>
{
    size_t operator()(const pair<Pos, int>& p) const
    {
        size_t seed = 0;
        boost::hash_combine(seed, p.first.first);
        boost::hash_combine(seed, p.first.second);
        boost::hash_combine(seed, p.second);
        return seed;
    }
};

template<>
struct std::hash<Pos>
{
    size_t operator()(const Pos& p) const
    {
        size_t seed = 0;
        boost::hash_combine(seed, p.first);
        boost::hash_combine(seed, p.second);
        return seed;
    }
};

unordered_set<Pos> path;
void bt(const PQElem* current)
{
    path.insert(current->pos);
    if (current->preds.empty())
        return;
    for (PQElem* p : current->preds) {
        bt(p); 
    }
}

int main()
{
    vector<PQElem> nodes{};
    nodes.reserve(1000000);
    vector<string> grid;
    string line;
    while (cin >> line)
        grid.push_back(line);
    
    grid[1][grid[0].size()-2] = '.';
    grid[grid.size()-2][1] = '.';

    priority_queue<PQElem*, vector<PQElem*>, PQElem> q;     
    unordered_map<pair<Pos, int>, pair<long, vector<PQElem*>*>> visited;

    Pos target{1, grid[0].size()-2};

    nodes.push_back({0, {grid.size()-2, 1}, 0, {}});
    q.push(&nodes.back());
    while (!q.empty()) {
        PQElem* e = q.top();
        q.pop();

        if (e->pos == target) {
            cout << e->dist << '\n';
            bt(e);
            break;
        }

        pair<Pos, int> key{e->pos, e->dir};
        auto vis_res = visited.find(key);
        if (vis_res != visited.end()) {
            if (vis_res->second.first == e->dist)
                vis_res->second.second->push_back(e);
            continue;
        }
        visited[key] = {e->dist, &e->preds};

        auto[dr, dc] = dirs.at(e->dir);
        Pos next{e->pos.first+dr, e->pos.second+dc};
        if (grid[next.first][next.second] != '#') {
            nodes.push_back({e->dist+1, next, e->dir, {e}});
            q.push(&nodes.back());
        }

        for (int nd = -1; nd <= 1; nd += 2) {
            nodes.push_back({e->dist + 1000, e->pos, (e->dir+nd + 4)%4, {e}});
            q.push(&nodes.back());
        }
    }
    cout << path.size() << '\n';
}
