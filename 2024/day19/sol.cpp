#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using ul = unsigned long;

unordered_map<string, ul> memo;
ul count_towels(string pattern, const vector<string>& towels)
{
    auto res = memo.find(pattern);
    if (res != memo.end())
        return res->second;

    if (pattern == "")
        return 1;

    ul count = 0;
    for (auto& t : towels) {
        if (pattern.starts_with(t))
            count += count_towels(pattern.substr(t.size()), towels);
    }

    memo[pattern] = count;
    return count;
}

int main()
{
    vector<string> towels;

    string word, line;
    getline(cin, line); 
    stringstream stream(line); 
    while (stream >> word) {
        if (word.ends_with(','))
            towels.push_back(word.substr(0, word.size()-1));
        else
            towels.push_back(word);
    }

    ul p1 = 0, p2 = 0;
    while (cin >> word) {
        ul res = count_towels(word, towels);
        p2 += res;
        if (res != 0) ++p1;
    }

    cout << p1 << '\n';
    cout << p2 << '\n';
}
