//
// Created by root on 7/14/18.
//

#ifndef IADS_COMMONHW_H
#define IADS_COMMONHW_H

#include "Command.h"
#include "Common.h"

struct SystemInfo {
    SystemInfo() = default;
    void init();
    string to_json();

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
};


#endif //IADS_COMMONHW_H
