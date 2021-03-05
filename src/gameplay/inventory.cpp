#include "gameplay/inventory.h"
#include "utilities/exceptions.h"

void Inventory::add(const std::string &object) {
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