#include <iostream>
#include "lib/CmdlineParser.h"

using namespace std;


int main(int argc, char* argv[]) {
    /*CmdlineParser parser;
    parser.parse(argc, argv);
    parser.doing();*/
    cout <<  SystemInfo::get_sys_mem_size() << endl;
    return 0;
}