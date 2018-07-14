#include <iostream>
#include "lib/linux/Common.h"
using namespace std;

int main() {
    string  a="asfds1rtgf sfdgd qwed123\r\n";
    vector<string> ret = Common::split_string(a);
    cout << ret.size() << endl;
    for(auto i: ret) {
            cout << i << endl;
    }
    return 0;
}