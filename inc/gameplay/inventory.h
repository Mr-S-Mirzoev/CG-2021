#ifndef INVENTORY_H
#define INVENTORY_H

#include "utilities/game_object.h"

#include <set>
#include <string>

class Inventory {
    std::set <std::string> inventory_data_;
public:
    Inventory() = default;

    void add(const std::string &object);
    bool has(const std::string &object);
    void remove(const std::string &object);
};

#endif // INVENTORY_H