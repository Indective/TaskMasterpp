#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class TaskManager {
public:
    bool check_command_syntax(const std::string &command,const std::vector<std::pair<std::string, std::string>> commands);
    void handle_commands(const std::string &command, const std::vector<std::pair<std::string, std::string>> commands);

private:
    void add_task(const std::string &command);
    void list_tasks();
    json read_tasks();
    void set_complete(const std::string task_name);
    void change_priority(const std::string task_name);
    void change_taskname(const std::string task_name);
    void change_taskdes(const std::string task_name);
    void remove_task(const std::string task_name);
    bool check_command(const int base_length, const std::string command);
    void cls();
    std::vector<std::string> tokenize(const std::string &command);
    std::string tasks = "tasks.json";
    std::string fixed_dir = "users";
    
protected:
    void create_task(std::string_view base_path, const std::string user_name);
};
#endif
