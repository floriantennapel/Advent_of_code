#include <iostream>
#include <numeric>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    long lo, hi;
    char c;
    cin >> lo >> c >> hi;
    vector<int> diffs(20);

    int p1_sum = 0;
    int p2_sum = 0;
    for (long i = lo; i <= hi; i++) {
        string s = to_string(i);
        auto diff_end = adjacent_difference(begin(s), end(s), begin(diffs));
        if (all_of(begin(diffs), diff_end, [](char d) {return d >= 0;})) {
            if (any_of(begin(diffs), diff_end, [](char d) {return d == 0;}))
                ++p1_sum;

            int same_count = 0;
            bool p2 = false;
            for (auto diff_it = begin(diffs); diff_it != diff_end; diff_it++) {
                if (*diff_it == 0)
                    ++same_count;
                else {
                    if (same_count == 1)
                        p2 = true;
                    same_count = 0;
                }
            }
            if (same_count == 1) p2 = true;
            if (p2) ++p2_sum;
        }
    }
    cout << p1_sum << '\n';
    cout << p2_sum << '\n';
}
    

