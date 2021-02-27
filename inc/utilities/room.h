#include <sstream>
#include <vector>

#include "graphics/Image.h"

struct RoomObject {
    std::string name_;
    bool mutable_; // If object can be changed or removed from the map and put into inventory
};

const RoomObject void_obj {"void", false};
const RoomObject wall_obj {"wall", false};
const RoomObject floor_obj {"floor", false};
const RoomObject exit_obj {"exit", false};
const RoomObject main_exit_obj {"main_exit", false};

const RoomObject door_obj {"door", true};
const RoomObject key_obj {"key", true};

class Room {
    std::string map_type_;
    std::vector<std::vector<RoomObject>> map_layout_;
    std::pair <unsigned, unsigned> player_starting_pose_;
public:
    Room (const std::string &map_file);

    std::vector<std::vector<RoomObject>> get_layout() const;
    std::string get_type() const;

    std::string to_string() const;

    void DrawScaledPixel(Image &screen, int i, int j, Pixel color) const;

    void DrawRoomFrom(Image &screen, int left_upper_x, int left_upper_y) const;
};

class RoomA {
    Room map_;
public:
    RoomA(): map_("./res/maps/mapA.txt") {}
    std::string to_string() const { return map_.to_string(); }
    void Draw(Image &screen, int left_upper_x, int left_upper_y) const {
        map_.DrawRoomFrom(screen, left_upper_x, left_upper_y);
    }
};

class RoomB {
    Room map_;
public:
    RoomB(): map_("./res/maps/mapB.txt") {}
};

class RoomC {
    Room map_;
public:
    RoomC(): map_("./res/maps/mapC.txt") {}
};

class RoomD {
    Room map_;
public:
    RoomD(): map_("./res/maps/mapD.txt") {}
};

const RoomA default_mapA;
/*const RoomB default_mapB;
const RoomC default_mapC;
const RoomD default_mapD;*/