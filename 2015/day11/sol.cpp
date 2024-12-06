#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <regex>
#include <vector>

using namespace std;

// rules are unclear if the two pairs can have the same characters
// in my input, this was not a problem anyway
const regex two_pairs(R"(([a-z])\1.*([a-z])\2)");
const regex confusing("[iol]");
const string confusing_s = "iol";

vector<int> diffs(8);
bool is_valid(const string& s)
{
    adjacent_difference(s.begin(), s.end(), diffs.begin()); 
    bool found = false;
    int prev = -1;
    for (int i = 0; i < diffs.size(); i++) {
        if (prev == 1 && diffs[i] == 1) {
            found = true;
            break;
        }
        prev = diffs[i];
    }
    if (!found)
        return false;

    if (regex_search(s, confusing))
        return false;

    return regex_search(s, two_pairs);
}

void remove_confusing(string& s)
{
    for (int i = 0; i < 8; i++) {
        if (confusing_s.find(s[i]) != string::npos) {
            s[i]++;
            for (int j = i+1; j < 8; j++)
                s[j] = 'a';
            return;
        }
    }     
}

void inc(string& s)
{
    for (int i = 7; i >= 0; i--) {
        char c = s[i];
        if (c != 'z') {
            s[i]++;
            if (confusing_s.find(s[i]) != string::npos)
                remove_confusing(s);
            return;
        } else
            s[i] = 'a';
    }
    throw runtime_error("password overflow");
}


int main()
{
    string s;
    cin >> s;
    remove_confusing(s);

    // part 1
    for (inc(s); !is_valid(s); inc(s));
    cout << s << '\n';

    // part 2
    for (inc(s); !is_valid(s); inc(s));
    cout << s << '\n';
}
