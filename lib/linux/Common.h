//
// Created by root on 7/14/18.
//

#ifndef IADS_COMMON_H
#define IADS_COMMON_H

#include "../stevy.h"
#include <ctime>
#include <utility>
#include "Command.h"

class DataType{
public:
    DataType(){
        this->clear();
    }
    void clear(){
        this->value_int = 0;
        this->value_str = "";
        this->type = "int";
    }
    bool if_int(){
        return this->type == "int";
    }
    bool if_str(){
        return this->type == "str";
    }
    void set_int(int value){
        this->set_type_int();
        this->value_int = value;
    }
    void set_str(string value){
        this->set_type_str();
        this->value_str = std::move(value);
    }
    int get_int(){
        if(if_int())
            return this->value_int;
        else
            return -1;
    }
    string get_str(){
        if(if_str())
            return this->value_str;
        else
            return "";
    }

private:
    void set_type_int(){
        this->type = "int";
    }
    void set_type_str(){
        this->type = "str";
    }

    int value_int;
    string value_str;
    string type;
};

struct Common {
    static vector<string> regex_rows(string src_str, string reg_str, bool if_trim = true);
    static vector<string> regex_rows_column(string src_str, string reg_str, int column, string reg_split="\\s+", bool if_trim= true);
    static vector<string> regex_rows_uniq(string src_str, string reg_str, bool if_trim=true);
    static vector<string> regex_rows_column_uniq(string src_str, string reg_str, int column, string reg_split="\\s+", bool if_trim= true);
    static vector<string> split_lines(string src_str);
    static vector<string> split_string(string src_str, string reg_str="\\s+", bool if_trim= true);

    static string trim(string src_str);
    static void stringstream_clear(stringstream& stringstream_buf);

    static bool exeist_file(string file_path);
    static bool exeist_files(vector<string> file_paths);
    static int write(string file_path, string str, bool append=true);
    static string read(string file_path, int& return_code);
    static string read_trim(string file_path, int& return_code);
    static string get_current_dir();

    static map<string, DataType> parse_cpu_info();
};

struct STLEx{
    static void vector_uniq(vector<string>& v);
    static void print_vector(vector<string> v);
    static vector<string> vectors_set_union(vector<string> v1,vector<string> v2);
    static long vector_find(vector<string> v, string element);
};


class Net{
private:
    string conf_path;
    vector<string> ports;
};

class IoDemo{
public:
    static void create_multi_dirs(string file_path, int multi_num);
    static void create_multi_files(string file_path, int multi_num, long file_size);
};


#endif //IADS_COMMON_H
