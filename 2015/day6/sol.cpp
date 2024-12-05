#include <cstring>
#include <iostream>
#include <vector>
#include <array>
#include <tuple>

using namespace std;

enum Instr { ON, OFF, TOGGLE };

long sum_lights(const array<array<char, 1000>, 1000>& lights)
{
    long count = 0;
    for (auto& r : lights) {
        for (int c : r)
            count += c;
    }
    return count;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<tuple<Instr, pair<int, int>, pair<int, int>>> instructions;

    int a,b,c,d;
    string line, word;
    char ign;
    while (cin >> word) {
        Instr instr;
        if (word == "turn") {
            cin >> word; 
            instr = (word == "on") ? ON : OFF;
        } else
            instr = TOGGLE;
        cin >> a >> ign >> b >> word >> c >> ign >> d; 
        instructions.push_back({instr, {a, b}, {c, d}});
    }

    array<array<char, 1000>, 1000> lights = {};

    // part 1
    for (auto&[instr, first, last] : instructions) {
        for (int r = first.first; r <= last.first; r++) {
            if (instr != TOGGLE) 
                memset(lights[r].data()+first.second, (instr == ON) ? 1 : 0, (last.second - first.second + 1));
            else {
                for (int c = first.second; c <= last.second; c++)
                    lights[r][c] = !lights[r][c];
            }
        }
    }
    cout << sum_lights(lights) << '\n';

    // part 2
    lights = {};
    for (auto&[instr, first, last] : instructions) {
        for (int r = first.first; r <= last.first; r++) {
            for (int c = first.second; c <= last.second; c++) {
                if (instr == ON)
                    lights[r][c]++;
                else if (instr == OFF)
                    lights[r][c] = max(--lights[r][c], '\0');
                else
                    lights[r][c] += 2;
            }
        }
    }
    cout << sum_lights(lights);
}
