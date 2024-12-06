#include <iostream>
#include <string>

using namespace std;

// I did not think a brute force simulation would work
// but here we are...
long run_iters(string& current, string& next, int iters)
{
    for (int i = 0; i < iters; i++) {
        char cur = current[0];
        int count = 1;
        for (int i = 1; i < current.size(); i++) {
            char c = current[i];
            if (c != cur) {
                next += to_string(count) + cur;
                cur = c;
                count = 0;
            }
            ++count;
        }
        next += to_string(count) + cur;

        swap(next, current);
        next = "";
    } 
    return current.size();
}

int main()
{
    string current, next;

    cin >> current;
    cout << run_iters(current, next, 40) << '\n';
    cout << run_iters(current, next, 10) << '\n';
}
