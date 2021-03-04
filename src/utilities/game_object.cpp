#include "utilities/game_object.h"

GameObject::GameObject(const std::string &name, bool mutability):
    name_(name), mutable_(mutability), current_tile_(&get_tile_by_name(name_)) {}

std::string GameObject::get_name() const { return name_; }
bool GameObject::is_mutable() const { return mutable_; }  