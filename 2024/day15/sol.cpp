#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;
using Pos = pair<int, int>;

const unordered_map<char, Pos> dirs{
    {'<', {0, -1}}, {'>', {0, 1}},
    {'^', {-1, 0}}, {'v', {1, 0}}
};

class Warehouse
{
public:
    Warehouse(string& input, bool pt2 = false) : pt2{pt2} 
    {
        string line;
        stringstream stream(input);
        for (int i = 0; getline(stream, line) && line != ""; i++) {
            if (!pt2) {
                grid.push_back(line);
                for (int j = 0; j < line.size(); j++) {
                    if (grid[i][j] == '@') {
                        grid[i][j] = '.';
                        pos = {i, j};
                    }
                }
            } else {
                grid.emplace_back();
                auto& b = grid.back();
                for (int j = 0; j < line.size(); j++) {
                    char c = line[j];
                    switch (c) {
                    case 'O':
                        b += "[]";
                        break;
                    case '@':
                        b += "..";
                        pos = {i, j*2};
                        break;
                    default:
                        b.push_back(c);
                        b.push_back(c);
                    }
                }
            }
        }
    }

    void move(char dir) 
    {
        auto& d = dirs.at(dir);
        Pos next{pos.first+d.first, pos.second+d.second};
        if (dir == '<' || dir == '>' || !pt2) {
            if (move_p1(next, d))
                pos = next;
        } else {
            if (wide_vert_check(next, d, false)) {
                wide_vert_check(next, d, true);
                pos = next;
            }
        }
    }

    long gps_sum()
    {
        long sum = 0;
        for (int i = 1; i < grid.size()-1; i++) {
            for (int j = 1; j < grid[0].size()-1; j++) {
                if (grid[i][j] == 'O' || grid[i][j] == '[')
                    sum += 100 * i + j;
            }
        }
        return sum;
    }
        
private:
    vector<string> grid;
    Pos pos;
    bool pt2;

    char at(const Pos& p)
    {
        return grid[p.first][p.second];
    }

    bool move_p1(const Pos& p, const Pos& dir) 
    {
        switch (at(p)) {
        case '#':
            return false;
        case '.':
            return true;
        }

        Pos next{p.first + dir.first, p.second + dir.second};
        if (move_p1(next, dir)) {
            grid[next.first][next.second] = at(p); 
            grid[p.first][p.second] = '.'; 
            return true;
        }
        return false;
    }

    bool wide_vert_check(const Pos& p, const Pos& dir, bool move_blocks)
    {
        int r = p.first+dir.first;
        int dc;
        switch(at(p)) {
        case '.':
            return true;
        case '#':
            return false;
        case '[':
            dc = 1;
            break;
        case ']':
            dc = -1;
        }

        if (wide_vert_check({r, p.second}, dir, move_blocks) && wide_vert_check({r, p.second+dc}, dir, move_blocks)) {
            if (move_blocks) {
                grid[r][p.second] = at(p);
                grid[r][p.second+dc] = grid[p.first][p.second+dc];
                grid[p.first][p.second] = '.';
                grid[p.first][p.second+dc] = '.';
            }
            return true;
        }
        return false;
    }
};

int main()
{
    string dirs, line, grid;
    while (getline(cin, line) && line != "")
        grid += line + '\n';

    while (getline(cin, line) && line != "")
        dirs += line;

    Warehouse p1(grid);
    Warehouse p2(grid, true);

    for (char d : dirs) {
        p1.move(d);
        p2.move(d);
    }

    cout << p1.gps_sum() << '\n';
    cout << p2.gps_sum() << '\n';
}
