#include <windows.h>
#include <iostream>
#include "users.h"
#include "animals.h"
#include "menus.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    auto users = load_users();
    auto animals = load_animals();

    auth_menu(users, animals);

    save_users(users);
    save_animals(animals);

    return 0;
}