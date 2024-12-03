#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    cin >> line;
    vector<int> mapped;
    ranges::transform(line, back_inserter(mapped), [](char c) {return c == '(' ? 1 : -1;});
    cout << accumulate(begin(mapped), end(mapped), 0) << '\n';

    partial_sum(begin(mapped), end(mapped), begin(mapped));
    cout << (ranges::find(mapped, -1) - begin(mapped) + 1) << '\n';
}
