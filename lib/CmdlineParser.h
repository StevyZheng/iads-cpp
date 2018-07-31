//
// Created by root on 7/18/18.
//

#ifndef IADS_CMDLINEPARSER_H
#define IADS_CMDLINEPARSER_H

#include "linux/SystemInfo.h"
#include "linux/Storage.h"

using namespace boost::program_options;

class CmdlineParser {
public:
    CmdlineParser(){
        this->pOpts = new options_description("iads options");
        this->pVm = new variables_map();
        this->pOpts->add_options()
                ("help,h", "iads help info.")
                ("sysinfo", value<string>()->implicit_value("\"table\""),"system info, add param: table, str or json.")
                ("mkdir", value<vector<string>>()->multitoken(), "multi create dirs, param: path count.")
                ("phyerror", "print phy error table.");
    }
    ~CmdlineParser(){
        delete this->pOpts;
        delete this->pVm;
    }

    void parse(int argc, char* argv[]);
    void doing();

private:
    options_description* pOpts;
    variables_map* pVm;
};


#endif //IADS_CMDLINEPARSER_H
