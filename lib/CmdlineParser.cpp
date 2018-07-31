//
// Created by root on 7/18/18.
//

#include "CmdlineParser.h"

void CmdlineParser::parse(int argc, char* argv[]) {
    try {
        store(parse_command_line(argc, reinterpret_cast<const char *const *>(argv), *(this->pOpts)), *(this->pVm));
        notify(*(this->pVm));
    }
    catch (...){
        cout << "Undefined options in the input parameters!" << endl;
        return;
    }
}

void CmdlineParser::doing() {
    if(this->pVm->count("help")){
        cout << *(this->pOpts) << endl;
        return;
    }
    if(this->pVm->count("sysinfo")){
        SystemInfo si;
        si.get_info();
        if("str" == this->pVm->at("sysinfo").as<string>())
            cout << si.to_string();
        else if("table" == this->pVm->at("sysinfo").as<string>())
            cout << si.to_table();
        else if("json" == this->pVm->at("sysinfo").as<string>())
            cout << si.to_json() << endl;
    }
    if(this->pVm->count("mkdir")){
        IoDemo::create_multi_dirs(this->pVm->at("mkdir").as<vector<string>>()[0], atoi(this->pVm->at("mkdir").as<vector<string>>()[1].c_str()));
    }
    if(this->pVm->count("phyerror")){
        cout << Phy::err_phys_to_table();
    }
    if(this->pVm->empty()){
        //cout << "no options." << endl;
        cout << *(this->pOpts) << endl;
        return;
    }
}
