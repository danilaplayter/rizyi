#ifndef USERS_H
#define USERS_H

#include <vector>
#include <string>

const int ADMIN_ACCESS = 1;
const int USER_ACCESS = 2;
const int NO_ACCESS = 0;

struct User {
    std::string login;
    std::string password;
};

std::vector<User> load_users();
void save_users(const std::vector<User>& users);
int authenticate(const std::vector<User>& users, const std::string& login, const std::string& password);
bool user_exists(const std::vector<User>& users, const std::string& login);
void add_user(std::vector<User>& users, const User& user);
void remove_user(std::vector<User>& users, const std::string& login);
void print_users(const std::vector<User>& users);

#endif