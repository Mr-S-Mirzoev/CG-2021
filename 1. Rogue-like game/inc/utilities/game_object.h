#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>

#include "graphics/tile.h"

class Game;
class GameObject {
protected:
    enum Action {
        ACTION_NOT_APPLIED,
        ACTION_APPLIED
    };

    int state_ = ACTION_NOT_APPLIED;

    Tile *current_tile_;
private:
    std::string name_;
public:
    GameObject(const std::string &name): name_(name), current_tile_(&get_tile_by_name(name)) {}

    std::string get_name() const { return name_; }

    Tile &get_tile() const { return *current_tile_; }

    virtual void apply_action(Game &gm) = 0;
};

class VoidObject: public GameObject {
public:
    VoidObject (): GameObject("void") {}

    void apply_action(Game &gm) override;
};

class WallObject: public GameObject {
public:
    WallObject (): GameObject("wall") {}

    void apply_action(Game &gm) override;
};

class FloorObject: public GameObject {
public:
    FloorObject (): GameObject("floor") {}

    void apply_action(Game &gm) override {};
};

class ExitObject: public GameObject {
public:
    ExitObject (): GameObject("exit") {}

    void apply_action(Game &gm) override;
};

class MainExitObject: public GameObject {
public:
    MainExitObject (): GameObject("main_exit") {}

    void apply_action(Game &gm) override;
};

class DoorObject: public GameObject {
public:
    DoorObject (): GameObject("door") {}

    void apply_action(Game &gm) override;
};

class KeyObject: public GameObject {
public:
    KeyObject (): GameObject("key") {}

    void apply_action(Game &gm) override;
};

#endif // GAME_OBJECT_H