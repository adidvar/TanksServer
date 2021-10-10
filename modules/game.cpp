#include "game.h"
#include "out.h"

#include "player_controller.h"
#include "map.h"
#include "bulletmodule.h"

const unsigned delay = 10;

Game::Game():
    update_timer(interface.Service(),boost::posix_time::millisec(delay))
{
    interface.modules.emplace_back(new PlayerModule(interface));
    //interface.modules.emplace_back(new Map(interface,"map.txt"));
    //interface.modules.emplace_back(new BulletModule(interface));

    for(auto &x : interface.modules)
        x->Start();
    update_timer.async_wait(boost::bind(&Game::Update,this,boost::asio::placeholders::error));
}

void Game::Update(const boost::system::error_code &)
{
    while(!this->interface.signals.empty())
    {
        auto &signal = this->interface.signals.front();
        for (auto& module : this->interface.modules)
            module->Signal(signal);
        this->interface.signals.pop();
    }

    interface.container.Update();
    update_timer.expires_from_now(boost::posix_time::millisec(delay));
    update_timer.async_wait(boost::bind(&Game::Update,this,boost::asio::placeholders::error));
}

void Game::Run()
{
    this->interface.service.run();
}
