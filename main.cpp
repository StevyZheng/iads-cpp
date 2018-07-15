#include <iostream>
#include "lib/linux/SystemInfo.h"
using namespace std;

int main() {
    SystemInfo si;
    cout << si.to_json() << endl;
    return 0;
}