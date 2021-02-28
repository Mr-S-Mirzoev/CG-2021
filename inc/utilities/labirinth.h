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

    class Labirinth
    {
        Matrix <Room::room_type> labirinth_plan_;
        int current_pose_x_, current_pose_y_;
    public:
        Labirinth(const std::string &lab_path);
    }; // class Labirinth

} // namespace mapping


#endif // LABIRINTH_H