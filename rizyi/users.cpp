#include "users.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

using namespace std;

const string PATH_AUTH = "BD_Authen.txt";

vector<User> load_users() {
    vector<User> users;
    ifstream file(PATH_AUTH);

    if (file.is_open()) {
        User user;
        while (file >> user.login >> user.password) {
            users.push_back(user);
        }
        file.close();
    }
    return users;
}

void save_users(const vector<User>& users) {
    ofstream file(PATH_AUTH);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.login << " " << user.password << endl;
        }
        file.close();
    }
}

int authenticate(const vector<User>& users, const string& login, const string& password) {
    if (login == "ADMIN" && password == "007") return ADMIN_ACCESS;

    for (const auto& user : users) {
        if (user.login == login && user.password == password) {
            return USER_ACCESS;
        }
    }
    return NO_ACCESS;
}

bool user_exists(const vector<User>& users, const string& login) {
    for (const auto& user : users) {
        if (user.login == login) {
            return true;
        }
    }
    return false;
}

void add_user(vector<User>& users, const User& user) {
    users.insert(users.begin(), user);
}

void remove_user(vector<User>& users, const string& login) {
    users.erase(remove_if(users.begin(), users.end(),
        [&login](const User& u) { return u.login == login; }),
        users.end());
}

void print_users(const vector<User>& users) {
    cout << "==========================================" << endl;
    cout << "| " << setw(15) << left << "Логин" << " | " << setw(15) << left << "Пароль" << " |" << endl;
    cout << "==========================================" << endl;

    for (const auto& user : users) {
        cout << "| " << setw(15) << left << user.login << " | " << setw(15) << left << user.password << " |" << endl;
    }
    cout << "==========================================" << endl;
}