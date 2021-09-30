#ifndef GAME_H
#define GAME_H

#include "modules/module.h"

#include "boost/asio/io_service.hpp"
#include "boost/asio/deadline_timer.hpp"
#include "boost/bind.hpp"

/**
 * @brief Клас з контролем гри
 */
class Game
{
    ModuleInterface interface;
    boost::asio::deadline_timer update_timer;
private:
    void Update(const boost::system::error_code &);
public:
    Game();
    void Run();
};

#endif // GAME_H
