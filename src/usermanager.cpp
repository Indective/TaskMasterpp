#include "taskmaster.hpp"
#include <bcrypt/bcrypt.h>
#include <bcrypt/bcrypt.c>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs  = std::filesystem;

bool UserManager::checkdir(std::string &base_path)
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

void UserManager::createdir(std::string &base_path)
{
    std::string full_path = base_path + "/" + fixed_dir;
    if(!checkdir(base_path))
    {
        fs::create_directory(full_path);
        fs::current_path(full_path);

    }
}

void UserManager::sign_in(const std::string user_name, const char* user_password, std::string &base_path)
{
    createdir(base_path);
    std::ofstream outputFile(user_name);
    char hash[100];
    char salt[100];
    bcrypt_gensalt(12,salt);
    if(outputFile.is_open())
    {
        if (bcrypt_hashpw(user_password, salt, hash) != 0) {
            std::cerr << "Error hashing password." << std::endl;
        }
        outputFile << hash;
        outputFile.close();
    }
}

bool UserManager::log_in(const char* user_password,const std::string user_name, std::string &base_path)
{
    std::string hash;
    std::ifstream inputfile(user_name);
    while(inputfile)
    {
        std::getline(std::cin,hash);
    }
    const char* hash_char = hash.c_str();
    if(bcrypt_checkpw(user_password, hash_char) == 0)
    {
        std::cout << "Log in complete !" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Log in incomplete !" << std::endl;
        return false;
    }
    return false;

}

bool UserManager::check_acc(std::string &base_path, const std::string user_name)
{
    for(auto &i: fs::directory_iterator{fs::current_path()})
    {
        if(i.path().filename() == fixed_dir)
        {
            fs::current_path(fs::current_path().string() + fixed_dir);
            for(auto &v: fs::directory_iterator{fs::current_path()})
            {
                if(i.path().filename() == user_name)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
