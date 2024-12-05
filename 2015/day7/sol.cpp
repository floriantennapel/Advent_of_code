#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cstdint>

using namespace std;

struct Node
{
    string op;
    string a;
    optional<string> b;
    optional<uint16_t> val;
};

bool is_number(const string& s)
{
    return ranges::all_of(s, [](char c) {return c >= '0' && c <= '9';});
}

uint16_t signal(unordered_map<string, Node>& wires, const string& current)
{
    if (is_number(current))
        return  stoi(current);

    Node& cur = wires.at(current);
    if (cur.val)
        return *cur.val;

    if (cur.op == "LINK")
        cur.val = signal(wires, cur.a);
    else if (cur.op == "AND")
        cur.val = signal(wires, cur.a) & signal(wires, *cur.b);
    else if (cur.op == "OR")
        cur.val = signal(wires, cur.a) | signal(wires, *cur.b);
    else if (cur.op == "LSHIFT")
        cur.val = signal(wires, cur.a) << signal(wires, *cur.b);
    else if (cur.op == "RSHIFT")
        cur.val = signal(wires, cur.a) >> signal(wires, *cur.b);
    else if (cur.op == "NOT")
        cur.val = ~signal(wires, cur.a);

    return *cur.val;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_map<string, Node> wires;

    string line;
    vector<string> split;
    while (getline(cin, line) && line != "") {
        stringstream stream(line);
        copy(istream_iterator<string>(stream), istream_iterator<string>(), back_inserter(split));

        if (split[1] == "->")
            wires[split[2]] = {"LINK", split[0], nullopt};
        else if (split[0] == "NOT")
            wires[split[3]] = {split[0], split[1], nullopt};
        else 
            wires[split[4]] = {split[1], split[0], {split[2]}};
        split.clear();
    }

    // part 1
    uint16_t res = signal(wires, "a");
    cout << res << '\n';

    // part 2
    for (auto&[key, node] : wires)
        node.val = nullopt;
    wires["b"].val = res;
    cout << signal(wires, "a") << '\n';
}
