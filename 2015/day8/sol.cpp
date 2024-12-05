#include <iostream>
#include <regex>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    while (getline(cin, line) && line != "")
        lines.push_back(line);

    
    // part 1
    regex escape(R"(\\"|\\\\)");
    regex hex(R"(\\x[0-9a-f]{2})");
    sregex_iterator it_end;

    int sum = 0;
    for (string& line : lines) {
        sum += 2;
        for (auto it = sregex_iterator(begin(line), end(line), escape); it != it_end; it++, sum++);
        for (auto it = sregex_iterator(begin(line), end(line), hex); it != it_end; it++, sum += 3);
    }
    cout << sum << '\n';

    // part 2
    auto is_escape = [](char c) { return c == '\\' || c == '\"'; };
    sum = 0;
    for (string& line : lines)
        sum += 2 + ranges::count_if(line, is_escape);
    cout << sum << '\n';
}
