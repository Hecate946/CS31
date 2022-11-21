#include <iostream>
using namespace std;

void removeS(char* cstring) {
    char* ptr = cstring;
    while (*cstring != 0) {
        if (*cstring != 's' && *cstring != 'S') {
            *ptr = *cstring;
            ptr++;
        }
        cstring++;
    *ptr = 0;
    }
}
int main()
{
    char msg[50] = "She'll shave a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll have a male prince.
}
