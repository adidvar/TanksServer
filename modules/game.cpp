#include "game.h"
#include "out.h"

#include "player_controller.h"
#include "map.h"
#include "bulletmodule.h"

const unsigned delay = 10;

Game::Game(boost::asio::io_service &serv):
    interface(serv , boost::bind(&Game::Event, this, boost::placeholders::_1)),
    update_timer(serv,boost::posix_time::millisec(delay))
{
    modules.emplace_back(new PlayerModule(interface));
    //interface.modules.emplace_back(new Map(interface,"map.txt"));
    //interface.modules.emplace_back(new BulletModule(interface));

    for(auto &x : modules)
        x->Start();

    update_timer.async_wait(boost::bind(&Game::Update,this,boost::asio::placeholders::error));
}

void Game::Update(const boost::system::error_code &error)
{
    if(error) {
        warning(error.message());
        return;
    }
/*
    while(!events.empty())
    {
        std::any &event = events.front();
        events.pop();
        for (auto& module : modules)
            module->Event(event);
    }
*/
    interface.container.Update();

    update_timer.expires_from_now(boost::posix_time::millisec(delay));
    update_timer.async_wait(boost::bind(&Game::Update,this,boost::asio::placeholders::error));
}

void Game::Event(std::any event)
{
  //  this->events.push(event);
}


void Game::Run()
{
    this->interface.service.run();
}
