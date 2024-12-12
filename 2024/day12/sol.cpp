#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
using Grid = vector<string>;

const vector<pair<int, int>> dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

template<typename T>
bool in_range(const T& grid, int r, int c)
{
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
}

int current_plot = 0;
pair<long, long> fences(const Grid& grid, vector<vector<int>>& partitions, pair<int, int> start)
{
    if (partitions[start.first][start.second])
        return {0, 0};

    ++current_plot;

    char current = grid[start.first][start.second];

    queue<pair<int, int>> q;
    q.emplace(start.first, start.second);
    
    long perimeter = 0;
    long area = 0;
    while (!q.empty()) {
        auto[r, c] = q.front();
        q.pop();
        if (partitions[r][c])
            continue;
        partitions[r][c] = current_plot;
        ++area;
        perimeter += 4;
        for (auto[dr, dc] : dirs) {
            int nr = r+dr;
            int nc = c+dc;
            if (in_range(grid, nr, nc) && grid[nr][nc] == current) {
                --perimeter;
                q.emplace(nr, nc);
            } 
        }
    }
    return {area, perimeter};
}

int count_sides(const vector<vector<int>>& partitions, int part)
{
    int sum = 0;
    for (int d = -1; d <= 1; d += 2) {
        for (int i = 0; i < partitions.size(); i++) {
            bool hor  = false;
            bool vert = false;
            for (int j = 0; j < partitions[0].size(); j++) {
                if ((!in_range(partitions, i+d, j) || partitions[i+d][j] != part) && partitions[i][j] == part)
                    hor = true;
                else if (hor) {
                    ++sum;
                    hor = false;
                }
                if ((!in_range(partitions, j, i+d) || partitions[j][i+d] != part) && partitions[j][i] == part)
                    vert = true;
                else if (vert) {
                    ++sum;
                    vert = false;
                }

            }
            if (hor)  ++sum;
            if (vert) ++sum;
        }
    }

    return sum;
}

int main()
{
    Grid grid;
    string line;
    while (cin >> line)
        grid.push_back(line);
    
    vector<vector<int>> partitions(grid.size(), vector<int>(grid[0].size())); 
    long sum_p1 = 0;
    long sum_p2 = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            auto[a, p] = fences(grid, partitions, {i, j});
            sum_p1 += a*p;
            if (a) {
                int sides = 0;
                sides += count_sides(partitions, partitions[i][j]);
                sum_p2 += a*sides;
            }
        }
    }

    cout << sum_p1 << '\n';
    cout << sum_p2 << '\n';
}
