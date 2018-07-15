//
// Created by root on 7/14/18.
//

#ifndef IADS_COMMON_H
#define IADS_COMMON_H

#include "../stevy.h"

struct Common {
    static vector<string> regex_rows(string src_str, string reg_str);
    static vector<string> regex_rows_column(string src_str, string reg_str, int column);

    static bool exeist_file(string file_path);
    static bool exeist_files(vector<string> file_paths);
    static int write(string file_path, string str, bool append=true);
    static string read(string file_path, int& return_code);
    static string read_trim(string file_path, int& return_code);
    static string trim(string src_str);
    static vector<string> split_lines(string src_str);
    static vector<string> split_string(string src_str, string reg_str="\\s+");
};


#endif //IADS_COMMON_H
