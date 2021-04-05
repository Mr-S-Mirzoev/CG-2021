#include "graphics/screen.h"

Screen::Screen(int width, int height, int left_upper_x, int left_upper_y): 
    Image(width, height, 4), x_(width), y_(height) {}

void Screen::set_room(Room *rm) {
    map_ = rm;
    const_map_ = new Room{*rm};
}

Pixel Screen::get_bg(int x, int y) const {  
    auto sz = map_->get_size();
    if (y < sz.first && x < sz.second) {
        return GetPixel(x, y);
    } else {
        return backgroundColor;
    }
}