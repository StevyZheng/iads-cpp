//
// Created by root on 7/14/18.
//

#ifndef IADS_COMMONHW_H
#define IADS_COMMONHW_H

#include <string>
#include "Command.h"
#include "Common.h"
using namespace std;

struct SystemInfo {
    SystemInfo() = default;
    void init();

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
