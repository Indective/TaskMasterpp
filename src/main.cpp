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
    std::string command;
    std::string user_name;
    std::string user_password;
    std::string task_name;
    bool logged_in = false;
    std::vector<std::string> commands = {"add","list","done","cpri","cts","ctd","rmt","--help","exit"};
    std::vector<std::string> commands_exp = {"Create a task","Lists Tasks","sets task as completed"
    ,"changes task priority","changes task name","changes task description","deletes a task","lists all commands with explanations"
    ,"shuts programm off"};

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
        tsm.create_task(base_path,user_name);
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
            if (command.substr(4,3) == "add") {tsm.add_task();}
            else if (command.substr(4,4) == "list") {tsm.list_tasks();}
            else if (command.substr(4,4) == "exit") {return 0;}
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
                for(int i = 0; i < commands.size(); i ++){
                    std::cout << commands[i] << "               " << commands_exp[i] << std::endl;
                }
            }

            

        }
    }
    
    return 0;
}
