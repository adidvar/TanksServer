#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

#include "module.h"

#include "boost/asio/io_service.hpp"
#include "boost/asio/deadline_timer.hpp"
#include "boost/bind.hpp"

#include "playermodule.h"
#include "map.h"

/**
 * @brief Клас з контролем гри
 */
class Game
{
    ModuleInterface interface;
    boost::asio::deadline_timer update_timer;
    //std::vector<shared_ptr<player_controller>> players; ///< контролери
private:
    void Update(const boost::system::error_code &);
public:
    Game();
    void Run();
};

#endif // GAME_H
