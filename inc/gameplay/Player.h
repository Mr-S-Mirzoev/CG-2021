/*! \file Player.h
    \brief Point, MovementDirection and Player classes
*/
#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "graphics/Image.h"
#include "graphics/tile.h"
struct Point
{
    int x;
    int y;
};

enum class MovementDir
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Player
{
    explicit Player(Point pos = {.x = 10, .y = 10}) :
                    coords(pos), old_coords(coords), person(get_tile_by_name("person")) {};

    /**
     * @return true - if current coordinates are equal to old
     * @return false - if current coordinates are not equal to old
     */
    bool Moved() const;
    /**
     * @brief Move the player from it's current position to the direction
     * 
     * @param dir - movement direction (of enum class MovementDir)
     */
    void ProcessInput(MovementDir dir);
    /**
     * @brief If player moved, move the player tile, save old coords
     * 
     * @param screen - Reference to Image object on which we're planning to draw
     */
    void Draw(Image &screen);

private:
    Point coords {.x = 10, .y = 10};
    Point old_coords {.x = 10, .y = 10};
    Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
    int move_speed = 4;
    Tile &person;
};

#endif //MAIN_PLAYER_H
