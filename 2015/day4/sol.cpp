#include <iostream>
#include <openssl/md5.h>
#include <cstring>

using namespace std;

int main()
{
    // interop with legacy C functions is such a mess...
    
    string secret;
    cin >> secret;
    unsigned char hash[17];
    unsigned char key[20];

    // part 1
    char hexbuf[7];
    int i = 1;
    for (;;i++) {
        int n = sprintf((char*)key, "%s%d", secret.c_str(), i);
        MD5(key, n, hash);
        sprintf(hexbuf, "%02x%02x%02x", hash[0], hash[1], hash[2]);
        if (strncmp(hexbuf, "00000", 5) == 0) {
            cout << (int) hash[2] << '\n';
            cout << i << '\n';
            break;
        }
    }

    // part 2
    char pref[] = {0, 0, 0}; 
    for (;;i++) {
        int n = sprintf((char*)key, "%s%d", secret.c_str(), i);
        MD5(key, n, hash);
        if (memcmp(pref, hash, 3) == 0) {
            cout << i << '\n';
            break;
        }
    }
}
