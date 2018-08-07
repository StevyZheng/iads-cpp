//
// Created by root on 8/7/18.
//

#include "BurnInTest.h"

void BurnInTest::burn_cpu_mem() {
    vector<string> cpus = Common::list_dirs("/sys/devices/virtual/cpuid");
    int cpu_count = static_cast<int>(cpus.size());
    long long every_mem_size = 1024 * 1024 * 1024;
    long long mem_init_size = SystemInfo::get_avail_mem_size();
    long long cpu_mem_size = 99416 * 1024 * cpu_count;
    long long mem_size = static_cast<long long int>((mem_init_size - cpu_mem_size) * 0.9);
    int mem_pro_count = static_cast<int>(mem_size / every_mem_size);
    long long free_mem_size = mem_size % every_mem_size;

    int th_count = cpu_count + mem_pro_count;
    ThreadPool tp(static_cast<size_t>(th_count));

    for(int i=0; i<cpu_count; i++){
        tp.enqueue([] {
            using Eigen::MatrixXd;
            MatrixXd m = MatrixXd::Random(3000,3000);
            while(true)
                m * m;
        });
    }
    for(int i=0; i<mem_pro_count; i++){
        tp.enqueue([every_mem_size] {
            auto * p = new char[every_mem_size];
            for (char *q = p; q != nullptr; q++){
               *q = 0;
               *q = 'a';
            }
        });
    }
}
