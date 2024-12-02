#include <iostream>
#include <numeric>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

bool is_safe(vector<int> report) // copy needs to happen here
{
    adjacent_difference(begin(report), end(report), begin(report));
    return all_of(++begin(report), end(report), [](int d) { return d >= 1 && d <= 3; })
        || all_of(++begin(report), end(report), [](int d) { return d <= -1 && d >= -3; });
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> reports;
    string line; 
    int d;
    while (getline(cin, line)) {
        vector<int> report;
        stringstream stream(line);
        while (stream >> d)
            report.push_back(d);
        reports.push_back(move(report));
    }

    // part 1
    long sum = 0;
    for (const auto& r : reports)
        if (is_safe(r)) 
            ++sum;
    cout << sum << '\n';

    // part 2
    sum = 0;
    for (auto& r : reports) {
        bool found = false;
        if (is_safe(r))
            found = true;
        for (auto it = begin(r); !found && it != end(r); it++) {
            int tmp = *it;
            it = r.erase(it);
            found = is_safe(r);
            it = r.insert(it, tmp);
        }
        if (found)
            ++sum;
    }
    cout << sum << '\n';
}
