//
// Created by root on 7/18/18.
//

#ifndef IADS_CMDLINEPARSER_H
#define IADS_CMDLINEPARSER_H

#include "stevy.h"

class CmdlineParser {
public:
    CmdlineParser(){
        this->pOpts = new boost::program_options::options_description("iads options");
        this->pVm = new boost::program_options::variables_map();
    }
    ~CmdlineParser(){
        delete this->pOpts;
        delete this->pVm;
    }

private:
    boost::program_options::options_description* pOpts;
    boost::program_options::variables_map* pVm;
};


#endif //IADS_CMDLINEPARSER_H
