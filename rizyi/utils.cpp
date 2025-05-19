#include "utils.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

int get_int_input(const string& prompt, int min_val, int max_val) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min_val || value > max_val) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод! Введите значение от " << min_val << " до " << max_val << ": ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double get_double_input(const string& prompt, double min_val, double max_val) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min_val || value > max_val) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод! Введите значение от " << min_val << " до " << max_val << ": ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

bool confirm_action(const string& message) {
    cout << message << " (1 - Да, 2 - Нет): ";
    int choice = get_int_input("", 1, 2);
    return choice == 1;
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}