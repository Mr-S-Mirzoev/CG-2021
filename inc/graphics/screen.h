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
    int x_ = 0; // left upper point of screen in map coordinates/ x coord
    int y_ = 0; // left upper point of screen in map coordinates/ y coord
    Room* map_ = nullptr;

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

    void set_map(Room *map);
    void draw(const std::vector <Image> &to_draw);
};

#endif //SCREEN_H