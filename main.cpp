#include <iostream>
#include "lib/linux/SystemInfo.h"
using namespace std;

int main() {
    SystemInfo si;
    si.init();
    return 0;
}