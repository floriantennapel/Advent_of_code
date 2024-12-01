#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    vector<int> v1;
    vector<int> v2;
    while (cin >> a >> b) {
        v1.push_back(a);
        v2.push_back(b);
    }

    // part 1
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    long sum = 0;
    for (int i = 0; i < v1.size(); i++)
        sum += abs(v1[i] - v2[i]);
    cout << sum << '\n';

    // part 2
    unordered_map<int, int> counter;
    for (int d : v2)
        counter[d] += 1;
    sum = 0;
    for (int d : v1)
        sum += d * counter[d];
    cout << sum << '\n';
}
