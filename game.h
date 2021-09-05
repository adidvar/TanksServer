#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <unordered_map>

class game;

#include "net/player_controller.h"
#include "net/server.h"
#include "map.h"
#include "bullet.h"
#include "debug_tools/collision_visualizer.h"
#include "container.h"

using namespace std;



/**
 * @brief Клас з контролем гри
 */
class game
{
    Container container;

    Server host;
    std::vector<shared_ptr<Bullet>> bullets;
    std::vector<shared_ptr<player_controller>> players; ///< контролери
public:
    game();

    Map map;

    void loop();
    void load_map() = delete;


    void load_tank(shared_ptr<Tank> tank);
};

#endif // GAME_H
