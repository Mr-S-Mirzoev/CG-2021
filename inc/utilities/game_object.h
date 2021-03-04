#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>

#include "graphics/tile.h"

class GameObject {
    std::string name_;
    bool mutable_; // If object can be changed or removed from the map and put into inventory
protected:
    Tile *current_tile_;
public:
    GameObject (const std::string &name, bool mutability);
    GameObject (const GameObject &rhs) = default;

    std::string get_name() const;
    bool is_mutable() const;
};

#endif // GAME_OBJECT_H