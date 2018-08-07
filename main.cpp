#include <iostream>
#include "lib/CmdlineParser.h"
#include "lib/linux/Storage.h"
extern "C" {
#include "lib/database/sqlcipher/sqlite3.h"
}

#include "Dense"

using namespace std;


int main(int argc, char* argv[]) {

    CmdlineParser parser;
    parser.parse(argc, argv);
    parser.doing();

    /*SystemInfo si;
    si.get_info();
    cout << si.to_table();

    Phy phy;
    cout << phy.phys_to_table();

    SysLog sl;
    sl.parse_log();
    cout << sl.get_err_msg_str();*/

    return 0;
}

