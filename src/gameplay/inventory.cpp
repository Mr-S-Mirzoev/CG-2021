#include "gameplay/inventory.h"
#include "utilities/exceptions.h"

#include <iostream>

void Inventory::add(const std::string &object) {
    std::cout << "Inv size: " << inventory_data_.size() << std::endl;

    if (has(object))
        throw utilities::InventoryHadItException(object);
    
    inventory_data_.insert(object);
}

bool Inventory::has(const std::string &object) {
    return inventory_data_.find(object) != inventory_data_.end();
}

void Inventory::remove(const std::string &object) {
    if (!has(object))
        throw utilities::InventoryDidntHaveItException(object);

    inventory_data_.erase(object);
}