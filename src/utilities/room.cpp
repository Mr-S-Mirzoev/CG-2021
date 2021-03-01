#include "utilities/room.h"
#include "utilities/exceptions.h"

#include <fstream>
#include <iostream>

constexpr int scale = 16;

RoomObject::RoomObject(const std::string &name, bool mutability):
    name_(name), mutable_(mutability) {}

std::string RoomObject::get_name() const { return name_; }
bool RoomObject::is_mutable() const { return mutable_; }    

/*
  - пустое пространство: ` ` (пробел)
  - стена: `#`
  - пол: `.`
  - игрок: `@`
  - выход из комнаты: `x`
  - выход из всего лабиринта: `Q`
  - ключи, которые позволяют открывать закрытые выходы из комнат: `K`
*/
Room::Room(const std::string &map_file) {
    std::ifstream infile(map_file);

    if (!infile.is_open())
        throw utilities::FileException(map_file);

    std::string line;
    while (std::getline(infile, line))
    {
        std::vector <RoomObject> line_of_objects;
        for (auto c : line) {
            switch (c) {
                case ' ':
                    line_of_objects.push_back(VoidObject{}); break;
                case '#':
                    line_of_objects.push_back(WallObject{}); break;
                case '.':
                    line_of_objects.push_back(FloorObject{}); break;
                case '@':
                    line_of_objects.push_back(FloorObject{});
                    player_starting_pose_ = {map_layout_.size(), line_of_objects.size()}; break;
                case 'x':
                    line_of_objects.push_back(ExitObject{}); break;
                case 'X':
                    line_of_objects.push_back(DoorObject{}); break;
                case 'Q':
                    line_of_objects.push_back(MainExitObject{}); break;
                case 'K':
                    line_of_objects.push_back(KeyObject{}); break;
                default:
                    throw std::runtime_error("Unrecognized object ");
            }
        }

        map_layout_.push_back(line_of_objects);
    }
}

Room::Room(int type): Room(type == ROOM_TYPE_A ? "./res/maps/roomA.txt" : 
                           type == ROOM_TYPE_B ? "./res/maps/roomB.txt" : 
                           type == ROOM_TYPE_C ? "./res/maps/roomC.txt" : 
                           type == ROOM_TYPE_D ? "./res/maps/roomD.txt" :
                                                 "./res/noroom.txt") {
    if (type == NO_ROOM)
        throw utilities::OuterSpaceException("You wished to create an unexisting room");
}

std::vector<std::vector<RoomObject>> Room::get_layout() const {
    return map_layout_;
}

std::string Room::get_type() const {
    return map_type_;
}

std::string Room::to_string() const {
    std::string s;
    for (int i = 0; i < map_layout_.size(); ++i) {        
        for (int j = 0; j < map_layout_[i].size(); ++j) {
            if (std::pair<unsigned int,unsigned int>{i, j} == player_starting_pose_)
                s += "@";
            s += map_layout_[i][j].get_name()[0];
        }
        s += '\n';
    }

    return s;
}

void Room::DrawScaledPixel(Image &screen, int i, int j, Pixel color) const {
    i *= scale - 1;
    j *= scale - 1;
    for (int x = 0; x < scale; ++x)
        for (int y = 0; y < scale; ++y)
            screen.PutPixel(j + x, i + y, color);
}

void Room::DrawTile(Image &screen, int i, int j, Tile &tl) const {
    i *= scale - 1;
    j *= scale - 1;
    for (int x = 0; x < scale; ++x)
        for (int y = 0; y < scale; ++y)
            screen.PutPixel(j + x, i + y, tl.get_pixel(x, y));
}

std::pair <int, int> Room::get_size() const {
    int room_width = map_layout_[0].size();
    int room_height = map_layout_.size();
    return {room_height, room_width};
}

void Room::DrawRoomOn(Image* screen) const {
    int center_x = screen->Width() / (scale * 2);
    int center_y = screen->Height() / (scale * 2);

    int room_width = map_layout_[0].size();
    int room_height = map_layout_.size();

    int x_min = center_x - room_width / 2;
    if (x_min < 0) {
        throw utilities::SizeMismatchException(
            "Size of room: (" + 
            std::to_string(room_height) + 
            "; " + 
            std::to_string(room_width) + 
            "). Size of screen: (" + 
            std::to_string(screen->Height()) + 
            "; " + 
            std::to_string(screen->Width()) + 
            ")"
        );
    }

    int x_max = center_x + room_width - room_width / 2;
    if (x_max >= screen->Width()) {
        throw utilities::SizeMismatchException(
            "Size of room: (" + 
            std::to_string(room_height) + 
            "; " + 
            std::to_string(room_width) + 
            "). Size of screen: (" + 
            std::to_string(screen->Height()) + 
            "; " + 
            std::to_string(screen->Width()) + 
            ")"
        );
    }

    int y_min = center_y - room_height / 2;
    if (y_min < 0) {
        throw utilities::SizeMismatchException(
            "Size of room: (" + 
            std::to_string(room_height) + 
            "; " + 
            std::to_string(room_width) + 
            "). Size of screen: (" + 
            std::to_string(screen->Height()) + 
            "; " + 
            std::to_string(screen->Width()) + 
            ")"
        );
    }

    int y_max = center_y + room_height - room_height / 2;
    if (y_max >= screen->Height()) {
        throw utilities::SizeMismatchException(
            "Size of room: (" + 
            std::to_string(room_height) + 
            "; " + 
            std::to_string(room_width) + 
            "). Size of screen: (" + 
            std::to_string(screen->Height()) + 
            "; " + 
            std::to_string(screen->Width()) + 
            ")"
        );
    }

    for (int j = x_min; j < x_max; ++j) {
        for (int i = y_min; i < y_max; ++i) {
            int i_m = i - y_min;
            int j_m = j - x_min;

            std::cout << "======BLOCK======" << std::endl;
            std::cout << x_min << " " << x_max << std::endl;
            std::cout << y_min << " " << y_max << std::endl;
            std::cout << room_height << " " << room_width << std::endl;
            std::cout << i_m << " " << j_m << std::endl;

            auto& tile = get_tile_by_name(map_layout_[i_m][j_m].get_name());

            if (map_layout_[i_m][j_m].get_name() == "void") {
                DrawTile(*screen, i, j, tile);
            } else if (map_layout_[i_m][j_m].get_name() == "wall") {
                DrawTile(*screen, i, j, tile);
            } else if (map_layout_[i_m][j_m].get_name() == "floor") {
                DrawTile(*screen, i, j, tile);
            } else if (map_layout_[i_m][j_m].get_name() == "exit") {
                DrawTile(*screen, i, j, tile);
            } else if (map_layout_[i_m][j_m].get_name() == "main_exit") {
                DrawTile(*screen, i, j, tile);
            } else if (map_layout_[i_m][j_m].get_name() == "door") {
                DrawTile(*screen, i, j, tile);
            } else if (map_layout_[i_m][j_m].get_name() == "key") {
                DrawTile(*screen, i, j, tile);
            }
        }
    }
}