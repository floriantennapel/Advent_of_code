#include <iostream>
#include <vector>

using namespace std;

int count__xmas(const vector<string>& crossword, int r, int c)
{
    const vector<pair<int, int>> dirs = {
        {-1,-1}, {-1, 0}, {-1, 1}, {0 , 1}, 
        {1 , 1}, {1 , 0}, { 1,-1}, {0 ,-1}
    };
    const string xmas = "MAS";
    int count = 0;
    for (auto[dr, dc] : dirs) {
        if (r+dr*3 < 0 || r+dr*3 >= crossword.size() || c+dc*3 < 0 || c+dc*3 > crossword[0].size())
            continue;
        bool found = true;
        for (int i = 0; i < 3; i++) {
            if (crossword[r+dr*(i+1)][c+dc*(i+1)] != xmas[i]) 
                found = false;
        } 
        if (found) ++count;
    }
    return count;
}

bool is_xmas(const vector<string>& crossword, int r, int c)
{
    for (int dr = -1; dr < 2; dr += 2) {
        for (int dc = -1; dc < 2; dc += 2) {
            if (crossword[r+dr][c+dc] != 'M' && crossword[r+dr][c+dc] != 'S')
                return false;
        }
    }
    return (crossword[r-1][c-1] != crossword[r+1][c+1] && crossword[r-1][c+1] != crossword[r+1][c-1]);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<string> crossword;
    string line;
    while (cin >> line) {
        if (line == "")
            break;
        crossword.push_back(line);
    } 
    
    // part 1
    int count = 0;
    for (int i = 0; i < crossword.size(); i++) {
        for (int j = 0; j < crossword[0].size(); j++) {
            if (crossword[i][j] == 'X')
                count += count__xmas(crossword, i, j); 
        }
    }
    cout << count << '\n';

    // part 2
    count = 0;
    for (int i = 1; i < crossword.size()-1; i++) {
        for (int j = 1; j < crossword[0].size()-1; j++) {
            if (crossword[i][j] == 'A' && is_xmas(crossword, i, j))
                ++count;
        }
    }
    cout << count << '\n';
}
