/*! \file screen.h
    \brief Representation of screen (it can move, etc)
*/
#ifndef SCREEN_H
#define SCREEN_H

#include "graphics/Image.h"
#include "utilities/room.h"

#include <array>

/**
 * @brief Class which represents an abstact of screen plane \n on which we'll print the tiles and pther info
 * 
 */
class Screen : public Image
{
private:
    int x_ = 0; // left upper point of map in screen coordinates/ x coord
    int y_ = 0; // left upper point of map in screen coordinates/ y coord
    
    Room* map_ = nullptr;
    Room* const_map_ = nullptr;

    void get_changed(const std::vector <Image> &images) {
        std::vector <std::vector <bool> > changed;
    }
public:
    /**
     * @brief Construct a new Screen object
     * 
     * @param width width of the screen
     * @param height height of the screen
     */
    Screen(int width, int height, int left_upper_x = 0, int left_upper_y = 0);

    void set_room(Room *map);
    void set_pose(std::pair <int, int> &map_pose);
    void draw(const std::vector <Image> &to_draw);

    Pixel get_bg(int x, int y) const ;
};

#endif //SCREEN_H