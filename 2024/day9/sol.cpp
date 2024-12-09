#include <iostream>
#include <vector>

using namespace std;

void remove_block(vector<int>& nums, int id, int n)
{
    for (int i = nums.size()-1; i >= 0 && n > 0; i--) {
        if (nums[i] == id) {
            nums[i] = -1;
            n--;
        }
    }
}

int free_size(const vector<int>& nums, int i)
{
    int count = 0;
    for (int id = nums[i]; i < nums.size() && nums[i] == id; i++, count++);
    return count;
}

long checksum(const vector<int>& nums)
{
    long sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == -1)
            continue;
        sum += i * nums[i];
    }
    return sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    cin >> input;
    
    vector<int> nums_p1;
    int pos = 0;
    for (int i = 0; i < input.size(); i++) {
        int n = input[i] - '0';
        for (int j = 0; j < n; j++)
            nums_p1.push_back(i % 2 == 0 ? i/2 : -1);
    }
    vector<int> nums_p2{nums_p1};

    // part 1
    for (int i = 0; i < nums_p1.size(); i++) {
        if (nums_p1[i] == -1) {
            int b = nums_p1.back();
            nums_p1.pop_back();
            if (b == -1) {
                --i;
                continue;
            }
            nums_p1[i] = b;
        }
    }

    cout << checksum(nums_p1) << '\n';

    // part 2
    // this code is so bad...
    for (int bi = input.size()-1; bi >= 0; bi -= 2) {
        int n = input[bi]-'0';
        for (int i = 0; i < nums_p2.size(); i++) {
            if (nums_p2[i] == -1) {
                int f = free_size(nums_p2, i);
                if (n <= f) {
                    for (int j = 0; j < n; j++) {
                        nums_p2[i+j] = bi/2;
                    }
                    remove_block(nums_p2, bi/2, n);
                    break;
                } else {
                    i += f-1;
                }
            }
        }
    }

    cout << checksum(nums_p2)<< '\n';
}
