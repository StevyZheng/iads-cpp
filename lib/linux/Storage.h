//
// Created by root on 7/15/18.
//

#ifndef IADS_STORAGE_H
#define IADS_STORAGE_H

#include <utility>

#include "../stevy.h"
#include "Common.h"

enum PhyCount{
    invalid_dword_count,
    loss_of_dword_sync_count,
    phy_reset_problem_count,
    running_disparity_error_count
};

class Phy{
public:
    Phy() = default;

    explicit Phy(string phy_name){
        this->phy_name = std::move(phy_name);
        this->invalid_dword_count = -1;
        this->loss_of_dword_sync_count = -1;
        this->phy_reset_problem_count = -1;
        this->running_disparity_error_count = -1;
    }

    static vector<string> scan_phys_name();
    static vector<Phy> scan_phys();
    static string phys_to_table();
    static string err_phys_to_table();

    void fill_attrs();
    long long get_err_attr(PhyCount err_name);
    void clear(){
        this->invalid_dword_count = 0;
        this->loss_of_dword_sync_count = 0;
        this->phy_reset_problem_count = 0;
        this->running_disparity_error_count = 0;
    }
    string get_phy_name(){
        return this->phy_name;
    }
    string get_sas_addr(){
        return this->sas_addr;
    }

private:
    string phy_name;
    long long invalid_dword_count;
    long long loss_of_dword_sync_count;
    long long phy_reset_problem_count;
    long long running_disparity_error_count;
    string sas_addr;
};


class Disk{
public:
    Disk() = default;
};


class Hba{};


class Raid{};


class Storage {

};

#endif //IADS_STORAGE_H
