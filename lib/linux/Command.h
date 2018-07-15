//
// Created by root on 7/13/18.
//

#ifndef IADS_COMMAND_H
#define IADS_COMMAND_H

#include "../stevy.h"

class Command {
public:
    Command(string t_cmd, string name="default"){
        this->cmd = t_cmd;
        this->name = name;
        this->return_code = 0;
        this->result = "";
    }
    string get_name();
    void set_name(string name);
    string get_cmd();
    void set_cmd(string t_cmd);
    int get_return_code();
    string get_result();
    void exec();

    static string shell_exec(string cmd, int& return_code);
private:
    string cmd;
    string name;
    int return_code;
    string result;
};


class CommandPool {
public:
    CommandPool() = default;
    void add_command(Command cmd);
    void add_command(string cmd_str, string name="default");
    void delete_command(string name);
    void delete_command(int index);
    string exec_one(int index);
    void exec_by_name(string name);
    void serial_exec_all();
    void parallel_exec_all();
    void clear();
    vector<Command> get_cmds();
private:
    vector<Command> cmds;
};


#endif //IADS_COMMAND_H
