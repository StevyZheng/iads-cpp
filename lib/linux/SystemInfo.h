//
// Created by root on 7/14/18.
//

#ifndef IADS_COMMONHW_H
#define IADS_COMMONHW_H

#include <utility>

#include "Command.h"
#include "Common.h"
#include "../ConsoleTable.h"

enum Json_all_str{
    JSON_ORIGINAL,
    JSON_ALL_STR
};

struct SystemInfo {
    SystemInfo();
    void init();
    string to_string();
    string to_json(Json_all_str all_str= Json_all_str::JSON_ORIGINAL);
    string to_table();
    static long long get_avail_mem_size();
    string get_info();
    vector<string> get_attr_value();

    string ry_sn;
    string sm_sn;
    string server_model;
    string cpu_model;
    int cpu_count;
    string cpu_stepping;
    int cpu_socket_count;
    string mem_model;
    int mem_count;
    int mem_channel_count;
    string bios_vender;
    string bios_ver;
    string bios_date;
    string bmc_ver;
    string bmc_date;
    string os_ver;
    string kernel_ver;

    vector<string> attr_vector;
    bool ipmicfg_exeist;
    bool dmi_exeist;
};

namespace dt = boost::gregorian;
namespace pt = boost::posix_time;
class SysLog{
public:
    SysLog(){
        this->log_file = "/var/log/messages";
        this->init_reg_err_arr();
    }

    explicit SysLog(string file_path){
        this->log_file = std::move(file_path);
        this->init_reg_err_arr();
    }
    void set_log_file(string file){ this->log_file = std::move(file); }
    void add_err_reg(vector<string> errs);
    void parse_log();
    vector<string> get_err_msg(){ return this->reg_err_arr; }
    string get_err_msg_str();
    string get_err_msg_table();
private:
    vector<string> err_msg;
    vector<string> reg_err_arr;
    string log_file;
    void init_reg_err_arr(){ this->reg_err_arr = {"error", "failed", "ecc", "Call Trace"}; }
};


#endif //IADS_COMMONHW_H
