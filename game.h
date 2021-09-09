#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>

class game;

#include "net/player_controller.h"
#include "net/server.h"

#include "map.h"
#include "bullet.h"
#include "debug_tools/collision_visualizer.h"
#include "container.h"
#include "module.h"

#include "boost/asio/io_service.hpp"
#include "boost/asio/deadline_timer.hpp"
#include "boost/bind.hpp"
#include "playermodule.h"

using namespace std;

/**
 * @brief Клас з контролем гри
 */
class game
{
    ModuleInterface interface;
    boost::asio::deadline_timer update_timer;

    //Server host;
    //std::vector<shared_ptr<Bullet>> bullets;
    //std::vector<shared_ptr<player_controller>> players; ///< контролери
public:
    game();
    void update(const boost::system::error_code &);
    void run();
    void load_map() = delete;


    void load_tank(shared_ptr<Tank> tank);
};

#endif // GAME_H
