#include "taskmaster.h"
#include "usermanager.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;

int main()
{
    TaskManager task_mgr;
    UserManager user_mgr;
    std::string base_path = fs::current_path().parent_path().string();
    std::string command, user_name, user_password, task_name;
    bool logged_in = false;

    const std::vector<std::pair<std::string, std::string>> commands = 
    {
        {"add",        "Add a new task"},
        {"list",       "List all tasks"},
        {"done",       "Mark a task as complete"},
        {"rename",     "Rename a task"},
        {"describe",   "Change the task's description"},
        {"priority",   "Set or change task priority"},
        {"remove",     "Delete a task"},
        {"cls",      "Clear the terminal screen"},
        {"exit",       "Exit the program"},
        {"--help",     "Show all available commands with descriptions"}
    };
    

    user_mgr.createdir(base_path);
    user_mgr.acc(user_name, base_path, user_password, logged_in);

    while (logged_in)
    {   
        try
        {
            std::cout << std::endl <<"> ";
            std::getline(std::cin, command);
            if(task_mgr.check_command_syntax(command, commands))
            {
                task_mgr.handle_commands(command, commands);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    
    return 0;
}
