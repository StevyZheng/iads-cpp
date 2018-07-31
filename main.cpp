#include <iostream>
#include "lib/CmdlineParser.h"
#include "lib/linux/Storage.h"
extern "C" {
#include "lib/database/sqlcipher/sqlite3.h"
}

using namespace std;


int main(int argc, char* argv[]) {
    CmdlineParser parser;
    parser.parse(argc, argv);
    parser.doing();

    /*SystemInfo si;
    si.get_info();
    cout << si.to_table();

    Phy phy;
    cout << phy.phys_to_table();*/
    sqlite3 *db = NULL;
    char *err_msg = NULL;
    int rc = sqlite3_open("test.db", &db);
    sqlite3_close(db);

    return 0;
}

