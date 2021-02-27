#include "utilities/room.h"

#include <fstream>
#include <iostream>

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
    std::string line;
    while (std::getline(infile, line))
    {
        std::vector <RoomObject> line_of_objects;
        for (auto c : line) {
            switch (c) {
                case ' ':
                    line_of_objects.push_back(void_obj); break;
                case '#':
                    line_of_objects.push_back(wall_obj); break;
                case '.':
                    line_of_objects.push_back(floor_obj); break;
                case '@':
                    player_starting_pose_ = {map_layout_.size(), line_of_objects.size()}; break;
                case 'x':
                    line_of_objects.push_back(exit_obj); break;
                case 'X':
                    line_of_objects.push_back(door_obj); break;
                case 'Q':
                    line_of_objects.push_back(main_exit_obj); break;
                case 'K':
                    line_of_objects.push_back(key_obj); break;
                default:
                    throw std::runtime_error("Unrecognized object ");
            }
        }

        map_layout_.push_back(line_of_objects);
    }
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
            s += map_layout_[i][j].name_[0];
        }
        s += '\n';
    }

    return s;
}

void Room::DrawScaledPixel(Image &screen, int i, int j, Pixel color) const {
    i *= 15;
    j *= 15;
    for (int x = 0; x < 16; ++x)
        for (int y = 0; y < 16; ++y)
            screen.PutPixel(j + x, i + y, color);
}

void Room::DrawRoomFrom(Image &screen, int left_upper_x, int left_upper_y) const {
    for (int i = 0; i < map_layout_.size(); ++i) {
        for (int j = 0; j < map_layout_[i].size(); ++j) {
            if (map_layout_[i][j].name_ == "void") {
                DrawScaledPixel(screen, left_upper_x + i, left_upper_y + j, {33, 172, 237, 255});
            } else if (map_layout_[i][j].name_ == "wall") {
                DrawScaledPixel(screen, left_upper_x + i, left_upper_y + j, {33, 60, 237, 255});
            } else if (map_layout_[i][j].name_ == "floor") {
                DrawScaledPixel(screen, left_upper_x + i, left_upper_y + j, {206, 33, 237, 255});
            } else if (map_layout_[i][j].name_ == "exit") {
                DrawScaledPixel(screen, left_upper_x + i, left_upper_y + j, {65, 11, 74, 255});
            } else if (map_layout_[i][j].name_ == "main_exit") {
                DrawScaledPixel(screen, left_upper_x + i, left_upper_y + j, {87, 85, 53, 255});
            } else if (map_layout_[i][j].name_ == "door") {
                DrawScaledPixel(screen, left_upper_x + i, left_upper_y + j, {74, 11, 16, 255});
            }
        }
    }
}