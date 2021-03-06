#include "utilities/game_object.h"
#include "gameplay/game.h"

void KeyObject::apply_action(Game &gm) {
    if (state_ == ACTION_NOT_APPLIED) {
        state_ = ACTION_APPLIED;
        current_tile_ = &get_tile_by_name("floor");
        gm.inventory_.add("key");
    }
}

void ExitObject::apply_action(Game &gm) {
    if (state_ == ACTION_NOT_APPLIED)
        current_tile_ = &get_tile_by_name("exit");

    gm.lab_.navigate(gm.get_direction());
}

void MainExitObject::apply_action(Game &gm) {
    
}

void DoorObject::apply_action(Game &gm) {

}

void VoidObject::apply_action(Game &gm) {

}

void WallObject::apply_action(Game &gm) {
    gm.player_.Collision();
}