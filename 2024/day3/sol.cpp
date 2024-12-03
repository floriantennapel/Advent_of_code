#include <iostream>
#include <regex>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input; 
    string line;
    while (getline(cin, line))
        input += line;

    int a, b;
    char c;
    sregex_iterator end_it;

    // part 1
    long sum = 0;
    const regex re_p1("mul\\(\\d{1,3},\\d{1,3}\\)");
    sregex_iterator it(begin(input), end(input), re_p1);
    for (; it != end_it; it++) {
        stringstream stream((*it).str().substr(4)); 
        stream >> a >> c >> b;
        sum += a * b;
    }
    cout << sum << '\n';

    /* new shorter solution based on hyperneutrino's solution.
     * I didn't know about matching several regexes simultaneously, but this is a much cleaner and more logical solution.
     * My goal with AOC is to get better at programming, so I'm perfectly fine with trying to copy other peoples better solutions (of course after having solved it myself)
     */
    // part 2
    bool active = true;
    sum = 0;
    const regex re_p2("don't\\(\\)|do\\(\\)|mul\\(\\d{1,3},\\d{1,3}\\)");
    it = {begin(input), end(input), re_p2};
    for (; it != end_it; it++) {
        string s = (*it).str(); 
        if (s == "don't()")
            active = false;
        else if (s == "do()")
            active = true;
        else if (active) {
            stringstream stream(s.substr(4)); 
            stream >> a >> c >> b;
            sum += a * b;
        }
    }
    cout << sum << '\n';
}
