#include <iostream>
#include "lib/CmdlineParser.h"

using namespace std;


int main(int argc, char* argv[]) {
    /*CmdlineParser parser;
    parser.parse(argc, argv);
    parser.doing();*/
    SystemInfo si;
    si.get_info();
    cout << si.to_table();
    return 0;
}