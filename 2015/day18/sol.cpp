#include <iostream>
#include <vector>

using namespace std;

class Lights
{
public:
    Lights(bool pt2 = false) : pt2{pt2}
    {
        string line;
        while (cin >> line) {
            grid.emplace_back();
            auto& b = grid.back();
            for (char c : line)
                b.push_back(c == '#');
        } 
        buf = vector<vector<bool>>(grid.size(), vector<bool>(grid[0].size()));
    }

    void step()
    {
        if (pt2) 
            set_corners();
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                int count = count_neighbors(i, j);  
                buf[i][j] =  count == 3 || (grid[i][j] && count == 2);
            }
        }
        swap(grid, buf);
        if (pt2) 
            set_corners();
    }

    int count_lights()
    {
        int sum = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                sum += grid[i][j]; 
            }
        }
        return sum;
    }

private:
    vector<vector<bool>> grid;
    vector<vector<bool>> buf;
    bool pt2;

    bool in_range(int r, int c)
    {
        return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
    }

    int count_neighbors(int r, int c)
    {
        int sum = 0;
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0)
                    continue;
                if (in_range(r+dr, c+dc) && grid[r+dr][c+dc])
                    ++sum;
            }
        }
        return sum;
    }

    void set_corners()
    {
        for (int r = 0; r < grid.size(); r += grid.size()-1) {
            for (int c = 0; c < grid[0].size(); c += grid[0].size()-1)
                grid[r][c] = true;
        }
    }
};

int main()
{
    Lights lights;

    for (int i = 0; i < 100; i++)
        lights.step();
    cout << lights.count_lights() << '\n';
}
