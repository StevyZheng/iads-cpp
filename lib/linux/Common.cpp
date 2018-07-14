//
// Created by root on 7/14/18.
//

#include "Common.h"
#include <fstream>
#include <iostream>

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

vector<string> Common::regex_rows_column(string src_str, string reg_str, int column) {
    vector<string> ret;
    boost::regex reg(reg_str);
    boost::sregex_iterator pos(src_str.begin(), src_str.end(), reg, boost::match_not_dot_newline);
    boost::sregex_iterator end;
    while(pos != end){
        vector<string> buf = Common::split_string((*pos)[0]);
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

