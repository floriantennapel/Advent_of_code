#include <iostream>
#include <string>
#include <boost/json/src.hpp>

using namespace std;
using namespace boost;

long sum_json(const json::value& val, bool pt2 = false)
{
    // base cases
    if (val.is_int64())
        return val.as_int64();
    if (val.is_string())
        return 0;
    if (pt2 && val.is_object()) {
        for (auto&[_, value] : val.as_object()) {
            if (value.is_string() && value.as_string() == "red")
                return 0;
        }
    }

    // recursive step
    long sum = 0;
    if (val.is_object()) {
        for (auto&[_, value] : val.as_object())
            sum += sum_json(value, pt2);
    } else if (val.is_array()) {
        for (auto& value : val.as_array())
            sum += sum_json(value, pt2);
    }
    return sum;
}

int main()
{
    string input;
    string line;
    while(getline(cin, line) && line != "")
        input += line;

    json::value doc = json::parse(input);
    cout << sum_json(doc) << '\n';
    cout << sum_json(doc, true) << '\n'; 
}
