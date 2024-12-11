#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;
using Aunts = vector<unordered_map<string, int>>;

int part1(const Aunts& aunts, const unordered_map<string, int> reqs)
{
    for (int i = 0; i < aunts.size(); i++) {
        if (ranges::all_of(aunts[i], [&](auto& p) {return reqs.at(p.first) == p.second;})) {
            return i+1; 
        }
    }
    return -1; 
}

int part2(const Aunts& aunts, const unordered_map<string, int> reqs)
{
    for (int i = 0; i < aunts.size(); i++) {
        bool match = true;
        for (auto&[prop, num] : aunts[i]) {
            if (prop == "cats" || prop == "trees") {
                if (reqs.at(prop) >= num) {
                    match = false;
                    break;
                }
            } else if (prop == "pomeranians" || prop == "goldfish") {
                if (reqs.at(prop) <= num) {
                    match = false;
                    break;
                }
            } else if (reqs.at(prop) != num) {
                match = false;
                break;
            }
        }
        if (match)
            return i+1;
    }
    return -1;
}

int main()
{
    Aunts aunts;
    string line, a, b;
    while (getline(cin, line) && line != "") {
        stringstream str(line);
        str >> a >> a;
        aunts.emplace_back();
        auto& last = aunts.back();
        while (str >> a >> b) {
            last[a.substr(0, a.size()-1)] = stoi(b); 
        }
    }

    unordered_map<string, int> requirements{
        {"children", 3}, {"cats",        7},
        {"samoyeds", 2}, {"pomeranians", 3},
        {"akitas",   0}, {"vizslas",     0},
        {"goldfish", 5}, {"trees",       3},
        {"cars",     2}, {"perfumes",    1}
    };

    cout << part1(aunts, requirements) << '\n';
    cout << part2(aunts, requirements) << '\n';
}
