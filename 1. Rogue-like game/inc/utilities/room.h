#ifndef ROOM_H
#define ROOM_H

#include <sstream>
#include <vector>

#include "graphics/Image.h"
#include "graphics/tile.h"
#include "utilities/game_object.h"

class Room {
    int map_type_;
    std::vector < std::vector<GameObject*> > map_layout_;
    std::pair <unsigned, unsigned> player_starting_pose_;
    std::pair <int, int> mins_;
    std::vector <std::pair <int, int> > exit_poses_;

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

    std::vector<std::vector<GameObject *>> get_layout() const;
    int get_type() const;
    std::pair <int, int> get_size() const;
    std::pair <int, int> get_mins() const;

    std::string to_string() const;

    std::pair <unsigned, unsigned> get_player() const;

    void DrawScaledPixel(Image &screen, int i, int j, Pixel color) const;

    void DrawTile(Image &screen, int i, int j, const Tile &tl) const;

    void DrawRoomOn(Image* screen);
};

#endif // ROOM_H