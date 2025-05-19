#ifndef ANIMALS_H
#define ANIMALS_H

#include <vector>
#include <string>

struct Animal {
    std::string name;
    double price;
    std::string country;
    int count;
    int min_age;
    int max_age;
};

std::vector<Animal> load_animals();
void save_animals(const std::vector<Animal>& animals);
void add_animal(std::vector<Animal>& animals, const Animal& animal, bool to_front = false);
void remove_animal(std::vector<Animal>& animals, int index);
void print_animals(const std::vector<Animal>& animals);
void print_animals_by_price(const std::vector<Animal>& animals, double max_price);

// Функции сравнения для сортировки
bool compare_by_price(const Animal& a, const Animal& b);
bool compare_by_count(const Animal& a, const Animal& b);
bool compare_by_name(const Animal& a, const Animal& b);
bool compare_by_country(const Animal& a, const Animal& b);

#endif