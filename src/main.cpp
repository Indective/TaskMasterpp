#include "taskmaster.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main()
{
    TaskManager tsm;

    std::string base_path = fs::current_path().parent_path().string();
    fs::current_path(base_path + "/" + "data");
    std::string command;
    while (true)
    {        std::cout << std::endl <<"> ";
        std::getline(std::cin, command);
        if(command.substr(0,3) != "tsm")
        {
            std::cerr << "Invalid command syntax" << std::endl;
        }
        else
        {
            if (command.substr(4,7) == "add") {tsm.add_task();}
            if (command.substr(4,8) == "list") {tsm.list_tasks();}
            if (command.substr(4,6) == "--help") {std::cout << "Help";}
            if (command.substr(4,4) == "exit") {exit(0);}
            if (command.substr(4,4) == "done") {
                std::string task_name = command.substr(9); 
                tsm.set_complete(task_name);
            }

        }
    }
    
    return 0;
}
