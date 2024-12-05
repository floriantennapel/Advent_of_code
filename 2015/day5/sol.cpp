#include <iostream>
#include <vector>
#include <regex>

using namespace std;

bool is_nice(const string& s, const vector<regex>& incl, const vector<regex>& excl)
{
    for (auto& r : incl)
        if (!regex_search(s, r))
            return false;
    for (auto& r : excl)
        if (regex_search(s, r))
            return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> strings;
    string line;
    while (cin >> line)
        strings.push_back(line);

    // part 1
    const vector<regex> allowed_p1 = { 
        regex(R"((.*[aeoiu]){3,})"), 
        regex(R"(([a-z])\1+)") 
    };
    const vector<regex> naughty_p1 = { regex(R"(ab|cd|pq|xy)") };
    int sum = 0;
    for (auto& s : strings)
         if (is_nice(s, allowed_p1, naughty_p1))
            ++sum;
    cout << sum << '\n';

    // part 2
    const vector<regex> allowed_p2 = { 
        regex(R"(([a-z]{2}).*\1+)"), 
        regex(R"(([a-z])[a-z]\1)") 
    };
    const vector<regex> naughty_p2;
    sum = 0;
    for (auto& s : strings)
        if (is_nice(s, allowed_p2, naughty_p2))
            ++sum;
    cout << sum << '\n';
}
