#ifndef UTILS_H
#define UTILS_H

#include <string>

int get_int_input(const std::string& prompt, int min_val, int max_val);
double get_double_input(const std::string& prompt, double min_val, double max_val);
bool confirm_action(const std::string& message);
void clear_screen();

#endif