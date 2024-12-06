#include <boost/container_hash/hash.hpp>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

const vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

template<>
struct std::hash<pair<int, int>>
{
    size_t operator()(const pair<int, int>& p) const
    {
        size_t seed = p.first;
        boost::hash_combine(seed, p.second);
        return seed;
    }
};

template<>
struct std::hash<pair<pair<int, int>, int>>
{
    size_t operator()(const pair<pair<int, int>, int>& p) const
    {
        size_t seed = p.first.first;
        boost::hash_combine(seed, p.first.second);
        boost::hash_combine(seed, p.second);
        return seed;
    }
};

bool is_valid(const pair<int, int>& p, const vector<string>& map)
{
    auto[r, c] = p;
    return r >= 0 && r < map.size() && c >= 0 && c < map[0].size();
}

bool has_loop(const vector<string>& map, pair<int, int> pos)
{
    unordered_set<pair<pair<int, int>, int>> visited;
    int dir_ind = 0;
    pair<int, int> next;
    while (is_valid(pos, map)) {
        if (visited.find({pos, dir_ind}) != visited.end())
            return true;
        visited.insert({pos, dir_ind});    
        auto[r, c] = dirs[dir_ind];
        next = {pos.first + r, pos.second + c};
        if (is_valid(next, map) && map[next.first][next.second] == '#')
            dir_ind = (dir_ind+1) % 4;
        else
            swap(pos, next);
    }
    return false;
}

pair<int, int> find_start(const vector<string>& map)
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == '^')
                return {i, j};
        }
    }
    return {-1, -1};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> map;
    string line;
    while (getline(cin, line) && line != "") {
        map.push_back(line);
    }

    pair<int, int> start_pos = find_start(map);

    long count = 0;
    unordered_set<pair<int, int>> visited;
    unordered_set<pair<int, int>> added;
    int dir_ind = 0;
    pair<int, int> pos{start_pos};
    pair<int ,int> next;
    while (true) {
        visited.insert(pos);    
        auto& d = dirs[dir_ind];
        next = {pos.first + d.first, pos.second + d.second};
        if (!is_valid(next, map))
            break;

        if (map[next.first][next.second] == '#')
            dir_ind = (dir_ind+1) % 4;
        else {
            if (added.find(next) == added.end()) {
                map[next.first][next.second] = '#';    
                if (has_loop(map, start_pos))
                    ++count;
                map[next.first][next.second] = '.';
                added.insert(next);
            }
            swap(pos, next);
        }
    }
    cout << visited.size() << '\n';
    cout << count << '\n';
}
