#include "taskmaster.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main()
{
    TaskManager tsm;
    UserManager usm;
    std::string base_path = fs::current_path().parent_path().string();
    std::string command;
    std::string user_name;
    std::string user_password;
    bool logged_in = false;


    usm.createdir(base_path);
    std::cout << "Enter User Name : ";
    std::getline(std::cin,user_name);

    if(usm.check_acc(base_path,user_name))
    {
        std::cout << "Logging You in ." << std::endl;
        std::cout << "Enter password : ";
        std::getline(std::cin, user_password);
        if(usm.log_in(user_password,user_name,base_path))
        {
            logged_in = true;
        }
    }
    else
    {
        std::cout << "Sign-ing You Up ." << std::endl;
        std::cout << "Enter password : ";
        std::getline(std::cin, user_password);
        usm.sign_in(user_name,user_password,base_path);
        logged_in = true;
    }

    while (logged_in)
    {   std::cout << std::endl <<"> ";
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
