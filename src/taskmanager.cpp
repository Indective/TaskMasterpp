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
        std::string task_pri;
        std::cout << "Enter task name: ";
        std::getline(std::cin, task_name);
        std::cout << "Enter task description: ";
        std::getline(std::cin, task_des);
        std::cout << "Enter your task priority :";
        std::getline(std::cin,task_pri);

        json new_task = {
            {"task name", task_name},
            {"task des", task_des},
            {"task priority",task_pri},
            {"done", "false"}
        };
        
        json tasks = read_tasks();
        tasks.push_back(new_task);
        std::ofstream outputFile("tasks.json");
        outputFile << tasks.dump(4); 
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
        json data;
        inputFile >> data;
        inputFile.close();
                 
        for(auto task : data)
        {
            std::cout << "Task name : " << task["task name"] << std::endl;
            std::cout << "Task des : " << task["task des"] << std::endl;
            std::cout << "Task Priority : " << task["task priority"] << std::endl;
            std::cout << "Done ?  : " << task["done"] << std::endl << "\n";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

json TaskManager::read_tasks()
{
    json data;
    try
    {
        std::ifstream inputFile(tasks);
        std::cout << fs::current_path().string();

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
    return data;
}

void TaskManager::set_complete(const std::string task_name)
{
    try
    {
        std::ifstream inputFile(tasks);
        json tasksData;
        inputFile >> tasksData;
        inputFile.close();

        bool found = false;

        for (auto& task : tasksData)
        {
            if (task["task name"] == task_name)
            {
                task["done"] = "true";
                found = true;
                break;
            }
        }

        if (found)
        {
            std::ofstream outputFile(tasks);
            outputFile << tasksData.dump(4); 
            outputFile.close();
        }
        else
        {
            std::cerr << "Task not found: " << task_name << '\n';
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error setting task complete: " << e.what() << '\n';
    }
    
}

void TaskManager::create_task(std::string &base_path, const std::string user_name)
{
    try
    {
        if(fs::current_path().filename() == user_name)
        {
            std::ofstream outfile(tasks);       
        }
        else if (fs::current_path().filename() == fixed_dir)
        {
            fs::current_path(fs::current_path().string() + "/" + user_name);
            std::ofstream outfile(tasks);  
        }
        else
        {
            fs::current_path(fs::current_path().string() + "/" + fixed_dir + "/" + user_name);
            std::ofstream outfile(tasks);  
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void TaskManager::change_priority(const std::string task_name)
{
    try
    {
        std::ifstream inputFile(tasks);
        json tasksData;
        std::string pri;
        inputFile >> tasksData;
        inputFile.close();

        bool found = false;

        std::cout << "Enter your task priority : ";
        std::getline(std::cin,pri);

        for (auto& task : tasksData)
        {
            if (task["task name"] == task_name)
            {
                task["task priority"] = pri;
                found = true;
                break;
            }
        }

        if (found)
        {
            std::ofstream outputFile(tasks);
            outputFile << tasksData.dump(4); 
            outputFile.close();
        }
        else
        {
            std::cerr << "Task not found: " << task_name << '\n';
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error setting task complete: " << e.what() << '\n';
    }
}

void TaskManager::change_taskname(const std::string task_name)
{
    try
    {
        std::ifstream inputFile(tasks);
        json tasksData;
        std::string ts_name;
        inputFile >> tasksData;
        inputFile.close();

        bool found = false;

        std::cout << "Enter new task name : ";
        std::getline(std::cin,ts_name);

        for (auto& task : tasksData)
        {
            if (task["task name"] == task_name)
            {
                task["task name"] = ts_name;
                found = true;
                break;
            }
        }

        if (found)
        {
            std::ofstream outputFile(tasks);
            outputFile << tasksData.dump(4); 
            outputFile.close();
        }
        else
        {
            std::cerr << "Task not found: " << task_name << '\n';
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error setting task complete: " << e.what() << '\n';
    }
}

void TaskManager::change_taskdes(const std::string task_name)
{
    try
    {
        std::ifstream inputFile(tasks);
        json tasksData;
        std::string des;
        inputFile >> tasksData;
        inputFile.close();

        bool found = false;

        std::cout << "Enter new task description : ";
        std::getline(std::cin,des);

        for (auto& task : tasksData)
        {
            if (task["task name"] == task_name)
            {
                task["task des"] = des;
                found = true;
                break;
            }
        }

        if (found)
        {
            std::ofstream outputFile(tasks);
            outputFile << tasksData.dump(4); 
            outputFile.close();
        }
        else
        {
            std::cerr << "Task not found: " << task_name << '\n';
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error setting task complete: " << e.what() << '\n';
    }
}

void TaskManager::remove_task(const std::string task_name)
{
    try
    {
        json data = read_tasks();
        for (auto it = data.begin(); it != data.end(); ) {
            if ((*it)["task name"] == task_name) {
                it = data.erase(it); // erase returns the next valid iterator
            } else {
                ++it;
            }
        }
        std::cout << "Task deleted." << std::endl;
    
        std::ofstream outFile(tasks);
        if (outFile.is_open()) {
            outFile << data.dump(4);  // Pretty-print with indentation
            outFile.close();
        } else {
            std::cerr << "Failed to write to file.\n";
            return;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
