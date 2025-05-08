#include "taskmaster.hpp"
#include  <json.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib> // for std::getenv and system()
#include <vector>
#include <iomanip> // for std::quoted

using json = nlohmann::json;
namespace fs = std::filesystem;

void TaskManager::add_task(const std::string &command)
{
    try
    {  
        std::vector<std::string> tokens = tokenize(command);
        if (tokens.size() != 7)
        {
            std::cout << "Invalid command syntax" << std::endl;
            std::cout << "command structure must be <tsm add [quoted command name] --description [quoted discreption] --priority [quoted priority]>" << std::endl;

        }
        else
        {
            json new_task = {
                {"task name", tokens[2]},
                {"task des", tokens[4]},
                {"task priority",tokens[6]},
                {"done", "false"}
            };
            
            json tasks = read_tasks();
            tasks.push_back(new_task);
            std::ofstream outputFile("tasks.json");
            outputFile << tasks.dump(4); 
            outputFile.close();
            std::cout << "Tasks successfully stored";
        }
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
                if(task["done"] == "true")
                {
                    std::cout << "Task already set as completed." << std::endl;
                    return;
                }
                else
                {
                    task["done"] = "true";
                    found = true;
                    break;
                }
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

bool TaskManager::check_command(const int base_length, const std::string command)
{
    //base length = tsm + {command name} length
    std::string letter = command.substr(base_length);
    if(letter.empty() or letter == " ")
    {
        return false;
    }
    return true;
}

void TaskManager::cls()
{
    #ifdef _WIN32
        if (std::getenv("TERM")) {
            std::cout << "\033[2J\033[H" << std::flush;
        } else {
            system("cls");
        }
    #else
        std::cout << "\033[2J\033[H" << std::flush;
    #endif   
}

std::vector<std::string> TaskManager::tokenize(const std::string &command)
{
    std::vector<std::string> tokens;
    try
    {
        std::istringstream iss(command);
        std::string token;
    
        while (iss >> std::quoted(token)) {
            tokens.push_back(token);
        }
    
        return tokens;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return tokens;
}

bool TaskManager::check_command_syntax(const std::string &command, const std::vector<std::pair<std::string, std::string>> commands)
{
    try
    {
        std::vector<std::string> tokens = tokenize(command);
        if(tokens[0] != "tsm")
        {
            std::cout << "Invalid command syntax; command must start with <tsm>." << std::endl;
            return false;
        }
        else
        {
            for(const auto &i: commands)
            {
                if(i.first == tokens[1])  // Validate command: tokens[1] must match a known command
                {
                    return true;
                }
            }
            std::cout << "Invalid command syntax; command does not exist." << std::endl;
            std::cout << "Use <tsm --help> to see all current commands." << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return false;
}

void TaskManager::handle_commands(const std::string &command, const std::vector<std::pair<std::string, std::string>> commands)
{
    try
    {
        std::vector<std::string> tokens = tokenize(command);
        if (tokens[1] == "add")
        {
            add_task(command);
        }
        else if(tokens[1] == "list")
        {
            list_tasks();
        }
        else if(tokens[1] == "done")
        {
            set_complete(tokens [2]);
        }
        else if(tokens[1] == "rename")
        {
            change_taskname(tokens[2]);
        }
        else if(tokens[1] == "describe")
        {
            change_taskdes(tokens[1]);
        }
        else if(tokens[1] == "priority")
        {
            change_priority(tokens[1]);
        }
        else if(tokens[1] == "remove")
        {
            remove_task(tokens[1]);
        }
        else if(tokens[1] == "cls")
        {
            cls();
        }
        else if(tokens[1] == "--help")
        {
            for(const auto &i : commands)
            {
                std::cout << i.first << "  -  " << i.second << std::endl;
            }
        }
        else if(tokens[1] == "exit")
        {
            exit(0);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
