#include "graphics/screen.h"

Screen::Screen(int width, int height, int left_upper_x, int left_upper_y): 
    Image(width, height, 4), x_(width), y_(height) {}

void Screen::set_map(Map *map) {
    map_ = map;
}

