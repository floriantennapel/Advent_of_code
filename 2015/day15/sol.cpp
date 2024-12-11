#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <array>
#include <regex>

using namespace std;

int main()
{
    regex re(R"(-?\d+)");
    sregex_iterator end;

    vector<array<int, 5>> ingredients;

    string line;
    while (getline(cin, line) && line != "") {
        sregex_iterator it(line.begin(), line.end(), re);
        ingredients.emplace_back();
        auto& b = ingredients.back();
        for (int i = 0; it != end; it++, i++) {
            b[i] = stoi(it->str()); 
        }
    }
    
    // probably the worst code ever written...
    long best = 0;
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            if (i + j > 100)
                break;
            for (int k = 0; k <= 100; k++) {
                if (i + j + k > 100)
                    break;
                for (int l = 0; l <= 100; l++) {
                    if (i + j + k + l > 100)
                        break;
                    if (i+j+k+l != 100)
                        continue;
                    array<long, 5> sums;
                    for (int ind = 0; ind < 5; ind++) {
                        sums[ind] = ingredients[0][ind]*i + ingredients[1][ind]*j
                                  + ingredients[2][ind]*k + ingredients[3][ind]*l;
                    }
                    if (/* *part 2* sums[4] != 500 || */ any_of(sums.begin(), sums.end()-1, [](long s) {return s <= 0;}))
                        continue;
                    long prod = accumulate(sums.begin(), sums.end()-1, 1, [](long acc, long s) {return acc * s;});
                    best = max(best, prod);   
                }
            }
        }
    }
    cout << best << '\n';
}
