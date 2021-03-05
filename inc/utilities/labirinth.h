/*! \file labirinth.h
    \brief Labitinth creation from map
    
    Here is a bridge function which handles C errors from glad and 
	transforms it into exception. 
*/

#ifndef LABIRINTH_H
#define LABIRINTH_H

#include <string>

#include "utilities/room.h"
#include "utilities/matrix.h"

namespace mapping {

    enum NavigationDirection {
        GO_LEFT,
        GO_UP,
        GO_RIGHT,
        GO_DOWN
    };

    class Labirinth
    {
        Matrix <Room::room_type> labirinth_plan_;
        int current_pose_x_, current_pose_y_;
    public:
        /**
         * @brief Construct a new Labirinth object
         * 
         * @param lab_path Path to file which contains labirinth description.
         */
        Labirinth(const std::string &lab_path);

        void navigate(int direction);
    }; // class Labirinth

} // namespace mapping


#endif // LABIRINTH_H