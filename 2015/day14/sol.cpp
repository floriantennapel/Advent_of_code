#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <regex>

using namespace std;

int main()
{
    regex re(R"(\d+)");
    vector<array<int, 3>> reindeer;
    sregex_iterator it_end;

    string line;
    int s, d, r;
    while (getline(cin, line) && line != "") {
        sregex_iterator it(line.begin(), line.end(), re);
        reindeer.emplace_back();
        auto& b = reindeer.back();
        for (int i = 0; i < 3; i++) {
            b[i] = stoi((it++)->str()); 
        }
    }

    int secs = 2503;

    // original part 1 solution had O(1) runtime
    // A full simulation is needed for part 2, so I could just as well remove the old solution
    int n = reindeer.size();
    vector<int> dists(n);
    vector<int> points(n);
    for (int  sec = 0; sec < secs; sec++) {
        for (int j = 0; j < n; j++) {
            auto&[s, d, r] = reindeer[j];
            if ((sec % (d+r)) < d)
                dists[j] += s;
        }
        int m = ranges::max(dists);
        for (int j = 0; j < n; j++) {
            if (dists[j] == m)
                points[j]++;
        }
    }
    cout << ranges::max(dists) << '\n';
    cout << ranges::max(points) << '\n';
}
