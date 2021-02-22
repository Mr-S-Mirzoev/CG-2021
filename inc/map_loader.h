#include <sstream>
#include <vector>

struct MapObject {
    std::string name_;
    bool mutable_; // If object can be changed or removed from the map and put into inventory
};

const MapObject void_obj {"void", false};
const MapObject wall_obj {"wall", false};
const MapObject floor_obj {"floor", false};
const MapObject exit_obj {"exit", false};
const MapObject main_exit_obj {"main_exit", false};

const MapObject door_obj {"door", true};
const MapObject key_obj {"key", true};

class Map {
    std::string map_type_;
    std::vector<std::vector<MapObject>> map_layout_;
    std::pair <unsigned, unsigned> player_starting_pose_;
public:
    Map (const std::string &map_file);

    std::vector<std::vector<MapObject>> get_layout() const;
    std::string get_type() const;

    std::string to_string() const;
};

class MapA {
    Map map_;
public:
    MapA(): map_("./res/maps/mapA.txt") {}
    std::string to_string() const { return map_.to_string(); }
};

class MapB {
    Map map_;
public:
    MapB(): map_("./res/maps/mapB.txt") {}
};

class MapC {
    Map map_;
public:
    MapC(): map_("./res/maps/mapC.txt") {}
};

class MapD {
    Map map_;
public:
    MapD(): map_("./res/maps/mapD.txt") {}
};

const MapA default_mapA;
/*const MapB default_mapB;
const MapC default_mapC;
const MapD default_mapD;*/