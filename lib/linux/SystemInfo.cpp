//
// Created by root on 7/14/18.
//

#include "SystemInfo.h"



SystemInfo::SystemInfo() {
    this->ry_sn = this->sm_sn = this->server_model = this->cpu_model = "";
    this->cpu_count = this->cpu_socket_count = this->mem_count = this->mem_channel_count = 0;
    this->cpu_stepping = this->mem_model = this->bios_vender = this->bios_ver = "";
    this->bios_date = this->bmc_ver = this->bmc_date = this->os_ver = this->kernel_ver = "";
    this->attr_vector = {"ry_sn", "sm_sn", "server_model", "cpu_model", "cpu_count", "cpu_stepping",\
        "cpu_socket_count", "mem_model", "mem_count", "mem_channel_count", "bios_vender", "bios_ver",\
         "bios_date", "bmc_ver", "bmc_date", "os_ver", "kernel_ver"};
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
    retstream << "ry_sn:" << this->ry_sn << endl << "sm_sn:" << this->sm_sn << endl << "server_model:" \
        << this->server_model << endl << "cpu_model:" << this->cpu_model << endl << "cpu_count:" << this->cpu_count << endl\
        << "cpu_stepping:" << this->cpu_stepping << endl << "cpu_socket_count:" << this->cpu_socket_count << endl\
        << "mem_model:" << this->mem_model << endl << "mem_count:" << this->mem_count << endl << "mem_channel_count:"\
        << this->mem_channel_count << endl << "bios_ver:" << this->bios_ver << endl << "bios_vender:" << this->bios_vender\
        << endl << "bios_date:" << this->bios_date << endl << "bmc_ver:" << this->bmc_ver << endl << "bmc_date:" << this->bmc_date\
        << endl << "os_ver:" << this->os_ver << endl << "kernel_ver:" << this->kernel_ver << endl;
    return retstream.str();
}

long long SystemInfo::get_avail_mem_size() {
    int tmp;
    string ret_shell = Command::shell_exec("cat /proc/meminfo|grep MemFree", tmp);
    vector<string> ret_v = Common::split_string(ret_shell);
    stringstream buf;
    buf << ret_v[1];
    long long ret;
    buf >> ret;
    return ret *= 1024;
}

string SystemInfo::get_info() {
    int recode;
    string cpu_info = Common::trim(Command::shell_exec("lscpu", recode));
    string dmi_info = Common::trim(Command::shell_exec("dmidecode", recode));
    string fru_info = Common::trim(Command::shell_exec("./ipmicfg -fru PS", recode));
    string os_info = Common::trim(Command::shell_exec("lsb_release -d", recode));
    string kernel_info = Common::trim(Command::shell_exec("uname -r", recode));
    this->kernel_ver = kernel_info;
    this->os_ver = Common::trim(Common::split_string(os_info, ":").at(1));
    this->cpu_model = Common::trim(Common::regex_rows_column(cpu_info, ".*Model name.+", 1, ":").at(0));
    this->cpu_stepping = Common::trim(Common::regex_rows_column(cpu_info, ".*Stepping.+", 1, ":").at(0));
    try {
        stringstream t_str;
        t_str << Common::regex_rows_column(cpu_info, ".*Socket.+", 1)[0];
        t_str >> this->cpu_socket_count;
        t_str.clear();
    }catch(Exception e){
        cout << "" << endl;
    }
    /*int tpc, cps, cs;
    t_str << Common::regex_rows_column(cpu_info, ".*Thread(s) per core.+", 1).at(0);
    t_str >> tpc;
    t_str.clear();
    t_str << Common::regex_rows_column(cpu_info, ".*Core(s) per socket.+", 1).at(0);
    t_str >> cps;
    this->cpu_count = get_nprocs() / (tpc * cps);*/
    return std::string();
}

vector<string> SystemInfo::get_attr_value() {
    vector<string> ret;
    stringstream tmp_cpu_count, tmp_cpu_socket_count, tmp_mem_count, tmp_mem_channel_count;
    tmp_cpu_count << this->cpu_count;
    string t_cpu_count, t_cpu_socket_count, t_mem_count, t_mem_channel_count;
    tmp_cpu_socket_count << this->cpu_socket_count;
    tmp_mem_count << this->mem_count;
    tmp_mem_channel_count << this->mem_channel_count;

    ret.emplace_back(this->ry_sn);
    ret.emplace_back(this->sm_sn);
    ret.emplace_back(this->server_model);
    ret.emplace_back(this->cpu_model);
    ret.emplace_back(tmp_cpu_count.str());
    ret.emplace_back(this->cpu_stepping);
    ret.emplace_back(tmp_cpu_socket_count.str());
    ret.emplace_back(this->mem_model);
    ret.emplace_back(tmp_mem_count.str());
    ret.emplace_back(tmp_mem_channel_count.str());
    ret.emplace_back(this->bios_vender);
    ret.emplace_back(this->bios_ver);
    ret.emplace_back(this->bios_date);
    ret.emplace_back(this->bmc_ver);
    ret.emplace_back(this->bmc_date);
    ret.emplace_back(this->os_ver);
    ret.emplace_back(this->kernel_ver);
    return ret;
}

string SystemInfo::to_table() {
    ConsoleTable sysinfo_table(2);
    auto *buf = new ostringstream;
    Row header = {"**Attribute**", "**Value**"};
    sysinfo_table.AddNewRow(header);
    vector<string> attr_value = this->get_attr_value();
    for(int i=0; i < this->attr_vector.size(); i++){
        sysinfo_table.AddNewRow({this->attr_vector[i], attr_value[i]});
    }
    sysinfo_table.WriteTable(Align::Center, buf);
    return buf->str();
}

