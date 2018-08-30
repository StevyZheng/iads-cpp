//
// Created by root on 8/7/18.
//

#ifndef IADS_BURNINTEST_H
#define IADS_BURNINTEST_H

#include "../eigen3.3.5/Dense"
#include "../linux/SystemInfo.h"


class BurnInTest {
public:
    static void burn_cpu_mem();
    static void mem_badblock();
};


#endif //IADS_BURNINTEST_H
