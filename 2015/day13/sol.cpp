#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    unordered_map<string, unordered_map<string, int>> relations;
    vector<string> people;
    string line, a, b, sign, ign;
    int happiness;
    while (getline(cin, line) && line != "") {
        stringstream stream(line);
        stream >> a;
        stream >> ign >> sign >> happiness;
        for (int i = 0; i < 6; i++)
            stream >> ign;
        stream >> b;
        if (!relations.contains(a))
            people.push_back(a);
        relations[a].emplace(b.substr(0, b.size()-1), sign == "gain" ? happiness : -happiness);
    } 

    // add line for part 2
    // people.emplace_back("self");
    
    int optimal = INT_MIN;
    while(next_permutation(people.begin()+1, people.end())) {
        int seating = 0;
        for (int i = 0; i < people.size(); i++) {
            int before = (i - 1 + people.size()) % people.size();
            int after = (i + 1) % people.size();
            string& person = people[i];
            seating += relations[person][people[before]];
            seating += relations[person][people[after]];
        }
        optimal = max(optimal, seating);
    }
    cout << optimal << '\n';
}
