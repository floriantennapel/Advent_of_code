#include <climits>
#include <iostream>
#include <regex>
#include <vector>
#include <array>

using namespace std;

template<typename T>
long quadrant_count(int x1, int y1, int x2, int y2, const T& grid)
{
    int count = 0;
    for (int i = y1; i <= y2; i++) {
        for (int j = x1; j <= x2; j++)
            count += grid[i][j];
    } 
    return count;
}

template<typename T>
long safety_factor(const T& space)
{
    int height = space.size();
    int width = space[0].size();
    long ret = 1;
    int cw = width / 2;
    int ch = height / 2;
    ret *= quadrant_count(0, 0, cw-1, ch-1, space);
    ret *= quadrant_count(0, ch+1, cw-1, height-1, space);
    ret *= quadrant_count(cw+1, 0, width-1, ch-1, space);
    ret *= quadrant_count(cw+1, ch+1, width-1, height-1, space);
    return ret;
}

template<typename T>
void print_tree(const T& grid)
{
    for (int i = 0; i < grid.size(); i++) {
        for (bool d : grid[i])
            cout << (d ? '#' : ' ');
        cout << '\n';
    }
}

template<typename T>
vector<vector<int>> make_space(const T& robots, int width, int height, int steps)
{
    vector<vector<int>> space(height, vector<int>(width));
    for (auto& r : robots) {
        int px = (r[0] + r[2]*steps + 10000L*width) % width;
        int py = (r[1] + r[3]*steps + 10000L*height) % height;
        space[py][px] += 1;
    }
    return space;
}

int main()
{
    regex num(R"(-?\d+)");
    sregex_iterator it_end;
    vector<array<int, 4>> robots;
    string line;
    while (getline(cin, line) && line != "") {
        robots.emplace_back();
        auto& b = robots.back();
        sregex_iterator it(line.begin(), line.end(), num);
        for (int i = 0; it != it_end; it++, i++)
            b[i] = stoi(it->str());
    }

    int width = 101;
    int height = 103;

    // part 1
    cout << safety_factor(make_space(robots, width, height, 100)) << '\n';

    // part 2
    // New solution, I wanted to check if maybe part 1 was related to part 2, and it was :D
    // for old solution look at commit history
    pair<int, long> best{-1, LONG_MAX};
    for (int i = 0; i < 10000; i++) {
        long safety = safety_factor(make_space(robots, width, height, i));
        if (safety < best.second) {
            best = {i, safety};
        }
    }

    //print_tree(make_space(robots, width, height, best.first));
    cout << best.first << '\n';
}
