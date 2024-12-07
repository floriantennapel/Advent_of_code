#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

template<class RIt>
bool is_valid(long target, RIt r_first, RIt r_end, bool pt2 = false)
{
    if (r_first+1 == r_end)
        return target == *r_first;
    if (*r_first > target)
        return false;
    if (is_valid(target - *r_first, r_first + 1, r_end, pt2))
        return true;
    if (target % *r_first == 0 && is_valid(target / *r_first, r_first + 1, r_end, pt2))
        return true;
    if (pt2) {
        string a = to_string(*r_first);
        string ts = to_string(target);
        if (ts.size() > a.size() && ts.ends_with(a)) {
            long new_target = stol(ts.substr(0, ts.size()-a.size()));
            return is_valid(new_target, r_first + 1, r_end, pt2);
        }
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
        
        if (is_valid(target, ns.rbegin(), ns.rend())) {
            sum_p1 += target;
            sum_p2 += target;
        } else if (is_valid(target, ns.rbegin(), ns.rend(), true))
            sum_p2 += target;
    }
    cout << sum_p1 << '\n';
    cout << sum_p2 << '\n';
}
