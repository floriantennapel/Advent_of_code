#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

long mul(const string& input)
{
    long sum = 0;
    int a, b;
    char c;

    const regex re("mul\\([1-9][0-9]{0,2},[1-9][0-9]{0,2}\\)");

    sregex_iterator it(begin(input), end(input), re);
    sregex_iterator end;
    for (; it != end; it++) {
        stringstream str((*it).str().substr(4)); 
        str >> a >> c >> b;
        sum += a * b;
    }

    return sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input; 
    string line;
    while (getline(cin, line))
        input += line;

    // part 1
    cout << mul(input) << '\n';

    // part 2
    const regex dont_do("don't\\(\\)[\\s\\S]*?do\\(\\)");
    const regex dont("don't\\(\\)");

    input = regex_replace(input, dont_do, "");
    smatch match;
    regex_search(input, match, dont);
    cout << mul(input.substr(0, match.position())) << '\n';
}
