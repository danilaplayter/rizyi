#include "menus.h"
#include "utils.h"
#include <iostream>
#include <algorithm>

using namespace std;

void auth_menu(vector<User>& users, vector<Animal>& animals) {
    while (true) {
        clear_screen();
        cout << "=== Аутентификация ===" << endl;

        string login, password;
        cout << "Логин: ";
        cin >> login;
        cout << "Пароль: ";
        cin >> password;

        int access = authenticate(users, login, password);

        if (access == ADMIN_ACCESS) {
            admin_menu(users, animals);
            break;
        }
        else if (access == USER_ACCESS) {
            user_menu(animals);
            break;
        }
        else {
            cout << "Неверный логин или пароль!" << endl;
            system("pause");
        }
    }
}

void admin_menu(vector<User>& users, vector<Animal>& animals) {
    while (true) {
        clear_screen();
        cout << "=== Меню администратора ===" << endl;
        cout << "1. Управление пользователями" << endl;
        cout << "2. Управление животными" << endl;
        cout << "0. Выход" << endl;

        int choice = get_int_input("Выберите: ", 0, 2);

        switch (choice) {
        case 1: user_management_menu(users); break;
        case 2: animal_management_menu(animals, true); break;
        case 0: return;
        }
    }
}

void user_menu(vector<Animal>& animals) {
    while (true) {
        clear_screen();
        cout << "=== Меню пользователя ===" << endl;
        cout << "1. Просмотр животных" << endl;
        cout << "2. Покупка животного" << endl;
        cout << "3. Сортировка животных" << endl;
        cout << "0. Выход" << endl;

        int choice = get_int_input("Выберите: ", 0, 3);

        switch (choice) {
        case 1: {
            clear_screen();
            cout << "1. Все животные" << endl;
            cout << "2. По цене" << endl;
            cout << "0. Назад" << endl;

            int sub_choice = get_int_input("Выберите: ", 0, 2);

            if (sub_choice == 1) {
                print_animals(animals);
            }
            else if (sub_choice == 2) {
                double price = get_double_input("Введите максимальную цену: ", 0.0, 10000.0);
                print_animals_by_price(animals, price);
            }
            system("pause");
            break;
        }
        case 2: {
            clear_screen();
            if (animals.empty()) {
                cout << "Нет доступных животных!" << endl;
            }
            else {
                cout << "1. По номеру" << endl;
                cout << "2. По бюджету" << endl;
                cout << "0. Назад" << endl;

                int sub_choice = get_int_input("Выберите: ", 0, 2);

                if (sub_choice == 1) {
                    print_animals(animals);
                    int index = get_int_input("Введите номер животного: ", 1, animals.size()) - 1;
                    if (confirm_action("Вы уверены, что хотите купить этого питомца?")) {
                        remove_animal(animals, index);
                        cout << "Покупка совершена!" << endl;
                    }
                }
                else if (sub_choice == 2) {
                    double price = get_double_input("Введите ваш бюджет: ", 0.0, 10000.0);
                    print_animals_by_price(animals, price);
                    if (!animals.empty()) {
                        int index = get_int_input("Введите номер животного: ", 1, animals.size()) - 1;
                        if (confirm_action("Вы уверены, что хотите купить этого питомца?")) {
                            remove_animal(animals, index);
                            cout << "Покупка совершена!" << endl;
                        }
                    }
                }
            }
            system("pause");
            break;
        }
        case 3: {
            clear_screen();
            cout << "=== Сортировка ===" << endl;
            cout << "1. По цене" << endl;
            cout << "2. По количеству" << endl;
            cout << "3. По виду" << endl;
            cout << "4. По стране" << endl;
            cout << "0. Назад" << endl;

            int sub_choice = get_int_input("Выберите: ", 0, 4);

            if (sub_choice == 1) {
                sort(animals.begin(), animals.end(), compare_by_price);
            }
            else if (sub_choice == 2) {
                sort(animals.begin(), animals.end(), compare_by_count);
            }
            else if (sub_choice == 3) {
                sort(animals.begin(), animals.end(), compare_by_name);
            }
            else if (sub_choice == 4) {
                sort(animals.begin(), animals.end(), compare_by_country);
            }

            if (sub_choice != 0) {
                print_animals(animals);
                system("pause");
            }
            break;
        }
        case 0: return;
        }
    }
}

