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

using namespace std;


/**
 * @brief Клас з контролем гри
 */
class game
{
    Server host;
    std::unordered_map<shared_ptr<player_controller> , shared_ptr<tank>> players; ///< контролери
public:
    game():_map("map.txt"){};

    Map _map;

    void loop();
    void load_map() = delete;


    void load_tank(shared_ptr<tank> tank);
};

#endif // GAME_H
