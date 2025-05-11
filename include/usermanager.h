#ifndef USER_MANAGER_H
#define USER_MANAGER_H 

#include <iostream>
#include "taskmaster.h"
#include <string>

class UserManager : public TaskManager{
    private:
        std::string fixed_dir = "users";
        bool checkdir(std::string_view base_path);
        void sign_in(const std::string user_name, const std::string user_password, const std::string base_path);
        bool log_in(const std::string user_password,const std::string user_name, std::string_view base_path);
        bool check_acc(std::string_view base_path, const std::string user_name);
    public:
        void createdir(const std::string base_path);
        void acc(std::string &user_name,const std::string base_path, std::string& user_password, bool &logged_in);
    };
    
#endif
    