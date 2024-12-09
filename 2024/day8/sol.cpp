#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdint>

using namespace std;
using ul = uint64_t;

ul to_key(const pair<int, int>& p)
{
    return ((ul)p.first << 32) | p.second;
}

bool in_range(const pair<int, int>& p, const vector<string>& grid)
{
    auto[r, c] = p;
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
}

int main()
{
    vector<string> grid;
    string line;
    while (cin >> line)
        grid.push_back(line);
    
    unordered_map<char, vector<pair<int, int>>> antenna;
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            char ch = grid[r][c];
            if (ch != '.')
                antenna[ch].emplace_back(r, c);
        }
    }

    // ul just pair of two ints: a << 32 | b
    unordered_set<ul> anti_p1;
    unordered_set<ul> anti_p2;

    for (auto&[_, poss] : antenna) {
        for (int i = 0; i < poss.size()-1; i++) {
            for (int j = i+1; j < poss.size(); j++) {
                auto& a = poss[i];
                auto& b = poss[j];
                int dr = b.first - a.first;
                int dc = b.second - a.second;
                pair<int, int> front{b.first+dr, b.second+dc};
                pair<int, int> back{a.first-dr, a.second-dc};
                
                // part 1
                if (in_range(front, grid)) anti_p1.insert(to_key(front));
                if (in_range(back, grid))  anti_p1.insert(to_key(back));

                // part 2
                anti_p2.insert(to_key(a));
                anti_p2.insert(to_key(b));
                for (; in_range(front, grid); front.first += dr, front.second += dc)
                    anti_p2.insert(to_key(front));
                for (; in_range(back, grid); back.first -= dr, back.second -= dc)
                    anti_p2.insert(to_key(back));
            }
        }
    }
    cout << anti_p1.size() << '\n';
    cout << anti_p2.size() << '\n';
}