void user_management_menu(vector<User>& users) {
    while (true) {
        clear_screen();
        cout << "=== Управление пользователями ===" << endl;
        cout << "1. Просмотр пользователей" << endl;
        cout << "2. Добавление пользователя" << endl;
        cout << "3. Редактирование пользователя" << endl;
        cout << "4. Удаление пользователя" << endl;
        cout << "0. Назад" << endl;

        int choice = get_int_input("Выберите: ", 0, 4);

        switch (choice) {
        case 1: {
            clear_screen();
            print_users(users);
            system("pause");
            break;
        }
        case 2: {
            clear_screen();
            User new_user;
            cout << "Введите логин: ";
            cin >> new_user.login;

            if (user_exists(users, new_user.login)) {
                cout << "Пользователь с таким логином уже существует!" << endl;
            }
            else {
                cout << "Введите пароль: ";
                cin >> new_user.password;

                if (confirm_action("Добавить пользователя?")) {
                    add_user(users, new_user);
                    cout << "Пользователь добавлен!" << endl;
                }
            }
            system("pause");
            break;
        }
        case 3: {
            clear_screen();
            string login;
            cout << "Введите логин пользователя: ";
            cin >> login;

            bool found = false;
            size_t user_index = 0;
            for (size_t i = 0; i < users.size(); i++) {
                if (users[i].login == login) {
                    found = true;
                    user_index = i;
                    break;
                }
            }

            if (!found) {
                cout << "Пользователь не найден!" << endl;
            }
            else {
                cout << "1. Изменить логин и пароль" << endl;
                cout << "2. Изменить только логин" << endl;
                cout << "3. Изменить только пароль" << endl;
                cout << "0. Назад" << endl;

                int sub_choice = get_int_input("Выберите: ", 0, 3);

                if (sub_choice == 1) {
                    string new_login;
                    cout << "Введите новый логин: ";
                    cin >> new_login;

                    if (!user_exists(users, new_login)) {
                        cout << "Введите новый пароль: ";
                        string new_pass;
                        cin >> new_pass;

                        if (confirm_action("Подтвердить изменения?")) {
                            users[user_index].login = new_login;
                            users[user_index].password = new_pass;
                            cout << "Изменения сохранены!" << endl;
                        }
                    }
                    else {
                        cout << "Пользователь с таким логином уже существует!" << endl;
                    }
                }
                else if (sub_choice == 2) {
                    string new_login;
                    cout << "Введите новый логин: ";
                    cin >> new_login;

                    if (!user_exists(users, new_login)) {
                        if (confirm_action("Подтвердить изменения?")) {
                            users[user_index].login = new_login;
                            cout << "Изменения сохранены!" << endl;
                        }
                    }
                    else {
                        cout << "Пользователь с таким логином уже существует!" << endl;
                    }
                }
                else if (sub_choice == 3) {
                    cout << "Введите новый пароль: ";
                    string new_pass;
                    cin >> new_pass;

                    if (confirm_action("Подтвердить изменения?")) {
                        users[user_index].password = new_pass;
                        cout << "Изменения сохранены!" << endl;
                    }
                }
            }
            system("pause");
            break;
        }
        case 4: {
            clear_screen();
            cout << "1. Удалить по логину" << endl;
            cout << "2. Удалить всех" << endl;
            cout << "0. Назад" << endl;

            int sub_choice = get_int_input("Выберите: ", 0, 2);

            if (sub_choice == 1) {
                string login;
                cout << "Введите логин: ";
                cin >> login;

                if (confirm_action("Вы уверены, что хотите удалить этого пользователя?")) {
                    remove_user(users, login);
                    cout << "Пользователь удален!" << endl;
                }
            }
            else if (sub_choice == 2) {
                if (confirm_action("Вы уверены, что хотите удалить ВСЕХ пользователей?")) {
                    users.clear();
                    cout << "Все пользователи удалены!" << endl;
                }
            }
            system("pause");
            break;
        }
        case 0: return;
        }
    }
}

