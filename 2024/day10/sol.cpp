#include <boost/container_hash/hash.hpp>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;
using Grid = vector<vector<int>>;
using Res = pair<unordered_set<pair<int, int>>, int>;

const vector<pair<int, int>> dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; 

template<>
struct std::hash<pair<int, int>>
{
    size_t operator()(const pair<int, int>& p) const
    {
        size_t seed = 0;
        boost::hash_combine(seed, p.first);
        boost::hash_combine(seed, p.second);
        return seed;
    }
};

bool in_range(const Grid& grid, const pair<int, int>& pos)
{
    auto[r, c] = pos;
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
}

unordered_map<pair<int, int>, Res> memo;
Res count_trails(const Grid& grid, const pair<int, int>& pos)
{
    int h = grid[pos.first][pos.second];
    if (h == 9)
        return {{pos}, 1}; 

    auto res = memo.find(pos);
    if (res != memo.end()) {
        return res->second;
    }

    Res ret;
    for (auto[dr, dc] : dirs) {
        pair<int, int> next{pos.first+dr, pos.second+dc};
        if (in_range(grid, next) && grid[next.first][next.second] == h+1) {
            auto[ends, count] = count_trails(grid, next);
            ret.first.merge(ends);
            ret.second += count;
        }
    }

    memo[pos] = ret;
    return ret;
}

int main()
{
    Grid grid;
    string line;
    while (cin >> line) {
        grid.emplace_back();
        ranges::transform(line, back_inserter(grid.back()), [](char c) {return c - '0';});
    }

    long sum_p1 = 0;
    long sum_p2 = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 0) {
                auto[ends, count] = count_trails(grid, {i, j});
                sum_p1 += ends.size(); 
                sum_p2 += count;
            }
        }
    }
    cout << sum_p1 << '\n';
    cout << sum_p2 << '\n';
}
