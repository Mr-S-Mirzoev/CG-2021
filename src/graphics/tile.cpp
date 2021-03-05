#include "graphics/tile.h"
#include "utilities/exceptions.h"
#include "utilities/matrix.h"

Image wallset("./res/walls.png");
Image floorset("./res/floor.png");
Image objset("./res/obj_set.png");
Image persset("./res/persons.png");

Tile::Tile(const Image &src, int x_s, int y_s): img_(tileSize, tileSize, 4) {
    x_s *= tileSize;
    y_s *= tileSize;

    for (int i = x_s; i < x_s + tileSize; ++i)
        for (int j = y_s; j < y_s + tileSize; ++j)
            img_.PutPixel(i - x_s, j - y_s, src.GetPixel(i, j));
}

Pixel Tile::get_pixel(int i, int j) const {
    return img_.GetPixel(i, j);
}

Tile wall(objset, 1, 1);
Tile room_floor(floorset, 1, 1);
Tile void_floor(objset, 3, 3);
Tile closed_door(wallset, 4, 2);
/*
Tile open_door(wallset, 64, 48);
Tile tile_exit(wallset, 48, 96);
*/
Tile main_exit(wallset, 4, 1);
Tile key(objset, 8, 6);
Tile person = Tile(persset, 1, 9);

Tile& get_tile_by_name(const std::string &tile_name) {
    if (tile_name == "wall")
        return wall;
    else if (tile_name == "floor")
        return room_floor;
    else if (tile_name == "void")
        return void_floor;
    else if (tile_name == "door")
        return closed_door;
    else if (tile_name == "exit")
        return room_floor;
    else if (tile_name == "main_exit")
        return main_exit;
    else if (tile_name == "key")
        return key;
    else if (tile_name == "person")
        return person;
    else 
        throw utilities::DictError(tile_name, "get_tile_by_name");
}