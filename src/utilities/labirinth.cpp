#include "utilities/labirinth.h"
#include "utilities/exceptions.h"
#include "utilities/random.h"

#include <fstream>
#include <iostream>

namespace mapping {

    Labirinth::Labirinth(const std::string &lab_path) {
        std::ifstream infile(lab_path);

        std::string line;
        int i = 0, j;
        bool set = false;

        while (std::getline(infile, line)) {
            auto old_size = labirinth_plan_.size();
            std::cout << line << std::endl;

            if (old_size == std::pair<int, int>{0, 0}) {
                labirinth_plan_.resize(line.size(), 1);
            } else {
                labirinth_plan_.resize(old_size.first, old_size.second + 1);
            }

            j = 0;
            for (auto c : line) {
                switch (c)
                {
                case 'A':
                    labirinth_plan_[{i, j}] = Room(Room::room_type::ROOM_TYPE_A);
                    break;

                case 'B':
                    labirinth_plan_[{i, j}] = Room(Room::room_type::ROOM_TYPE_B);
                    break;

                case 'C':
                    labirinth_plan_[{i, j}] = Room(Room::room_type::ROOM_TYPE_C);
                    break;

                case 'D':
                    labirinth_plan_[{i, j}] = Room(Room::room_type::ROOM_TYPE_D);
                    break;

                case '.':
                    labirinth_plan_[{i, j}] = Room(Room::room_type::NO_ROOM);
                    break;
                
                default:
                    throw utilities::ParseException{lab_path};
                    break;
                }

                if (labirinth_plan_[{i, j}].get_type() != Room::NO_ROOM) {

                    if (!set) {
                        current_pose_x_ = i;
                        current_pose_y_ = j;
                        set = true;
                    }

                    if (utilities::getRand(0.0f, 1.0f) < 0.2) { // leave a chance to change the starting point
                        current_pose_x_ = i;
                        current_pose_y_ = j;
                    }

                }

                ++j;
            }

            ++i;
        }

    } // Labirinth::Labirinth ()

    Room& Labirinth::get_current_room () {
        return labirinth_plan_[{current_pose_x_, current_pose_y_}];
    }

    void Labirinth::navigate(int direction) {
        auto sz = labirinth_plan_.size();

        std::cout << direction << std::endl;

        switch (direction)
        {
        case GO_UP:
            ++current_pose_y_;
            break;

        case GO_RIGHT:
            ++current_pose_x_;
            break;

        case GO_LEFT:
            --current_pose_x_;
            break;

        case GO_DOWN:
            --current_pose_y_;
            break;
        
        default:
            throw utilities::GameException("Unknown Direction");
            break;
        }

        if (current_pose_y_ < 0 || current_pose_y_ >= sz.first || 
            current_pose_x_ < 0 || current_pose_x_ >= sz.second  ||
            get_current_room().get_type() == Room::room_type::NO_ROOM) {
            std::cout << current_pose_x_ << " " << current_pose_y_ << std::endl;
            std::cout << sz.first << " " << sz.second << std::endl;
            std::cout << "Type: " << get_current_room().get_type() << std::endl;
            throw utilities::OuterSpaceException("Out of labirinth");
        }
    }

} // namespace mapping