//
// Created by root on 7/14/18.
//

#include "SystemInfo.h"

void SystemInfo::init() {
    //check tools env,like ipmitool dmidecode.
    string sys_path = std::getenv("PATH");
    vector<string> split_path = Common::split_string(sys_path, ":");
    vector<string> files;
    for(auto c: split_path){
        string ipmitool_path = c + "/ipmitool";
        string dmidecode_path = c + "/dmidecode";
        if(!Common::exeist_file(ipmitool_path) || !Common::exeist_file(dmidecode_path)){
            cout << "ipmitool or dmidecode is not exeist." << endl;
            return;
        }
    }
}

string SystemInfo::to_json() {
    string json_str;
    sptree root;
    sptree item;
    return json_str;
}
