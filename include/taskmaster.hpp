#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <string>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

class TaskManager {
public:
    void add_task();
    void list_tasks();
    json read_tasks();
    void set_complete(const std::string task_name);

private:
    std::string tasks = "tasks.json";
};

class UserManager{
private:
    std::string fixed_dir = "users";
public :
    void createdir(std::string &base_path);
    bool checkdir(std::string &base_path);
    void sign_in(const std::string user_name, const char* user_password, std::string &base_path);
    bool log_in(const char* user_password,const std::string user_name, std::string &base_path);
    bool check_acc(std::string &base_path, const std::string user_name);
};

#endif
