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

private:
    std::string tasks = "tasks.json";
};

#endif
