//
// Created by root on 7/15/18.
//

#ifndef IADS_STORAGE_H
#define IADS_STORAGE_H

#include <utility>

#include "../stevy.h"


class Phy{
public:
    Phy() = default;

    explicit Phy(string phy_name){
        this->phy_name = phy_name;
    }

private:
    string phy_name;
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
