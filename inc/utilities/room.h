#ifndef ROOM_H
#define ROOM_H

#include <sstream>
#include <vector>

#include "graphics/Image.h"

class Game;

class RoomObject {
    std::string name_;
    bool mutable_; // If object can be changed or removed from the map and put into inventory
public:
    RoomObject (const std::string &name, bool mutability);

    std::string get_name() const;
    bool is_mutable() const;
};

class MutableRoomObject: public RoomObject {
public:
    MutableRoomObject(const std::string &name): RoomObject(name, true) {}
    virtual void apply_action(Game &gm) = 0;
};

class StaticRoomObject: public RoomObject {
public:
    StaticRoomObject(const std::string &name): RoomObject(name, false) {}
};

class VoidObject: public StaticRoomObject {
public:
    VoidObject (): StaticRoomObject("void") {}
};

class WallObject: public StaticRoomObject {
public:
    WallObject (): StaticRoomObject("wall") {}
};

class FloorObject: public StaticRoomObject {
public:
    FloorObject (): StaticRoomObject("floor") {}
};

class ExitObject: public MutableRoomObject {
public:
    ExitObject (): MutableRoomObject("exit") {}

    void apply_action(Game &gm) override {}
};

class MainExitObject: public MutableRoomObject {
public:
    MainExitObject (): MutableRoomObject("main_exit") {}

    void apply_action(Game &gm) override {}
};

class DoorObject: public MutableRoomObject {
public:
    DoorObject (): MutableRoomObject("door") {}

    void apply_action(Game &gm) override {}
};

class KeyObject: public MutableRoomObject {
public:
    KeyObject (): MutableRoomObject("key") {}

    void apply_action(Game &gm) override {}
};

class Room {
    std::string map_type_;
    std::vector<std::vector<RoomObject>> map_layout_;
    std::pair <unsigned, unsigned> player_starting_pose_;
public:
    typedef enum {
        ROOM_TYPE_A,
        ROOM_TYPE_B,
        ROOM_TYPE_C,
        ROOM_TYPE_D,
        NO_ROOM
    } room_type;

    Room (const std::string &map_file);
    Room (int room_type);

    std::vector<std::vector<RoomObject>> get_layout() const;
    std::string get_type() const;

    std::string to_string() const;

    void DrawScaledPixel(Image &screen, int i, int j, Pixel color) const;

    void DrawRoomFrom(Image &screen, int left_upper_x, int left_upper_y) const;
};

#endif // ROOM_H