#include "map_loader.h"
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

Map::Map(const std::string &map_file) {
    std::ifstream infile(map_file);
    std::string line;
    while (std::getline(infile, line))
    {
        std::vector <MapObject> line_of_objects;
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

std::vector<std::vector<MapObject>> Map::get_layout() const {
    return map_layout_;
}

std::string Map::get_type() const {
    return map_type_;
}

std::string Map::to_string() const {
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