#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <tuple>

using namespace std;
using ul = unsigned long; 

const vector<pair<int, int>> dirs{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

constexpr ul to_key(int x, int y) 
{ 
    return ((ul)x << 32) | y; 
}

bool valid(int x, int y, int dim) 
{
    return x >= 0 && x < dim && y >= 0 && y < dim;
}

pair<int, unordered_set<ul>> bfs(const vector<vector<bool>>& grid)
{
    unordered_map<ul, ul> preds;
    queue<tuple<int, int, int, ul>> q;
    q.emplace(0, 0, 0, 0);

    while (!q.empty()) {
        auto[x, y, d, pred] = q.front();
        q.pop();

        if (grid[y][x])
            continue;

        if (y == grid.size()-1 && x == grid.size()-1) {
            unordered_set<ul> path{to_key(x, y)}; 
            for (ul p = pred; p != 0; p = preds[p])
                path.insert(p);
            path.insert(0);

            return {d, move(path)};
        }
        
        ul key = to_key(x, y);
        if (preds.contains(key)) {
            continue;
        }
        preds[key] = pred;

        for (auto[dx, dy] : dirs) {
            if (valid(x+dx, y+dy, grid.size()))
                q.emplace(x+dx, y+dy, d+1, key);
        }
    }

    return {-1, {}};
}

int main()
{
    int x, y;
    char ign;

    int dim = 71;
    vector<vector<bool>> grid(dim, vector<bool>(dim));

    unordered_set<ul> current_path;
    int p1_time = 1024;
    bool start_p2 = false;

    for (int i = 1; cin >> x >> ign >> y; i++) {
        grid[y][x] = true;

        // part 1
        if (i == p1_time) {
            auto[dist, path] = bfs(grid);
            current_path = move(path);
            cout << dist << '\n';
            start_p2 = true;
            continue;
        }

        // part 2
        if (start_p2 && current_path.contains(to_key(x, y))) {
            auto[dist, path] = bfs(grid);
            if (dist == -1) {
                cout << x << ',' << y << '\n';
                break;
            }
            current_path = move(path);
        }
    }
}
