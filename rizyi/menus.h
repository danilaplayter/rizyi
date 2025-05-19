#ifndef MENUS_H
#define MENUS_H

#include <vector>
#include "users.h"
#include "animals.h"

void admin_menu(std::vector<User>& users, std::vector<Animal>& animals);
void user_menu(std::vector<Animal>& animals);
void auth_menu(std::vector<User>& users, std::vector<Animal>& animals);
void user_management_menu(std::vector<User>& users);
void animal_management_menu(std::vector<Animal>& animals, bool is_admin);

#endif