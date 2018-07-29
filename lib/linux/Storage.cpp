//
// Created by root on 7/15/18.
//

#include "Storage.h"

vector<string> Phy::scan_phys_name() {
    vector<string> ret;
    string t_path = "/sys/class/sas_phy";
    if(Common::exeist_file(t_path))
        ret = Common::list_dirs(t_path);
    else
        perror("has no sas_phys!");
    return ret;
}

long long Phy::get_err_attr(PhyCount err_name) {
    switch(err_name){
        case PhyCount::running_disparity_error_count:
            return this->running_disparity_error_count;
        case PhyCount::phy_reset_problem_count:
            return this->phy_reset_problem_count;
        case PhyCount::loss_of_dword_sync_count:
            return this->loss_of_dword_sync_count;
        case PhyCount::invalid_dword_count:
            return this->invalid_dword_count;
        default:
            return -1;
    }
}

void Phy::fill_attrs() {
    string phys_path = "/sys/class/sas_phy/";
    stringstream buf;
    int retcode;
    buf << Common::read_trim(phys_path+this->phy_name+"/invalid_dword_count", retcode);
    buf >> this->invalid_dword_count;
    Common::stringstream_clear(buf);
    buf << Common::read_trim(phys_path+this->phy_name+"/running_disparity_error_count", retcode);
    buf >> this->running_disparity_error_count;
    Common::stringstream_clear(buf);
    buf << Common::read_trim(phys_path+this->phy_name+"/phy_reset_problem_count", retcode);
    buf >> this->phy_reset_problem_count;
    Common::stringstream_clear(buf);
    buf << Common::read_trim(phys_path+this->phy_name+"/loss_of_dword_sync_count", retcode);
    buf >> this->loss_of_dword_sync_count;
    Common::stringstream_clear(buf);
    buf << Common::read_trim(phys_path+this->phy_name+"/sas_address", retcode);
    buf >> this->sas_addr;
}

vector<Phy> Phy::scan_phys() {
    vector<Phy> phys;
    for(auto p: Phy::scan_phys_name()){
        Phy pt(p);
        pt.fill_attrs();
        phys.emplace_back(pt);
    }
    return phys;
}

string Phy::phys_to_table() {
    ConsoleTable sysinfo_table(6);
    auto *buf = new ostringstream;
    Row header = {"phy_name", "invalid_dword_count", "loss_of_dword_sync_count", "phy_reset_problem_count",\
                    "running_disparity_error_count", "sas_addr"};
    sysinfo_table.AddNewRow(header);
    vector<Phy> phys = Phy::scan_phys();
    stringstream buf_c;
    string ti, tl, tp, tr;
    for(auto i: phys){
        buf_c << i.get_err_attr(PhyCount::invalid_dword_count);
        buf_c >> ti;
        Common::stringstream_clear(buf_c);
        buf_c << i.get_err_attr(PhyCount::loss_of_dword_sync_count);
        buf_c >> tl;
        Common::stringstream_clear(buf_c);
        buf_c << i.get_err_attr(PhyCount::phy_reset_problem_count);
        buf_c >> tp;
        Common::stringstream_clear(buf_c);
        buf_c << i.get_err_attr(PhyCount::running_disparity_error_count);
        buf_c >> tr;
        sysinfo_table.AddNewRow({i.get_phy_name(), ti, tl, tp, tr, i.get_sas_addr()});
    }
    sysinfo_table.WriteTable(Align::Center, buf);
    return buf->str();
}

string Phy::err_phys_to_table() {
    ConsoleTable sysinfo_table(6);
    auto *buf = new ostringstream;
    Row header = {"phy_name", "invalid_dword_count", "loss_of_dword_sync_count", "phy_reset_problem_count",\
                    "running_disparity_error_count", "sas_addr"};
    sysinfo_table.AddNewRow(header);
    vector<Phy> phys = Phy::scan_phys();
    stringstream buf_c;
    string ti, tl, tp, tr;
    long long til, tll, tpl, trl;
    for(auto i: phys){
        til = i.get_err_attr(PhyCount::invalid_dword_count);
        buf_c << til;
        buf_c >> ti;
        Common::stringstream_clear(buf_c);
        tll = i.get_err_attr(PhyCount::loss_of_dword_sync_count);
        buf_c << tll;
        buf_c >> tl;
        Common::stringstream_clear(buf_c);
        tpl = i.get_err_attr(PhyCount::phy_reset_problem_count);
        buf_c << tpl;
        buf_c >> tp;
        Common::stringstream_clear(buf_c);
        trl = i.get_err_attr(PhyCount::running_disparity_error_count);
        buf_c << trl;
        buf_c >> tr;
        if(til > 0 || tll > 0 || tpl > 0|| trl > 0)
            sysinfo_table.AddNewRow({i.get_phy_name(), ti, tl, tp, tr, i.get_sas_addr()});
    }
    sysinfo_table.WriteTable(Align::Center, buf);
    return buf->str();
}
