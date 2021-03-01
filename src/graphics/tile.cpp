#include "graphics/tile.h"
#include "utilities/exceptions.h"
#include "utilities/matrix.h"

Image wallset("./res/walls.png");
Image floorset("./res/floor.png");
Image objset("./res/obj_set.png");
Image persset("./res/persons.png");

Tile::Tile(const Image &src, int x_s, int y_s): img_(16, 16, 4) {
    for (int i = x_s; i < x_s + 16; ++i)
        for (int j = y_s; j < y_s + 16; ++j)
            img_.PutPixel(i - x_s, j - y_s, src.GetPixel(i, j));
}

Pixel Tile::get_pixel(int i, int j) const {
    return img_.GetPixel(i, j);
}

Tile wall(objset, 16, 16);
Tile room_floor(floorset, 16, 16);
Tile void_floor(objset, 48, 48);
Tile closed_door(wallset, 64, 32);
/*
Tile open_door(wallset, 64, 48);
Tile tile_exit(wallset, 48, 96);
*/
Tile main_exit(wallset, 64, 16);
Tile key(objset, 128, 96);
Tile person = Tile(persset, 16, 144);

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