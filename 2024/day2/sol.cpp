#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>

using namespace std;

template<class It>
bool is_safe(It first, It last, bool dampened = true)
{
    auto prev = *first++;
    for (; first != last; first++) {
        int diff = *first - prev;  
        if (diff < 1 || diff > 3) {
            if (!dampened) {
                dampened = true;
                continue;
            }
            return false;
        }
        prev = *first;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> reports;
    string line; 
    int d;
    while (getline(cin, line) && !line.empty()) {
        vector<int> report;
        stringstream stream(line);
        while (stream >> d)
            report.push_back(d);
        reports.push_back(move(report));
    }

    // part 1
    long sum = 0;
    for (auto& r : reports) {
        if (is_safe(begin(r), end(r)) || is_safe(rbegin(r), rend(r)))
            ++sum;
    }
    cout << sum << '\n';

    // part 2
    sum = 0;
    for (auto& r : reports) {
        if (is_safe(begin(r), end(r), false) || is_safe(rbegin(r), rend(r), false) ||
            is_safe(++begin(r), end(r))|| is_safe(++rbegin(r), rend(r)))
            ++sum;
    }
    cout << sum << '\n';
}
