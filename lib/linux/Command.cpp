//
// Created by root on 7/13/18.
//

#include "Command.h"

string Command::shell_exec(string cmd, int& return_code) {
    int count = 2048;
    char* buffer = new char[count];
    string ret;
    FILE* stream = popen(cmd.c_str(), "r");
    if(nullptr != stream){
        while(fgets(buffer, count, stream))
            ret += buffer;
        pclose(stream);
    }else
        return_code = -1;
    delete[](buffer);
    return_code = 1;
    return ret;
}

void Command::exec() {
    int code;
    this->result = Command::shell_exec(this->cmd, code);
    this->return_code = code;
}

string Command::get_name() {
    return this->name;
}

void Command::set_name(string name) {
    this->name = name;
}

string Command::get_cmd() {
    return this->cmd;
}

void Command::set_cmd(string t_cmd) {
    this->cmd = t_cmd;
}

int Command::get_return_code() {
    return this->return_code;
}

string Command::get_result() {
    return this->result;
}

void CommandPool::add_command(Command cmd) {
    this->cmds.emplace_back(cmd);
}

void CommandPool::add_command(string cmd_str, string name) {
    Command t_cmd(cmd_str, name);
    this->cmds.emplace_back(t_cmd);
}

void CommandPool::delete_command(string name) {
    for(auto it=this->cmds.begin(); it!=this->cmds.end(); it++){
        if(name == it->get_name())
            it = this->cmds.erase(it);
    }
}

void CommandPool::delete_command(int index) {
    this->cmds.erase(this->cmds.begin() + index);
}

void CommandPool::clear() {
    this->cmds.clear();
}

string CommandPool::exec_one(int index) {
    this->cmds[index].exec();
    return this->cmds[index].get_result();
}

void CommandPool::exec_by_name(string name) {
    for(auto c: this->cmds){
        if(name == c.get_name())
            c.exec();
    }
}

void CommandPool::serial_exec_all() {
    for(auto c: this->cmds)
        c.exec();
}

void CommandPool::parallel_exec_all() {
    size_t pool_size = this->cmds.size();
    ThreadPool tp(pool_size);
    for(auto it=this->cmds.begin(); it!=this->cmds.end(); it++){
        tp.enqueue([it] {
            it->exec();
        });
    }
}

vector<Command> CommandPool::get_cmds() {
    return this->cmds;
}
