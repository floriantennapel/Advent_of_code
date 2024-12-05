#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

bool is_valid(const vector<bitset<100>>& rules, const vector<int>& update)
{
    bitset<100> seen;
    for (int u : update) {
        if ((rules[u] & seen).any())
            return false; 
        seen[u] = true;
    }
    return true;
}

void sort(const vector<bitset<100>>& rules, vector<int>& update)
{
    // A good sorting algorithm would require precomputing a topoligical sort of all rules
    // Insertion sort was a bit easier to implement, and every update is very short so runtime doesn't really matter
    bitset<100> added; 
    added[update[0]] = true;
    for (int i = 1; i < update.size(); i++) {
        int current = update[i];
        bitset<100> before(added);
        for (int j = i; (rules[current] & before).any(); j--) {
            swap(update[j], update[j-1]);
            before[update[j]] = false;
        }
        added[current] = true;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<bitset<100>> rules(100);
    vector<vector<int>> updates;
    
    string line;
    int a, b;
    char ign;
    while (getline(cin, line) && line != "") {
        stringstream stream(line);
        stream >> a >> ign >> b;
        rules[a][b] = true;
    }

    while (getline(cin, line) && line != "") {
        stringstream stream(line);
        vector<int> lv;
        stream >> a;
        lv.push_back(a); 
        while (stream >> ign >> a)
            lv.push_back(a);
        updates.push_back(move(lv));
    }

    long sum_p1 = 0;
    long sum_p2 = 0;
    for (auto& update : updates) {
        if (is_valid(rules, update))
            sum_p1 += update[update.size() / 2];
        else {
            sort(rules, update);
            sum_p2 += update[update.size() / 2];
        }
    }
    cout << sum_p1 << '\n';
    cout << sum_p2 << '\n';
}
