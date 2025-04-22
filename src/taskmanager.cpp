#include "taskmaster.hpp"
#include  <json.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

void TaskManager::add_task()
{
    try
    {   
        std::string task_name;
        std::string task_des;
        std::cout << "Enter task name: ";
        std::getline(std::cin, task_name);
        std::cout << "Enter task description: ";
        std::getline(std::cin, task_des);

        json new_task = {
            {"task name", task_name},
            {"task des", task_des},
            {"done", false}
        };
        
        json tasks = read_tasks();
        tasks.push_back(new_task);
        std::ofstream outputFile("tasks.json");
        outputFile << tasks.dump(4); // Dump with indentation
        outputFile.close();
        std::cout << "Tasks successfully stored";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}

void TaskManager::list_tasks()
{
    try
    {
        std::ifstream inputFile(tasks);
        json tasks;
        inputFile >> tasks;
    
        inputFile.close();
        
        for(auto &task : tasks)
        {
            std::cout << "Task name : " << task["task name"] << std::endl;
            std::cout << "Task des : " << task["task des"] << std::endl;
            std::cout << "Done ?  : " << (task["done"] ? "Yes" : "No")  << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

json TaskManager::read_tasks()
{
    try
    {
        std::ifstream inputFile(tasks);
        json data;
    
        if (inputFile.peek() != std::ifstream::traits_type::eof()) {
            inputFile >> data;
        } else {
            data = json::array();  // Start fresh if file is empty
        }
    
        return data;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

