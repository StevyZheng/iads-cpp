//
// Created by root on 7/14/18.
//

#include "Common.h"
#include <fstream>
#include <utility>


int Common::write(string file_path, string str, bool append) {
    ofstream fs;
    if(append)
        fs.open(file_path.c_str(), ios::app);
    else
        fs.open(file_path.c_str());
    if(!fs.is_open())
        return -1;
    fs << str;
    fs.close();
    return 1;
}

string Common::read(string file_path, int &return_code) {
    ifstream fs(file_path.c_str());
    stringstream buffer;
    buffer << fs.rdbuf();
    string ret(buffer.str());
    return ret;
}

vector<string> Common::split_lines(string src_str) {
    vector<string> lines;
    string token;
    istringstream tokenStream(src_str);
    while(getline(tokenStream, token, '\n')){
        lines.emplace_back(token);
    }
    return lines;
}

string Common::trim(string src_str) {
    return boost::trim_copy(src_str);
}

vector<string> Common::regex_rows(string src_str, string reg_str) {
    vector<string> ret;
    boost::regex reg(reg_str);
    boost::sregex_iterator pos(src_str.begin(), src_str.end(), reg, boost::match_not_dot_newline);
    boost::sregex_iterator end;
    while(pos != end){
        ret.emplace_back((*pos)[0]);
        ++pos;
    }
    return ret;
}

vector<string> Common::regex_rows_column(string src_str, string reg_str, int column, string reg_split) {
    vector<string> ret;
    boost::regex reg(reg_str);
    boost::sregex_iterator pos(src_str.begin(), src_str.end(), reg, boost::match_not_dot_newline);
    boost::sregex_iterator end;
    while(pos != end){
        vector<string> buf = Common::split_string((*pos)[0], reg_split);
        if(column >= 0 && column < buf.size())
            ret.emplace_back(buf[column]);
        else
            break;
        ++pos;
    }
    return ret;
}

vector<string> Common::split_string(string src_str, string reg_str) {
    vector<string> ret;
    boost::regex re(reg_str);
    boost::sregex_token_iterator i(src_str.begin(), src_str.end(), re, -1);
    boost::sregex_token_iterator j;
    while(i != j){
        ret.emplace_back(*i++);
    }
    return ret;
}

string Common::read_trim(string file_path, int &return_code) {
    return Common::trim(Common::read(std::move(file_path), return_code));
}

bool Common::exeist_file(string file_path) {
    struct stat file_stat;
    return (stat(file_path.c_str(), &file_stat) == 0);
}

bool Common::exeist_files(vector<string> file_paths) {
    struct stat file_stat;
    for(auto &f: file_paths){
        if(0 != stat(f.c_str(), &file_stat))
            return false;
    }
    return true;
}



void IoDemo::create_multi_dirs(string file_path, int multi_num) {
    int group_num = multi_num / MAX_THREAD_NUM;
    int group_mod = multi_num % MAX_THREAD_NUM;
    int i = 0, j = 0;
    for(; i < group_num; i++){
        ThreadPool tp(static_cast<size_t>(MAX_THREAD_NUM));
        for (j = 0; j < MAX_THREAD_NUM; j++) {
            stringstream file_name;
            file_name << file_path + "/" << i << "_" << j;
            string file_name_str = file_name.str();
            try {
                tp.enqueue([file_name_str] {
                    int status = mkdir(file_name_str.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
                    if (status)
                        throw runtime_error("create dir failed!");
                });
            }catch(exception& e){
                cout << e.what() << endl;
            }
        }
    }
    if(0 != group_mod){
        ThreadPool tp(static_cast<size_t>(group_mod));
        for (j = 0; j < group_mod; j++) {
            stringstream file_name;
            file_name << file_path + "/" << i << "_" << j;
            string file_name_str = file_name.str();
            try {
                tp.enqueue([file_name_str] {
                    int status = mkdir(file_name_str.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
                    if (status)
                        throw runtime_error("create dir failed!");
                });
            }catch(exception& e){
                cout << e.what() << endl;
            }
        }
    }
}

void IoDemo::create_multi_files(string file_path, int multi_num, long file_size) {
    int group_num = multi_num / MAX_THREAD_NUM;
    int group_mod = multi_num % MAX_THREAD_NUM;
    int i = 0, j = 0;
    for(; i < group_num; i++){
        ThreadPool tp(static_cast<size_t>(MAX_THREAD_NUM));
        for (j = 0; j < MAX_THREAD_NUM; j++) {
            stringstream file_name;
            file_name << file_path + "/" << i << "_" << j;
            string file_name_str = file_name.str();
            try {
                tp.enqueue([file_name_str, file_size] {
                    ofstream ofile(file_name_str.c_str());
                    auto* pBuf = new char[file_size];
                    memset(pBuf, 0, static_cast<size_t>(file_size));
                    ofile << pBuf;
                    ofile.close();
                    delete[] pBuf;
                });
            }catch(exception& e){
                cout << e.what() << endl;
            }
        }
    }
    if(0 != group_mod){
        ThreadPool tp(static_cast<size_t>(group_mod));
        for (j = 0; j < group_mod; j++) {
            stringstream file_name;
            file_name << file_path + "/" << i << "_" << j;
            string file_name_str = file_name.str();
            try {
                tp.enqueue([file_name_str, file_size] {
                    ofstream ofile(file_name_str.c_str());
                    auto * pBuf = new char[file_size];
                    memset(pBuf, 0, static_cast<size_t>(file_size));
                    ofile << pBuf;
                    ofile.close();
                    delete[] pBuf;
                });
            }catch(exception& e){
                cout << e.what() << endl;
            }
        }
    }
}
