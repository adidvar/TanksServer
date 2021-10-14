#ifndef GAME_H
#define GAME_H

#include <queue>

#include "module.h"

#include "boost/asio/io_service.hpp"
#include "boost/asio/deadline_timer.hpp"
#include "boost/bind/bind.hpp"

/**
 * @brief Клас з контролем гри
 */
class Game
{
    ModuleInterface interface;
    boost::asio::deadline_timer update_timer;
    std::vector<std::shared_ptr<Module>> modules;
   // std::queue<std::any> events;
private:
    void Update(const boost::system::error_code &);
    void Event(std::any event);
public:
    Game(boost::asio::io_service &serv);
    void Run();
};

#endif // GAME_H
