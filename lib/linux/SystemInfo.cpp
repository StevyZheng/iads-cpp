//
// Created by root on 7/14/18.
//

#include "SystemInfo.h"



SystemInfo::SystemInfo() {
    this->ry_sn = this->sm_sn = this->server_model = this->cpu_model = "";
    this->cpu_count = this->cpu_socket_count = this->mem_count = this->mem_channel_count = 0;
    this->cpu_stepping = this->mem_model = this->bios_vender = this->bios_ver = "";
    this->bios_date = this->bmc_ver = this->bmc_date = this->os_ver = this->kernel_ver = "";
}

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
            //return;
        }
    }

}

string SystemInfo::to_json() {
    string json_str;
    StaticJsonBuffer<2048> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    JsonObject& nextRoot = root.createNestedObject("systeminfo");
    nextRoot["ry_sn"] = this->ry_sn;
    nextRoot["sm_sn"] = this->sm_sn;
    nextRoot["server_model"] = this->server_model;
    nextRoot["cpu_model"] = this->cpu_model;
    nextRoot["cpu_count"] = this->cpu_count;
    nextRoot["cpu_stepping"] = this->cpu_stepping;
    nextRoot["cpu_socket_count"] = this->cpu_socket_count;
    nextRoot["mem_model"] = this->mem_model;
    nextRoot["mem_count"] = this->mem_count;
    nextRoot["mem_channel_count"] = this->mem_channel_count;
    nextRoot["bios_vender"] = this->bios_vender;
    nextRoot["bios_ver"] = this->bios_ver;
    nextRoot["bios_date"] = this->bios_date;
    nextRoot["bmc_ver"] = this->bmc_ver;
    nextRoot["bmc_date"] = this->bmc_date;
    nextRoot["os_ver"] = this->os_ver;
    nextRoot["kernel_ver"] = this->kernel_ver;
    root.prettyPrintTo(json_str);
    return json_str;
}

string SystemInfo::to_string() {
    stringstream retstream;
    string ret;
    retstream << "ry_sn:" << this->ry_sn << endl << "sm_sn:" << this->sm_sn << endl << "server_model:" \
        << this->server_model << endl << "cpu_model:" << this->cpu_model << endl << "cpu_count:" << this->cpu_count << endl\
        << "cpu_stepping:" << this->cpu_stepping << endl << "cpu_socket_count:" << this->cpu_socket_count << endl\
        << "mem_model:" << this->mem_model << endl << "mem_count:" << this->mem_count << endl << "mem_channel_count:"\
        << this->mem_channel_count << endl << "bios_ver:" << this->bios_ver << endl << "bios_vender:" << this->bios_vender\
        << endl << "bios_date:" << this->bios_date << endl << "bmc_ver:" << this->bmc_ver << endl << "bmc_date:" << this->bmc_date\
        << endl << "os_ver:" << this->os_ver << endl << "kernel_ver:" << this->kernel_ver << endl;
    ret = retstream.str();
    return ret;
}

long SystemInfo::get_sys_mem_size() {
    int tmp;
    string ret_shell = Command::shell_exec("cat /proc/meminfo|grep MemFree", tmp);
    vector<string> ret_v = Common::split_string(ret_shell, ":");
    long ret = 1024 * atoi(ret_v[1].c_str());
    return ret;
}

