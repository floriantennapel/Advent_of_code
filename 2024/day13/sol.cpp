#include <iostream>
#include <regex>
#include <gmpxx.h>

using namespace std;

// apparently all solutions are unique, 
// this makes solving todays puzzle a lot easier than expected
mpz_class solve(const vector<mpz_class>& args)
{
    mpz_class inv_det = args[0]*args[3] - args[1]*args[2];
    mpz_class a = args[3]*args[4] - args[2]*args[5];
    mpz_class b = -args[1]*args[4] + args[0]*args[5];

    if (a % inv_det != 0 || b % inv_det != 0)
        return 0;
    return a / inv_det * 3 + b / inv_det;
}

int main()
{
    string input;
    getline(cin, input, '\0');
    regex re(R"(\d+)");
    sregex_iterator re_end;
    sregex_iterator it(input.begin(), input.end(), re);

    mpz_class sum_p1 = 0;
    mpz_class sum_p2 = 0;
    vector<mpz_class> args;
    for (; it != re_end; it++) {
        args.emplace_back(it->str());
        if (args.size() == 6) {
            sum_p1 += solve(args);     

            args[4] += 10000000000000;
            args[5] += 10000000000000;
            sum_p2 += solve(args);

            args.clear();
        }
    }
    cout << sum_p1 << '\n';
    cout << sum_p2 << '\n';
}
