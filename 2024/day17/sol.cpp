#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ull = unsigned long long;

ull a, b, c;
long i;
string out = "";

ull combo_op(int o)
{
    switch (o) {
    case 4:
        return a;
    case 5:
        return b;
    case 6:
        return c;
    }
    return o;
}

void instr(int ins, int o)
{
    switch (ins) {
    case 0:
        a = a / (1UL << combo_op(o));
        break;
    case 1:
        b = b ^ o;
        break;
    case 2:
        b = combo_op(o) & 7;
        break;
    case 3:
        if (a) i = ((long)o)-2;
        break;
    case 4:
        b = b ^ c;
        break;
    case 5:
        out += to_string(combo_op(o) & 7);
        out += ",";
        break;
    case 6:
        b = a / (1UL << combo_op(o));
        break;
    case 7:
        c = a / (1UL << combo_op(o));
        break;
    }
}

int main()
{
    string sign;
    char cign;
    int num;
    vector<int> instructions;

    cin >> sign >> sign >> a;
    cin >> sign >> sign >> b;
    cin >> sign >> sign >> c;
    cin >> sign;
    while (cin >> num) {
        instructions.push_back(num);
        cin >> cign;
    }

    ull orig_b = b;
    ull orig_c = c;
    string instr_string = "";
    for (int j = 0; j < instructions.size(); j++) {
        instr_string += to_string(instructions[j]);
        instr_string += ",";
    }

    // part 1
    for (i = 0; i < instructions.size(); i += 2) {
        instr(instructions[i], instructions[i+1]);
    }
    cout << out.substr(0, out.size()-1) << '\n';

    // part 2
    // this process was a bit manual, I also used a python command line prompt to help
    // For any valid a that solves the problem for n instructions, all lower bits of a will be the same, these bits will stay the same when solving for more than n instructions. 
    // We can therefore iteratively find these last bits needed and increase the precision as we go
    for (ull j = 1;; j++) {
        ull a_val = (j << 25UL) | 19768544UL; // only check a's that end with 1001011011010010011100000, this number will vary based on your input
        a = a_val;
        b = orig_b;
        c = orig_c;
        out = "";

        for (i = 0; i < instructions.size(); i += 2)
            instr(instructions[i], instructions[i+1]);
        
        /* finding common lower bits for all valid a's for a subset of the problem
         * the end of the substring should be incremented as you go
         *
         * The results can be looked at using this little python script:
         *
         * res = [ <RESULTS OF SUBSET PROBLEM> ]
         * for d in res:
         *     print(f"{(64 - len(bin(d)))*'0'}{bin(d)}")
         * 
         * the offset on line 91 should be set according to the common lower bits
         *
         * if (out.substr(0, 12) == instr_string.substr(0, 12))
         *     cout << a_val << endl;
        */

        if (out == instr_string) {
            cout << a_val << '\n';
            break;
        }
    }
}
