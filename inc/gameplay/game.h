/*! \file game.h
    \brief Storage class, which holds the game state
*/
#ifndef GAME_H
#define GAME_H

#include "gameplay/Player.h"
#include "gameplay/inventory.h"

#include "graphics/Image.h"
#include "graphics/screen.h"

#include "utilities/labirinth.h"

class GLFWwindow;

struct Game
{
private:
    std::pair <int, int> get_pose_in_map_coords();
public:
    mapping::Labirinth lab_;
    Player player_;
    Screen screen_buffer_;
    Inventory inventory_;
    GLFWwindow* window_ = nullptr;

    Game();
    ~Game();

    void initGL() const;

    void process_action();
    int get_direction();

    void loop ();
};

#endif //GAME_H
