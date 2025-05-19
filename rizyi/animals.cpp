#include "animals.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

using namespace std;

const string PATH_ANIMALS = "BD_Animals.txt";

vector<Animal> load_animals() {
    vector<Animal> animals;
    ifstream file(PATH_ANIMALS);

    if (file.is_open()) {
        Animal animal;
        while (file >> animal.name >> animal.price >> animal.country
            >> animal.count >> animal.min_age >> animal.max_age) {
            animals.push_back(animal);
        }
        file.close();
    }
    return animals;
}

void save_animals(const vector<Animal>& animals) {
    ofstream file(PATH_ANIMALS);
    if (file.is_open()) {
        for (const auto& animal : animals) {
            file << animal.name << " " << animal.price << " "
                << animal.country << " " << animal.count << " "
                << animal.min_age << " " << animal.max_age << endl;
        }
        file.close();
    }
}

void add_animal(vector<Animal>& animals, const Animal& animal, bool to_front) {
    if (to_front) {
        animals.insert(animals.begin(), animal);
    }
    else {
        animals.push_back(animal);
    }
}

void remove_animal(vector<Animal>& animals, int index) {
    if (index >= 0 && index < static_cast<int>(animals.size())) {
        animals.erase(animals.begin() + index);
    }
}

void print_animals(const vector<Animal>& animals) {
    cout << "+-----+--------------------+----------+---------------+--------+---------------------------+" << endl;
    cout << "| №   | Вид питомца        | Цена     | Родина        | Кол-во | Ср. продолжительность жизни |" << endl;
    cout << "+-----+--------------------+----------+---------------+--------+---------------------------+" << endl;

    for (size_t i = 0; i < animals.size(); ++i) {
        cout << "| " << setw(3) << i + 1 << " | "
            << setw(18) << animals[i].name << " | "
            << setw(8) << animals[i].price << " | "
            << setw(13) << animals[i].country << " | "
            << setw(6) << animals[i].count << " | "
            << setw(25) << to_string(animals[i].min_age) + "-" + to_string(animals[i].max_age) + " лет"
            << " |" << endl;
    }
    cout << "+-----+--------------------+----------+---------------+--------+---------------------------+" << endl;
}

void print_animals_by_price(const vector<Animal>& animals, double max_price) {
    int count = 0;
    cout << "+-----+--------------------+----------+---------------+--------+---------------------------+" << endl;
    cout << "| №   | Вид питомца        | Цена     | Родина        | Кол-во | Ср. продолжительность жизни |" << endl;
    cout << "+-----+--------------------+----------+---------------+--------+---------------------------+" << endl;

    for (size_t i = 0; i < animals.size(); ++i) {
        if (animals[i].price <= max_price) {
            cout << "| " << setw(3) << i + 1 << " | "
                << setw(18) << animals[i].name << " | "
                << setw(8) << animals[i].price << " | "
                << setw(13) << animals[i].country << " | "
                << setw(6) << animals[i].count << " | "
                << setw(25) << to_string(animals[i].min_age) + "-" + to_string(animals[i].max_age) + " лет"
                << " |" << endl;
            count++;
        }
    }
    cout << "+-----+--------------------+----------+---------------+--------+---------------------------+" << endl;
    if (count == 0) {
        cout << " У вас недостаточно бюджета((" << endl;
    }
}

bool compare_by_price(const Animal& a, const Animal& b) {
    return a.price < b.price;
}

bool compare_by_count(const Animal& a, const Animal& b) {
    return a.count < b.count;
}

bool compare_by_name(const Animal& a, const Animal& b) {
    return a.name < b.name;
}

bool compare_by_country(const Animal& a, const Animal& b) {
    return a.country < b.country;
}