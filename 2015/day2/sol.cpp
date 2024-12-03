#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<array<int, 3>> boxes;

    int l, w, h;
    char ign;
    while (cin >> l >> ign >> w >> ign >> h) {
        array<int, 3> box = {l, w, h};
        ranges::sort(box);
        boxes.push_back(move(box));
    }

    // part 1
    vector<int> paper;
    ranges::transform(boxes, back_inserter(paper), [](auto& box) {
        auto[l, w, h] = box;
        return 2*l*w + 2*w*h + 2*h*l + l*w;
    });
    cout << accumulate(begin(paper), end(paper), 0) << '\n';

    // part 2
    vector<int> ribbon;
    ranges::transform(boxes, back_inserter(ribbon), [](auto& box) {
        auto[l, w, h] = box;
        return l+l+w+w + l*w*h;   
    });
    cout << accumulate(begin(ribbon), end(ribbon), 0) << '\n';
}
