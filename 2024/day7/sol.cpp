#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

template<class It>
bool is_valid(long target, long so_far, It first, It last, bool pt2 = false)
{
    if (so_far > target)
        return false;
    if (first == last)
        return target == so_far;
    if (is_valid(target, so_far + *first, first + 1, last, pt2))
        return true;
    if (is_valid(target, so_far * *first, first + 1, last, pt2))
        return true;
    if (pt2) {
        string a = to_string(so_far), b = to_string(*first);
        if (a.size() + b.size() > 18) // ingeger overflow
            return false;

        long concated = stol(a+b);
        return is_valid(target, concated, first + 1, last, pt2);
    }
    return false;
}

int main()
{
    string line;
    vector<long> ns;
    char ign;
    long target, d, sum_p1 = 0, sum_p2 = 0;
    while (getline(cin, line) && line != "") {
        ns.clear();
        stringstream s(line);
        s >> target >> ign;
        while (s >> d)
            ns.push_back(d);
        
        if (is_valid(target, 0, ns.begin(), ns.end())) {
            sum_p1 += target;
            sum_p2 += target;
        } else if (is_valid(target, 0, ns.begin(), ns.end(), true))
            sum_p2 += target;
    }
    cout << sum_p1 << '\n';
    cout << sum_p2 << '\n';
}
