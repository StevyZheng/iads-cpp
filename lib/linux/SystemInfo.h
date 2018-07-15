//
// Created by root on 7/14/18.
//

#ifndef IADS_COMMONHW_H
#define IADS_COMMONHW_H

#include "Command.h"
#include "Common.h"

struct SystemInfo {
    SystemInfo(){
        this->ry_sn = this->sm_sn = this->server_model = this->cpu_model = "";
        this->cpu_count = this->mem_count = this->mem_channel_count = 0;
        this->cpu_stepping = this->mem_model = this->bios_vender = this->bios_ver = "";
        this->bios_date = this->bmc_ver = this->bmc_date = this->os_ver = this->kernel_ver = "";
    };
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
