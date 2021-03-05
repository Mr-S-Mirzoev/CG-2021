#ifndef ROOM_H
#define ROOM_H

#include <sstream>
#include <vector>

#include "graphics/Image.h"
#include "graphics/tile.h"
#include "utilities/game_object.h"

class Game;

class MutableGameObject: public GameObject {
protected:
    enum Action {
        ACTION_NOT_APPLIED,
        ACTION_APPLIED
    };

    int state_ = ACTION_NOT_APPLIED;
public:
    MutableGameObject(const std::string &name): GameObject(name, true) {}
    virtual void apply_action(Game &gm) = 0;
};

class StaticGameObject: public GameObject {
public:
    StaticGameObject(const std::string &name): GameObject(name, false) {}
};

class VoidObject: public StaticGameObject {
public:
    VoidObject (): StaticGameObject("void") {}
};

class WallObject: public StaticGameObject {
public:
    WallObject (): StaticGameObject("wall") {}
};

class FloorObject: public StaticGameObject {
public:
    FloorObject (): StaticGameObject("floor") {}
};

class ExitObject: public MutableGameObject {
public:
    ExitObject (): MutableGameObject("exit") {}

    void apply_action(Game &gm) override;
};

class MainExitObject: public MutableGameObject {
public:
    MainExitObject (): MutableGameObject("main_exit") {}

    void apply_action(Game &gm) override;
};

class DoorObject: public MutableGameObject {
public:
    DoorObject (): MutableGameObject("door") {}

    void apply_action(Game &gm) override;
};

class KeyObject: public MutableGameObject {
public:
    KeyObject (): MutableGameObject("key") {}

    void apply_action(Game &gm) override;
};

class Room {
    int map_type_;
    std::vector<std::vector<GameObject>> map_layout_;
    std::pair <unsigned, unsigned> player_starting_pose_;

    void throw_exception (int room_width,
                          int room_height,
                          int screen_width,
                          int screen_height) const;

    Room (const std::string &map_file, int type);

public:

    typedef enum {
        ROOM_TYPE_A,
        ROOM_TYPE_B,
        ROOM_TYPE_C,
        ROOM_TYPE_D,
        NO_ROOM
    } room_type;

    Room (int room_type = room_type::NO_ROOM);
    Room (const Room &rhs) = default;

    std::vector<std::vector<GameObject>> get_layout() const;
    int get_type() const;
    std::pair <int, int> get_size() const;

    std::string to_string() const;

    void DrawScaledPixel(Image &screen, int i, int j, Pixel color) const;

    void DrawTile(Image &screen, int i, int j, Tile &tl) const;

    void DrawRoomOn(Image* screen) const;
};

#endif // ROOM_H