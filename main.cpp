#include <iostream>
#include "lib/CmdlineParser.h"
#include "lib/linux/Storage.h"

using namespace std;


int main(int argc, char* argv[]) {
    /*CmdlineParser parser;
    parser.parse(argc, argv);
    parser.doing();

    SystemInfo si;
    si.get_info();
    cout << si.to_json();*/

    Phy phy;
    cout << phy.err_phys_to_table();

    return 0;
}