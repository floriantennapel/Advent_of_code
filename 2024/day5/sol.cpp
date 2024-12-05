#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

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

    auto cmp = [&](int a, int b) {return !rules[b][a];};

    int sum1 = 0;
    int sum2 = 0;
    for (auto& u : updates) {
        if (ranges::is_sorted(u, cmp))
            sum1 += u[u.size() / 2];
        else {
            ranges::sort(u, cmp);
            sum2 += u[u.size() / 2];
        }
    }
    cout << sum1 << '\n';
    cout << sum2 << '\n';
}
