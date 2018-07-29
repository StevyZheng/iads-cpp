//
// Created by root on 7/14/18.
//

#include "Common.h"
#include <fstream>


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

vector<string> Common::regex_rows(string src_str, string reg_str, bool if_trim) {
    vector<string> ret;
    boost::regex reg(reg_str);
    boost::sregex_iterator pos(src_str.begin(), src_str.end(), reg, boost::match_not_dot_newline);
    boost::sregex_iterator end;
    while(pos != end){
        if(if_trim)
            ret.emplace_back(Common::trim((*pos)[0]));
        else
            ret.emplace_back((*pos)[0]);
        ++pos;
    }
    return ret;
}

vector<string> Common::regex_rows_column(string src_str, string reg_str, int column, string reg_split, bool if_trim) {
    vector<string> ret;
    boost::regex reg(reg_str);
    boost::sregex_iterator pos(src_str.begin(), src_str.end(), reg, boost::match_not_dot_newline);
    boost::sregex_iterator end;
    while(pos != end){
        vector<string> buf;
        if(if_trim)
            buf = Common::split_string((*pos)[0], reg_split);
        else
            buf = Common::split_string((*pos)[0], reg_split, false);
        if(column >= 0 && column < buf.size())
            ret.emplace_back(buf[column]);
        else
            break;
        ++pos;
    }
    return ret;
}

vector<string> Common::split_string(string src_str, string reg_str, bool if_trim) {
    vector<string> ret;
    boost::regex re(reg_str);
    boost::sregex_token_iterator i(src_str.begin(), src_str.end(), re, -1);
    boost::sregex_token_iterator j;
    while(i != j){
        if(if_trim)
            ret.emplace_back(Common::trim(*i));
        else
            ret.emplace_back(*i);
        i++;
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

void Common::stringstream_clear(stringstream &stringstream_buf) {
    stringstream_buf.str("");
    if(stringstream_buf.eof())
        stringstream_buf.clear();
}

string Common::get_current_dir() {
    string now_dir;
    char s_now_dir[1024] = {0};
    int cnt = static_cast<int>(readlink("/proc/self/exe", s_now_dir, 1024));
    if(cnt < 0 || cnt >=1024) {
        throw runtime_error("get_current_dir: readlink error.");
        exit;
    }
    for(int i=cnt; i>=0; --i){
        if(s_now_dir[i] == '/'){
            s_now_dir[i+1] = '\0';
            break;
        }
    }
    now_dir = s_now_dir;
    return now_dir;
}

map<string, DataType> Common::parse_cpu_info() {
    int tt;
    set<string> str_set;
    DataType data;
    map<string, DataType> cpu_info_map;
    string cpu_info = Common::read("/proc/cpuinfo", tt);
    vector<string> processors = Common::regex_rows_column(cpu_info, ".*processor.+", 1, ":");
    data.set_int(static_cast<int>(processors.size()));
    cpu_info_map.insert(pair<string, DataType>("thread_num", data));
    data.clear();
    vector<string> physicals = Common::regex_rows_column_uniq(cpu_info, ".*physical id.+", 1, ":");
    data.set_int(static_cast<int>(physicals.size()));
    cpu_info_map.insert(pair<string, DataType>("cpu_count", data));
    data.clear();
    vector<string> cpu_model = Common::regex_rows_column_uniq(cpu_info, ".*model name.+", 1, ":");
    if(cpu_model.size() == 1){
        data.set_str(cpu_model[0]);
        cpu_info_map.insert(pair<string, DataType>("cpu_model", data));
        data.clear();
    } else{
        perror("cpu model error: have more than one cpu model!");
        STLEx::print_vector(cpu_model);
    }
    vector<string> cpu_stepping = Common::regex_rows_column_uniq(cpu_info, ".*stepping.+", 1, ":");
    if(cpu_stepping.size() == 1){
        data.set_str(cpu_stepping[0]);
        cpu_info_map.insert(pair<string, DataType>("cpu_stepping", data));
        data.clear();
    } else{
        perror("cpu stepping error!");
    }
    stringstream cpu_socket_num; int cpu_socket_n;
    cpu_socket_num << Command::shell_exec("dmidecode -t4|grep Socket.Designation:|wc -l", tt);
    if(cpu_socket_num.str().length() > 0)
        cpu_socket_num >> cpu_socket_n;
    else
        cpu_socket_n = 0;
    data.set_int(cpu_socket_n);
    cpu_info_map.insert(pair<string, DataType>("cpu_socket_count", data));
    data.clear();

    return cpu_info_map;
}

vector<string> Common::regex_rows_uniq(string src_str, string reg_str, bool if_trim) {
    vector<string> tmp = Common::regex_rows(std::move(src_str), std::move(reg_str), if_trim);
    STLEx::vector_uniq(tmp);
    return tmp;
}

void STLEx::vector_uniq(vector<string> &v) {
    vector<string>::iterator vector_iterator;
    sort(v.begin(),v.end());
    vector_iterator = unique(v.begin(),v.end());
    if(vector_iterator != v.end()){
        v.erase(vector_iterator,v.end());
    }
}

vector<string>
Common::regex_rows_column_uniq(string src_str, string reg_str, int column, string reg_split, bool if_trim) {
    vector<string> tmp = Common::regex_rows_column(std::move(src_str), std::move(reg_str), column, std::move(reg_split), if_trim);
    STLEx::vector_uniq(tmp);
    return tmp;
}

void STLEx::print_vector(vector<string> v) {
    if(v.size()>0)
        for(int i=0;i<int(v.size());i++)
            cout << v[i] << endl;
    else
        cout << "none";
    cout << endl;
}

vector<string> STLEx::vectors_set_union(vector<string> v1, vector<string> v2) {
    vector<string> v;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));
    return v;
}

long STLEx::vector_find(vector<string> v, string element) {
    vector<string>::iterator it;
    it = find(v.begin(), v.end(), element);
    if(it == v.end())
        return -1;
    else
        return std::distance(std::begin(v), it);
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
