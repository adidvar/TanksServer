#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <unordered_map>

class game;

#include "player_controller.h"
#include "server.h"

using namespace std;


/**
 * @brief Клас з контролем гри
 */
class game
{
    Server host;
    std::unordered_map<player_controller* , shared_ptr<tank>> players; ///< контролери
public:
    game() = default;
    void loop();
    void load_map() = delete;


    void load_tank(shared_ptr<tank> tank);
};

#endif // GAME_H
