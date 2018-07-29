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
        if(!Common::exeist_file(ipmitool_path))
            this->ipmicfg_exeist = false;
        if(!Common::exeist_file(dmidecode_path))
            this->dmi_exeist = false;
    }
    if(!this->ipmicfg_exeist)
        cout << "ipmitool is not exeist." << endl;
    if(!this->dmi_exeist)
        cout << "dmidecode is not exeist." << endl;

}

string SystemInfo::to_json(Json_all_str all_str) {
    string json_str;
    StaticJsonBuffer<2048> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    JsonObject& nextRoot = root.createNestedObject("systeminfo");
    if(JSON_ALL_STR == all_str) {
        vector<string> ret_vect = this->get_attr_value();
        for (int i = 0; i < this->attr_vector.size(); i++) {
            nextRoot[this->attr_vector[i]] = ret_vect[i];
        }
    }else if(JSON_ORIGINAL == all_str) {
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
    }
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
    string now_dir = Common::get_current_dir();
    string ipmicfg_path = now_dir + "ipmicfg";
    int recode;
    string dmi_info, fru_info, bmc_summary;
    string cpu_info = Command::shell_exec("lscpu", recode);
    map<string, DataType> map_cpu = Common::parse_cpu_info();
    dmi_info = Command::shell_exec("dmidecode 2>> /dev/null", recode);
    fru_info = Command::shell_exec(ipmicfg_path + " -fru list", recode);
    bmc_summary = Command::shell_exec(ipmicfg_path + " -summary", recode);
    string os_info = Command::shell_exec("lsb_release -d", recode);
    this->kernel_ver = Command::shell_exec("uname -r", recode);
    try {
        this->os_ver = Common::split_string(os_info, ":").at(1);
        if(!cpu_info.empty()) {
            if(map_cpu.count("cpu_model") > 0)
                this->cpu_model = map_cpu["cpu_model"].get_str();
            if(map_cpu.count("cpu_stepping") > 0)
                this->cpu_stepping = map_cpu["cpu_stepping"].get_str();
            if(map_cpu.count("cpu_count") > 0)
                this->cpu_count = map_cpu["cpu_count"].get_int();
            if(map_cpu.count("cpu_socket_count") > 0)
                this->cpu_socket_count = map_cpu["cpu_socket_count"].get_int();
            //this->cpu_model = Common::regex_rows_column(cpu_info, ".*Model name.+", 1, ":").at(0);
            //this->cpu_stepping = Common::regex_rows_column(cpu_info, ".*Stepping.+", 1, ":").at(0);
        }
        if(!dmi_info.empty()) {
            this->bios_vender = Common::regex_rows_column(dmi_info, ".*Vendor.+", 1, ":").at(0);
            this->bios_ver = Common::regex_rows_column(dmi_info, ".*Version.+", 1, ":").at(0);
            this->bios_date = Common::regex_rows_column(dmi_info, ".*Release Date.+", 1, ":").at(0);
            this->server_model = Common::regex_rows_column(dmi_info, ".*Product Name.+", 1, ":").at(0);
        }
        if(!bmc_summary.empty()) {
            this->bmc_ver = Common::regex_rows_column(bmc_summary, ".*Firmware Revision.+", 1, ":").at(0);
            this->bmc_date = Common::regex_rows_column(bmc_summary, ".*Build Time.+", 1, ":").at(0);
        }

        vector<string> t_mem_model = Common::regex_rows_column(dmi_info, ".*Part Number.+", 1, ":");
        if(!t_mem_model.empty()) {
            this->mem_model = t_mem_model.at(1);
            string tmp;
            tmp = ".*" + this->mem_model + ".+";
            vector<string> t_mem_count = Common::regex_rows(dmi_info, tmp);
            this->mem_count = static_cast<int>(t_mem_count.size());
        }
        stringstream t_str;
        t_str << Common::regex_rows_column(cpu_info, ".*Socket.+", 1)[0];
        t_str >> this->cpu_socket_count;
        Common::stringstream_clear(t_str);
        vector<string> t_mem_channel_count = Common::regex_rows_column(dmi_info, ".*Number Of Devices.+", 1, ":");
        if(!t_mem_channel_count.empty()) {
            t_str << t_mem_channel_count.at(0);
            t_str >> this->mem_channel_count;
            Common::stringstream_clear(t_str);
        }
    } catch(Exception e){
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

