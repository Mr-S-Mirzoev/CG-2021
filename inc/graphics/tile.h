/*! \file game.h
    \brief Storage class, which holds the game state
*/
#ifndef TILE_H
#define TILE_H

#include "graphics/Image.h"

constexpr const int tile_size = 16;

#include <string>

class Tile {
private:
    Image img_;
public:
    Tile(const Image &src, int i = 0, int j = 0);

    Pixel get_pixel(int i, int j) const;
};

Tile& get_tile_by_name(const std::string &tile_name);

#endif //TILE_H
