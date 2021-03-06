#include "gameplay/Player.h"

static constexpr const int PIXEL_INVISIBLE = 0;

bool Player::Moved() const
{
    if(coords.x == old_coords.x && coords.y == old_coords.y)
        return false;
    else
        return true;
}

void Player::ProcessInput(PlayerAction dir)
{
    int move_dist = move_speed * 1;

    switch(dir)
    {
        case PlayerAction::UP:
            old_coords.y = coords.y;
            coords.y += move_dist;
            break;
        case PlayerAction::DOWN:
            old_coords.y = coords.y;
            coords.y -= move_dist;
            break;
        case PlayerAction::LEFT:
            old_coords.x = coords.x;
            coords.x -= move_dist;
            break;
        case PlayerAction::RIGHT:
            old_coords.x = coords.x;
            coords.x += move_dist;
            break;
        default:
            break;
    }
}

Point Player::get_coords() const {
    return coords;
}

void Player::Draw(Image &screen)
{
    
    if (Moved()) {
        /*
        for(int y = old_coords.y; y <= old_coords.y + tileSize; ++y) 
            for(int x = old_coords.x; x <= old_coords.x + tileSize; ++x)
                screen.PutPixel(x, y, backgroundColor);
        */
        
        old_coords = coords;
    }

    for(int y = coords.y; y <= coords.y + tileSize; ++y) {
        for(int x = coords.x; x <= coords.x + tileSize; ++x) {
            auto player_pixel = person.get_pixel(x - coords.x, tileSize - y + coords.y);
            if (player_pixel.a != PIXEL_INVISIBLE)
                screen.PutPixel(x, y, player_pixel);
        }
    }
}