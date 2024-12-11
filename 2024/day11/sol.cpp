#include <boost/container_hash/hash.hpp>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
using ul = unsigned long;

template<>
struct std::hash<pair<ul, int>>
{
    size_t operator()(const pair<ul, int>& p) const
    {
        size_t seed = 0;
        boost::hash_combine(seed, p.first);
        boost::hash_combine(seed, p.second);
        return seed;
    }
};

unordered_map<pair<ul, int>, ul> memo;
ul split_stones(ul stone, int remaining)
{
    if (remaining == 0)
        return 1;

    pair<ul, int> key = {stone, remaining};
    auto res = memo.find(key);
    if (res != memo.end())
        return res->second;
    
    ul result = 0;
    string as_str = to_string(stone);
    if (!stone)
        result = split_stones(1, remaining-1);
    else if (as_str.size() % 2 == 0) {
        ul s1 = stoul(as_str.substr(0, as_str.size() / 2));
        ul s2 = stoul(as_str.substr(as_str.size() / 2));
        result = split_stones(s1, remaining-1) + split_stones(s2, remaining-1);
    } else
        result = split_stones(stone*2024, remaining-1);

    memo[key] = result;
    return result;
}

int main()
{
    ul stone;
    ul sum_p1 = 0;
    ul sum_p2 = 0;
    while (cin >> stone) {
        sum_p1 += split_stones(stone, 25);
        sum_p2 += split_stones(stone, 75);
    }
    cout << sum_p1 << '\n';
    cout << sum_p2 << '\n';
}
