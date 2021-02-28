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

void Room::DrawRoomFrom(Image &screen, int left_upper_x, int left_upper_y) const {
    int x_max = std::max<int>(
        std::min<int>(
            left_upper_x + map_layout_.size(), 
            screen.Height() / scale - 1
        ), 
        0
    );
    int y_max = std::max<int>(
        std::min<int>(
            left_upper_y + map_layout_[0].size(), 
            screen.Width() / scale - 1
        ), 
        0
    );

    for (int i = left_upper_x; i < x_max; ++i) {
        for (int j = left_upper_y; j < y_max; ++j) {
            int i_m = i - left_upper_x;
            int j_m = j - left_upper_y;

            if (map_layout_[i_m][j_m].get_name() == "void") {
                DrawScaledPixel(screen, i, j, {33, 172, 237, 255});
            } else if (map_layout_[i_m][j_m].get_name() == "wall") {
                DrawScaledPixel(screen, i, j, {33, 60, 237, 255});
            } else if (map_layout_[i_m][j_m].get_name() == "floor") {
                DrawScaledPixel(screen, i, j, {206, 33, 237, 255});
            } else if (map_layout_[i_m][j_m].get_name() == "exit") {
                DrawScaledPixel(screen, i, j, {65, 11, 74, 255});
            } else if (map_layout_[i_m][j_m].get_name() == "main_exit") {
                DrawScaledPixel(screen, i, j, {87, 85, 53, 255});
            } else if (map_layout_[i_m][j_m].get_name() == "door") {
                DrawScaledPixel(screen, i, j, {74, 11, 16, 255});
            }
        }
    }
}