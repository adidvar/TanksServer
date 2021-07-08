#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <unordered_map>
#include <collision_up.h>

class game;

#include "net/player_controller.h"
#include "net/server.h"
#include "game_map.h"
#include "bullet.h"
#include "debug_tools/collision_visualizer.h"

using namespace std;

#define SCREEN


/**
 * @brief Клас з контролем гри
 */
class game
{
#ifdef SCREEN
    collision_visualizer visual;
#endif

    Server host;
    std::vector<shared_ptr<Bullet>> bullets;
    std::unordered_map<shared_ptr<player_controller> , shared_ptr<Tank>> players; ///< контролери
public:
    game():_map("map.txt"){};

    Map _map;

    void loop();
    void load_map() = delete;


    void load_tank(shared_ptr<Tank> tank);
};

#endif // GAME_H
