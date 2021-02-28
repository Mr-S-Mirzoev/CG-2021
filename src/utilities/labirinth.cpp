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
                    labirinth_plan_[{i, j}] = Room::ROOM_TYPE_A;
                    break;

                case 'B':
                    labirinth_plan_[{i, j}] = Room::ROOM_TYPE_B;
                    break;

                case 'C':
                    labirinth_plan_[{i, j}] = Room::ROOM_TYPE_C;
                    break;

                case 'D':
                    labirinth_plan_[{i, j}] = Room::ROOM_TYPE_D;
                    break;

                case '.':
                    labirinth_plan_[{i, j}] = Room::NO_ROOM;
                    break;
                
                default:
                    throw utilities::ParseException{lab_path};
                    break;
                }
            }

            if (labirinth_plan_[{i, j}] != Room::NO_ROOM) {

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

            ++i;
        }
    } // Labirinth::Labirinth ()

} // namespace mapping