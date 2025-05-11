#include "usermanager.h"
#include <bcrypt.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm> 

namespace fs  = std::filesystem;

bool UserManager::checkdir(std::string_view base_path)
{
    try{
        for (auto const& i : fs::directory_iterator{base_path})
        {
            if(i.path().filename() == fixed_dir)
            {
                return true;
            }

        }
    }catch(const fs::filesystem_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    return false;
}

void UserManager::acc(std::string &user_name, const std::string base_path, std::string& user_password, bool &logged_in)
{
    std::cout << "Enter User Name: ";
    std::getline(std::cin, user_name);
    if (check_acc(base_path, user_name))
    {
        std::cout << "Logging You in ." << std::endl;
        std::cout << "Enter password : ";
        std::getline(std::cin, user_password);
        if (log_in(user_password, user_name, base_path))
        {
            logged_in = true;
        }
    }
    else
    {
        std::cout << "Sign-ing You Up ." << std::endl;
        std::cout << "Enter password : ";
        std::getline(std::cin, user_password);
        sign_in(user_name, user_password, base_path);
        logged_in = true;
        create_task(base_path, user_name);
    }
}

void UserManager::createdir(const std::string base_path)
{
    try
    {
        std::string full_path = base_path + "/" + "data" + "/" + fixed_dir;
        if(!checkdir(base_path))
        {
            fs::create_directory(full_path);
            fs::current_path(full_path);
    
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void UserManager::sign_in(const std::string user_name, const std::string user_password, const std::string base_path)
{
    try
    {
        createdir(base_path);
        std::string full_path = fs::current_path().string() + "/" + user_name;
        fs::create_directory(full_path);
        std::ofstream outputFile(user_name);
        std::string hash = bcrypt::generateHash(user_password);
        if(outputFile.is_open())
        {
            outputFile << hash;
            outputFile.close();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

bool UserManager::log_in(const std::string user_password, const std::string user_name, std::string_view base_path)
{
    fs::current_path(fs::current_path().string() + "/" +  user_name);
    std::ifstream inputfile(user_name);
    if (!inputfile.is_open()) {
        std::cerr << "Error: Could not open file for user " << user_name << std::endl;
        return false;
    }

    std::string hash;
    std::getline(inputfile, hash);
    inputfile.close();

    bool result = bcrypt::validatePassword(user_password, hash);

    if (result) {
        std::cout << "Log in complete!" << std::endl;
        return true;
    } else {
        std::cout << "Log in incomplete!" << std::endl;
        return false;
    }

}

bool UserManager::check_acc(std::string_view base_path, const std::string user_name)
{
    try
    {
        if(fs::current_path().filename() == fixed_dir)
        {
            for(auto &i: fs::directory_iterator{fs::current_path()})
            {
                if(i.path().filename() == user_name)
                {
                    return true;
                    fs::current_path(fs::current_path().string() + "/" + user_name);
                }
            }
            return false;
        }
        else
        {
            fs::current_path(fs::current_path().string() + "/" + "data" + "/" + fixed_dir);
            for(auto &i: fs::directory_iterator{fs::current_path()})
            {
                if(i.path().filename() == user_name)
                {
                    return true;
                    fs::current_path(fs::current_path().string() + "/" + user_name);
                }
            }
            return false;
        }
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;
}