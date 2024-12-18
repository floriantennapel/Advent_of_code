#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <tuple>

using namespace std;
using ul = unsigned long; 

const vector<pair<int, int>> dirs{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool valid(int x, int y, int dim) 
{
    return x >= 0 && x < dim && y >= 0 && y < dim;
}

int bfs(const vector<vector<bool>>& grid)
{
    queue<tuple<int, int, int>> q;
    unordered_set<ul> visited;
    q.emplace(0, 0, 0);

    while (!q.empty()) {
        auto[x, y, d] = q.front();
        q.pop();

        if (grid[y][x])
            continue;

        if (y == grid.size()-1 && x == grid.size()-1) {
            return d;
        }
        
        ul key = ((ul)x << 32) | y;
        if (visited.contains(key)) {
            continue;
        }
        visited.emplace(key);

        for (auto[dx, dy] : dirs) {
            if (valid(x+dx, y+dy, grid.size()))
                q.emplace(x+dx, y+dy, d+1);
        }
    }

    return -1;
}

int main()
{
    int x, y;
    char ign;

    int dim = 71;
    vector<vector<bool>> grid(dim, vector<bool>(dim));

    int p1_time = 1024;
    bool start_p2 = false;
    for (int i = 1; cin >> x >> ign >> y; i++) {
        grid[y][x] = true;
        if (i == p1_time) {
            cout << bfs(grid) << '\n';
            start_p2 = true;
            continue;
        }
        if (start_p2 && bfs(grid) == -1) {
            cout << x << ',' << y << '\n';
            break;
        }
    }
}