void animal_management_menu(vector<Animal>& animals, bool is_admin) {
    while (true) {
        clear_screen();
        cout << "=== Управление животными ===" << endl;
        cout << "1. Просмотр животных" << endl;
        if (is_admin) {
            cout << "2. Добавление животного" << endl;
            cout << "3. Удаление животного" << endl;
        }
        else {
            cout << "2. Покупка животного" << endl;
        }
        cout << "4. Сортировка животных" << endl;
        cout << "0. Назад" << endl;

        int choice = get_int_input("Выберите: ", 0, is_admin ? 4 : 4);

        switch (choice) {
        case 1: {
            clear_screen();
            cout << "1. Все животные" << endl;
            cout << "2. По цене" << endl;
            cout << "0. Назад" << endl;

            int sub_choice = get_int_input("Выберите: ", 0, 2);

            if (sub_choice == 1) {
                print_animals(animals);
            }
            else if (sub_choice == 2) {
                double price = get_double_input("Введите максимальную цену: ", 0.0, 10000.0);
                print_animals_by_price(animals, price);
            }
            system("pause");
            break;
        }
        case 2: {
            if (is_admin) {
                clear_screen();
                Animal new_animal;
                cout << "Введите вид животного: ";
                cin >> new_animal.name;
                new_animal.price = get_double_input("Введите цену: ", 0.0, 10000.0);
                cout << "Введите страну происхождения: ";
                cin >> new_animal.country;
                new_animal.count = get_int_input("Введите количество: ", 0, 1000);
                new_animal.min_age = get_int_input("Введите минимальный возраст: ", 0, 100);
                new_animal.max_age = get_int_input("Введите максимальный возраст: ", new_animal.min_age, 100);

                cout << "1. Добавить в начало" << endl;
                cout << "2. Добавить в конец" << endl;
                cout << "0. Отмена" << endl;

                int sub_choice = get_int_input("Выберите: ", 0, 2);

                if (sub_choice == 1 || sub_choice == 2) {
                    if (confirm_action("Добавить животное?")) {
                        add_animal(animals, new_animal, sub_choice == 1);
                        cout << "Животное добавлено!" << endl;
                    }
                }
            }
            else {
                clear_screen();
                if (animals.empty()) {
                    cout << "Нет доступных животных!" << endl;
                }
                else {
                    cout << "1. По номеру" << endl;
                    cout << "2. По бюджету" << endl;
                    cout << "0. Назад" << endl;

                    int sub_choice = get_int_input("Выберите: ", 0, 2);

                    if (sub_choice == 1) {
                        print_animals(animals);
                        int index = get_int_input("Введите номер животного: ", 1, animals.size()) - 1;
                        if (confirm_action("Вы уверены, что хотите купить этого питомца?")) {
                            remove_animal(animals, index);
                            cout << "Покупка совершена!" << endl;
                        }
                    }
                    else if (sub_choice == 2) {
                        double price = get_double_input("Введите ваш бюджет: ", 0.0, 10000.0);
                        print_animals_by_price(animals, price);
                        if (!animals.empty()) {
                            int index = get_int_input("Введите номер животного: ", 1, animals.size()) - 1;
                            if (confirm_action("Вы уверены, что хотите купить этого питомца?")) {
                                remove_animal(animals, index);
                                cout << "Покупка совершена!" << endl;
                            }
                        }
                    }
                }
            }
            system("pause");
            break;
        }
        case 3: {
            if (is_admin) {
                clear_screen();
                if (animals.empty()) {
                    cout << "Нет животных для удаления!" << endl;
                }
                else {
                    cout << "1. Удалить по номеру" << endl;
                    cout << "2. Удалить всех" << endl;
                    cout << "0. Назад" << endl;

                    int sub_choice = get_int_input("Выберите: ", 0, 2);

                    if (sub_choice == 1) {
                        print_animals(animals);
                        int index = get_int_input("Введите номер животного: ", 1, animals.size()) - 1;
                        if (confirm_action("Вы уверены, что хотите удалить этого питомца?")) {
                            remove_animal(animals, index);
                            cout << "Животное удалено!" << endl;
                        }
                    }
                    else if (sub_choice == 2) {
                        if (confirm_action("Вы уверены, что хотите удалить ВСЕХ животных?")) {
                            animals.clear();
                            cout << "Все животные удалены!" << endl;
                        }
                    }
                }
                system("pause");
            }
            break;
        }
        case 4: {
            clear_screen();
            cout << "=== Сортировка ===" << endl;
            cout << "1. По цене" << endl;
            cout << "2. По количеству" << endl;
            cout << "3. По виду" << endl;
            cout << "4. По стране" << endl;
            cout << "0. Назад" << endl;

            int sub_choice = get_int_input("Выберите: ", 0, 4);

            if (sub_choice == 1) {
                sort(animals.begin(), animals.end(), compare_by_price);
            }
            else if (sub_choice == 2) {
                sort(animals.begin(), animals.end(), compare_by_count);
            }
            else if (sub_choice == 3) {
                sort(animals.begin(), animals.end(), compare_by_name);
            }
            else if (sub_choice == 4) {
                sort(animals.begin(), animals.end(), compare_by_country);
            }

            if (sub_choice != 0) {
                print_animals(animals);
                system("pause");
            }
            break;
        }
        case 0: return;
        }
    }
}