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
void print_tree(const T& grid, int steps)
{
    for (int i = 0; i < grid.size(); i++) {
        for (bool d : grid[i])
            cout << (d ? '#' : ' ');
        cout << '\n';
    }
    cout << "STEPS: " << steps << '\n';
    cout << "\n\n";
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
    vector<vector<int>> space(height, vector<int>(width));
    for (auto& r : robots) {
        int px = (r[0] + r[2]*100 + 100L*width) % width;
        int py = (r[1] + r[3]*100 + 100L*height) % height;
        space[py][px] += 1;
    }
    
    long mul = 1;

    int cw = width / 2;
    int ch = height / 2;
    mul *= quadrant_count(0, 0, cw-1, ch-1, space);
    mul *= quadrant_count(0, ch+1, cw-1, height-1, space);
    mul *= quadrant_count(cw+1, 0, width-1, ch-1, space);
    mul *= quadrant_count(cw+1, ch+1, width-1, height-1, space);
    cout << mul << '\n';

    // part 2
    // this was a bit tricky, and running the code will not reveal the answer
    // Looking at the output I noticed that there were two repeating patterns, once points lined up to a column, and once when the points line up to a row
    // My quess whas that the final answer is the step when these patterns intersect.
    

    // code to show grids
    /* for (int i = 0;; i++) {
        vector<vector<bool>> space(height, vector<bool>(width));
        for (auto& r : robots) {
            int px = (r[0] + r[2]*i + 10000L*width) % width;
            int py = (r[1] + r[3]*i + 10000L*height) % height;
            space[py][px] = true;
        }
        print_tree(space, i);
        this_thread::sleep_for(200ms);
    } */

    // For my input I found a column line at steps: 13, 114 ... giving the function 13 + 101x
    // and horizontal lines at: 79, 182 ... giving the function 79 + 103y 


    // As far as I know we cannot solve 13 + 101x = 79 + 103y directly,
    // however, we do know that x and y must be integers
    // 
    // solving for y we get: y = (101x - 66) / 103
    // from this, we can find the x that makes 101x - 66 be divisible by 103
    
    /* for (int x = 1;; x++) {
        if ((101*x - 66) % 103 == 0) {
            cout << x << '\n';
            break;
        }
    } */

    // giving x = 70 and therefore y = 68
    // solving both equations we get:
    
    // 13 + 101*70 = 7083
    // 79 + 103*68 = 7083
    
    // A quick check with the printing-code above from i = 7083 to 7084 showed that this step contained a christmas tree
    // This was also the accepted answer
}
