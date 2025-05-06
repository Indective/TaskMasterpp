#include "taskmaster.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;

int main()
{
    TaskManager tsm;
    UserManager usm;
    std::string base_path = fs::current_path().parent_path().string();
    std::string command, user_name, user_password, task_name;
    bool logged_in = false;

    const std::vector<std::pair<std::string, std::string>> commands = {
        {"add", "Create a task"},
        {"list", "Lists Tasks"},
        {"done", "Sets task as completed"},
        {"cpri", "Changes task priority"},
        {"cts", "Changes task name"},
        {"ctd", "Changes task description"},
        {"rmt", "Deletes a task"},
        {"--help", "Lists all commands with explanations"},
        {"exit", "Shuts program off"},
        {"cls", "Clears terminal screen"},
        {"logout", "Logs out and prompt logging-in screen"}
    };

    usm.createdir(base_path);
    usm.acc(user_name, usm, base_path, user_password, logged_in, tsm);

    while (logged_in)
    {   std::cout << std::endl <<"> ";
        std::getline(std::cin, command);
        if(command.substr(0,3) != "tsm")
        {
            std::cerr << "Invalid command syntax" << std::endl;
        }
        else
        {
            if (command.substr(4,3) == "add") {tsm.add_task();}
            else if (command.substr(4,4) == "list") {tsm.list_tasks();}
            else if (command.substr(4,4) == "exit") {logged_in = false;}
            else if (command.substr(4,4) == "done") 
            {
                if(tsm.check_command(8,command))
                {
                    task_name = command.substr(9); 
                    tsm.set_complete(task_name);
                }
                else
                {
                    std::cout << "Invalid command syntax" << std::endl;;
                }
            }
            else if (command.substr(4,4) == "cpri")
            {
                if(tsm.check_command(8,command))
                {
                    task_name = command.substr(9);
                    tsm.change_priority(task_name);
                }
                else
                {
                    std::cout << "Invalid command syntax" << std::endl;;
                }
            }
            else if(command.substr(4,3) == "cts")
            {
                if(tsm.check_command(7,command))
                {
                    task_name = command.substr(8);
                    tsm.change_taskname(task_name);
                }
                else
                {
                    std::cout << "Invalid command syntax" << std::endl;;
                }
            }
            else if(command.substr(4,3) == "ctd")
            {
                if(tsm.check_command(7,command))
                {
                    task_name = command.substr(8);
                    tsm.change_taskdes(task_name);
                }
                else
                {
                    std::cout << "Invalid command syntax" << std::endl;;
                }
            }
            else if(command.substr(4,3) == "rmt")
            {
                if(tsm.check_command(7,command))
                {
                    task_name = command.substr(8);
                    tsm.remove_task(task_name);
                }
                else
                {
                    std::cout << "Invalid command syntax" << std::endl;;
                }
            }
            else if(command.substr(4,6) == "--help")
            {
                for(const auto &i: commands)
                {
                    std::cout << i.first << i.second;
                }
            }
            else if(command.substr(4,3) == "cls")
            {
                tsm.cls();
            }
            else
            {
                std::cout << "Invalid command." << std::endl;
            }

            

        }
    }
    
    return 0;
}


