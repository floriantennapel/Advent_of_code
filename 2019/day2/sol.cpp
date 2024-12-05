#include <iostream>
#include <unordered_map>

using namespace std;
long run_prog(const unordered_map<long, long>& prog, int noun, int verb)
{
    unordered_map<long, long> cpy(prog);
    cpy[1] = noun;
    cpy[2] = verb;
    for (int i = 0;; i += 4) {
        long op = cpy[i];
        if (op == 99)
            break;
        else if (op == 1)
            cpy[cpy[i+3]] = cpy[cpy[i+1]]+cpy[cpy[i+2]];
        else if (op == 2)
            cpy[cpy[i+3]] = cpy[cpy[i+1]]*cpy[cpy[i+2]];
    }
    return cpy[0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<long, long> program;
    string d;
    for (int i = 0; getline(cin, d, ','); i++)
        program[i] = stol(d); 
    
    // part 1
    cout << run_prog(program, 12, 2) << '\n';

    // part 2
    long target = 19690720;
    for (int n = 0; n < 100; n++) {
        for (int v = 0; v < 100; v++) {
            if (run_prog(program, n, v) == target) {
                cout << 100 * n + v << '\n';
                return 0;
            }
        }
    }
}
