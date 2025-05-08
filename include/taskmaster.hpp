#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <string>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

class TaskManager {
public:
    void add_task(const std::string &command);
    void list_tasks();
    json read_tasks();
    void set_complete(const std::string task_name);
    void create_task(std::string &base_path, const std::string user_name);
    void change_priority(const std::string task_name);
    void change_taskname(const std::string task_name);
    void change_taskdes(const std::string task_name);
    void remove_task(const std::string task_name);
    bool check_command(const int base_length, const std::string command);
    void cls();
    std::vector<std::string> tokenize(const std::string &command);
    bool check_command_syntax(const std::string &command,const std::vector<std::pair<std::string, std::string>> commands);
    void handle_commands(const std::string &command, const std::vector<std::pair<std::string, std::string>> commands);

private:
    std::string tasks = "tasks.json";
    std::string fixed_dir = "users";
};

class UserManager{
private:
    std::string fixed_dir = "users";
public :
    void acc(std::string &user_name, UserManager &usm, std::string &base_path, std::string &user_password, bool &logged_in, TaskManager &tsm);
    void createdir(std::string &base_path);
    bool checkdir(std::string &base_path);
    void sign_in(const std::string user_name, const std::string user_password, std::string &base_path);
    bool log_in(const std::string user_password,const std::string user_name, std::string &base_path);
    bool check_acc(std::string &base_path, const std::string user_name);
};

#endif
